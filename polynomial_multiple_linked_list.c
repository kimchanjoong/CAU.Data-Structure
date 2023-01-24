#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int degree;
	int coef[10];
}polynomial;

struct Node { //����� ���� ��� : 1. ���� �� ���, 2. ���� ��带 ����Ű�� ������ (link)
	int expon;
	int coef;
	struct Node* next;	// ���� ����� ���� ��� ������
};

struct Node* pStart = NULL;	// ����Ʈ�� ù ����� ������
struct Node* pEnd = NULL;	// ����Ʈ�� ������ ����� ������, addrear�� �����ϰ� �ϱ����� ���


void addrear(int exp, int co);
void del(int exp);
int Search_expon(int exp, int co);
int Search_locate(int exp, struct Node* Current);
void Addbetween(int exp, int coef, int locate);
void printlist(struct Node* Current);


void pmul(polynomial a, polynomial b)
{
	int i, j, k, z, exp, co; //k�� ���׽� D�� ��ġ�ϱ� ���� �ʿ��ϴ�!
	for (i = a.degree; i >= 0; i--)
	{
		if (a.coef[i] == 0) //����� 0�̸� ���� ������ ����!
		{
			continue;
		}
		else
		{
			for (j = b.degree; j >= 0; j--)
			{
				if (b.coef[j] != 0)
				{
					if (i == a.degree) //�ʱ� ���������� ��ġ�� �ʿ����.
					{
						exp = i + j;
						co = a.coef[i] * b.coef[j];
						addrear(exp, co);
					}
					else //�������� ���� �� ��ġ�� �ʿ��ϴ�.
					{
						exp = i + j;
						co = a.coef[i] * b.coef[j];
						k = Search_expon(exp, co); //������ �����ϴ� �������̸� 0�� ����, ���ο� �������̸� 1�� ���ϵȴ�.
						if (k)
						{
							z = Search_locate(exp, pStart);
							if (z == 0)
							{
								addrear(exp, co);
							}
							else
							{
								Addbetween(exp, co, z);
							}
						}
						else
						{
							continue; //�ʿ� ���� ���������� �������� ���� �ڵ�
						}
					}
				}
				else
				{
					continue;
				}
			}
		}
	}
}

void addrear(int exp, int co) //�ڿ� �߰�
{
	struct Node* Current;	// ����Ʈ�� �߰��� �� ��� ����
	Current = (struct Node*)malloc(sizeof(struct Node));
	Current->expon = exp;
	Current->coef = co;	// �� Node data �ʵ忡 val �� ����
	Current->next = NULL;	// ����Ʈ �������� �߰��� ����̹Ƿ� ���� ��� ����

	if (pStart == NULL)		// ù ��° ����� ���
		pStart = pEnd = Current;
	else {
		pEnd->next = Current;	// ������ �뽺Ʈ ������ ���� ���� ��� �߰�
		pEnd = Current;		// ����Ʈ �������� �߰��ϴ� ���̹Ƿ� pEnd �� �ٲ���
	}
}

void del(int exp)
{
	struct Node* p = pStart; //���� pstart�� �Ѽ����� �ʱ� ���� ���纻�� �̿���.
	struct Node* q = p->next;

	while (q != NULL) {
		if (q->expon == exp) {
			p->next = q->next;
			free(q);
			break;
		}
		p = q;
		q = p->next;
	}
}

int Search_expon(int exp, int co)
{
	struct Node* p = pStart; //���� pstart�� �Ѽ����� �ʱ� ���� ���纻�� �̿���.
	struct Node* q = p->next;

	while (q != NULL)
	{
		if (q->expon == exp)
		{
			q->coef += co;//���� �߰� �Ǵ� ���� ������ ������ �����ϴ� ������ ���� ��
			if (q->coef == 0)
			{
				del(exp);
				return 0; //�Լ��� ����������.
			}
			else
			{
				return 0; //�Լ��� ����������.
			}
		}
		p = q;
		q = p->next;
	}
	return 1; //���� �߰��Ǵ� ���� ������ ������ �������� ���� ��
}

int Search_locate(int exp, struct Node* Current)
{
	int len = 1;
	Current = pStart;
	while (Current != NULL) {
		len++;
		Current = Current->next;
	}

	int count = 1;

	struct Node* p = pStart;
	struct Node* q = pStart->next;

	while (q->expon > exp)
	{
		count++;
		p = q;
		q = p->next;
		if (q == NULL)
		{
			break;
		}
	}

	if (len > count)
	{
		return count; //������ �� ������ �ε����� ��ȯ���ش�.
	}
	else
	{
		return 0; //�ԷµǾ��ϴ� ���� ������ ���� ���� ��
	}
}

void Addbetween(int exp, int co, int locate)
{
	struct  Node* Current; // ����Ʈ�� �߰��� ���ο� ��� ����
	Current = (struct Node*)malloc(sizeof(struct Node));
	Current->expon = exp;
	Current->coef = co;

	struct Node* p = pStart; //���� pstart�� �Ѽ����� �ʱ� ���� ���纻�� �̿���.
	struct Node* q = p->next;

	for (int i = 1; i < locate; i++)
	{
		p = q;
		q = p->next;
	}
	Current->next = p->next;
	p->next = Current;
}

void printlist(struct Node* Current)
{
	printf("\nD(x) = ");
	Current = pStart;
	printf("%dx%d", Current->coef, Current->expon);
	Current = Current->next;
	while (Current != NULL) {
		if (Current->coef < 0)
		{
			printf(" - %dx%d", (-1) * (Current->coef), Current->expon);
		}
		else
		{
			printf(" + %dx%d", Current->coef, Current->expon);
		}
		Current = Current->next;
	}
}

int main(void)
{
	polynomial a;
	polynomial b;
	int i, j, t;

	int a_coef;
	int b_coef;
	int a_exp;
	int b_exp;

	for (t = 0; t < 3; t++)
	{
		int a_num = 3;
		int b_num = 3;

		for (j = 0; j < 10; j++)
		{
			a.coef[j] = 0; //���׽� A�� B�� �ʱ�ȭ���ش�.
			b.coef[j] = 0;
		}

		printf("���׽� A�� ������������ �Է��Ͻÿ�. (���, ����)\n");
		while (a_num >= 1)
		{
			scanf_s("%d", &a_coef);
			scanf_s("%d", &a_exp);
			a.coef[a_exp] = a_coef;
			if (a_num == 3)
			{
				a.degree = a_exp;
			}
			a_num--;
		}

		printf("���׽� B�� ������������ �Է��Ͻÿ�. (���, ����)\n");
		while (b_num >= 1)
		{
			scanf_s("%d", &b_coef);
			scanf_s("%d", &b_exp);
			b.coef[b_exp] = b_coef;
			if (b_num == 3)
			{
				b.degree = b_exp;
			}
			b_num--;
		}

		printf("\n");

		pmul(a, b);

		printf("A(x) = ");
		for (j = 0; j <= 9; j++)
		{
			if (j == 0)
			{
				printf("%dx%d", a.coef[j], j);
			}
			else
			{
				if (a.coef[j] < 0)
				{
					printf(" - %dx%d", (-1) * a.coef[j], j);
				}
				else
				{
					printf(" + %dx%d", a.coef[j], j);
				}
			}
		}

		printf("\nB(x) = ");
		for (j = 0; j <= 9; j++)
		{
			if (j == 0)
			{
				printf("%dx%d", b.coef[j], j);
			}
			else
			{
				if (b.coef[j] < 0)
				{
					printf(" - %dx%d", (-1) * b.coef[j], j);
				}
				else
				{
					printf(" + %dx%d", b.coef[j], j);
				}
			}
		}

		printlist(pStart);

		for (i = 0; i <= a.degree; i++)
		{
			a.coef[i] = 0;
		}
		for (i = 0; i <= b.degree; i++)
		{
			b.coef[i] = 0;
		} //���� ������ 3�� �ݺ��ؾ��ϹǷ� �ٽ� 0���� �ʱ�ȭ�Ѵ�.

		struct  Node* temp; //������ ����ߴ� ����Ʈ�� �����ϱ� ���ؼ� ������ �ִ� ����Ʈ�� ��� free���ش��� �ʱⰪ�� NULL�� �缳���ؾ���.
		temp = pStart;
		while (temp != NULL)
		{
			pStart = pStart->next;
			free(temp);
			temp = pStart;
		}

		pStart = NULL;
		pEnd = NULL;

		printf("\n\n");
	}
}