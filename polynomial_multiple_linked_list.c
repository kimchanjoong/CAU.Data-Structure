#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int degree;
	int coef[10];
}polynomial;

struct Node { //노드의 구성 요소 : 1. 지수 및 계수, 2. 다음 노드를 가리키는 포인터 (link)
	int expon;
	int coef;
	struct Node* next;	// 현재 노드의 다음 노드 포인터
};

struct Node* pStart = NULL;	// 리스트의 첫 노드의 포인터
struct Node* pEnd = NULL;	// 리스트의 마지막 노드의 포인터, addrear을 수월하게 하기위한 노드


void addrear(int exp, int co);
void del(int exp);
int Search_expon(int exp, int co);
int Search_locate(int exp, struct Node* Current);
void Addbetween(int exp, int coef, int locate);
void printlist(struct Node* Current);


void pmul(polynomial a, polynomial b)
{
	int i, j, k, z, exp, co; //k는 다항식 D를 서치하기 위해 필요하다!
	for (i = a.degree; i >= 0; i--)
	{
		if (a.coef[i] == 0) //계수가 0이면 곱할 이유가 없다!
		{
			continue;
		}
		else
		{
			for (j = b.degree; j >= 0; j--)
			{
				if (b.coef[j] != 0)
				{
					if (i == a.degree) //초기 곱셈값에는 서치가 필요없다.
					{
						exp = i + j;
						co = a.coef[i] * b.coef[j];
						addrear(exp, co);
					}
					else //이제부턴 곱셈 후 서치가 필요하다.
					{
						exp = i + j;
						co = a.coef[i] * b.coef[j];
						k = Search_expon(exp, co); //기존에 존재하는 차수항이면 0이 리턴, 새로운 차수항이면 1이 리턴된다.
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
							continue; //필요 없는 구문이지만 가독성을 위한 코드
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

void addrear(int exp, int co) //뒤에 추가
{
	struct Node* Current;	// 리스트에 추가할 새 노드 생성
	Current = (struct Node*)malloc(sizeof(struct Node));
	Current->expon = exp;
	Current->coef = co;	// 새 Node data 필드에 val 을 저장
	Current->next = NULL;	// 리스트 마지막에 추가할 노드이므로 다음 노드 없음

	if (pStart == NULL)		// 첫 번째 노드일 경우
		pStart = pEnd = Current;
	else {
		pEnd->next = Current;	// 마지막 노스트 다음에 새로 만든 노드 추가
		pEnd = Current;		// 리스트 마지막에 추가하는 것이므로 pEnd 를 바꿔줌
	}
}

void del(int exp)
{
	struct Node* p = pStart; //기존 pstart를 훼손하지 않기 위해 복사본을 이용함.
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
	struct Node* p = pStart; //기존 pstart를 훼손하지 않기 위해 복사본을 이용함.
	struct Node* q = p->next;

	while (q != NULL)
	{
		if (q->expon == exp)
		{
			q->coef += co;//새로 추가 되는 항의 차수가 기존에 존재하는 차수의 항일 때
			if (q->coef == 0)
			{
				del(exp);
				return 0; //함수를 빠져나간다.
			}
			else
			{
				return 0; //함수를 빠져나간다.
			}
		}
		p = q;
		q = p->next;
	}
	return 1; //새로 추가되는 항의 차수가 기존에 존재하지 않을 때
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
		return count; //들어가야할 곳 이전의 인덱스를 반환해준다.
	}
	else
	{
		return 0; //입력되야하는 항의 차수가 가장 작을 때
	}
}

void Addbetween(int exp, int co, int locate)
{
	struct  Node* Current; // 리스트에 추가할 새로운 노드 생성
	Current = (struct Node*)malloc(sizeof(struct Node));
	Current->expon = exp;
	Current->coef = co;

	struct Node* p = pStart; //기존 pstart를 훼손하지 않기 위해 복사본을 이용함.
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
			a.coef[j] = 0; //다항식 A와 B도 초기화해준다.
			b.coef[j] = 0;
		}

		printf("다항식 A를 내림차순으로 입력하시오. (계수, 차수)\n");
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

		printf("다항식 B를 내림차순으로 입력하시오. (계수, 차수)\n");
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
		} //위의 과정을 3번 반복해야하므로 다시 0으로 초기화한다.

		struct  Node* temp; //이전에 사용했던 리스트를 재사용하기 위해선 기존에 있던 리스트를 모두 free해준다음 초기값을 NULL로 재설정해야함.
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