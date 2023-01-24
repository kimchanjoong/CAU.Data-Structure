#include<stdio.h>

typedef struct
{
	int degree;
	int coef[10];
}polynomial;

typedef struct
{
	int coef; //���
	int expon; //����
}polyD; //D�� ���׽��� �׹迭����̶� �ٸ� ����ü�� �����Ѵ�.
polyD terms[10];

void pmul(polynomial a, polynomial b, int* avail)
{
	int i, j, k, z; //k�� ���׽� D�� ��ġ�ϱ� ���� �ʿ��ϴ�!
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
						terms[*avail].coef = a.coef[i] * b.coef[j];
						terms[*avail].expon = i + j;
						*avail = *avail + 1;
					}
					else //�������� ���� �� ��ġ�� �ʿ��ϴ�.
					{
						for (k = 0; k < *avail; k++) //��Ī�� ���� for��
						{
							if (terms[k].expon == i + j) //������ ��ģ�ٸ� avail�� �߰��� �ʿ䰡 ���� ���� ������Ʈ�ϸ� �ȴ�.
							{
								terms[k].coef = terms[k].coef + a.coef[i] * b.coef[j];
								if (terms[k].coef == 0) //�� �迭������ ����� 0�� ��� �������� �ʴ´�.
								{
									terms[k].expon == 0; //����� 0�� �� ���� �ʱ�ȭ���ش�.
									for (z = k; z < *avail - 1; z++) //�ʱ�ȭ�� ���� k��° ���̹Ƿ� k��° ������ ���� ��ĭ�� �մ���ش�.
									{
										terms[z].coef = terms[z + 1].coef; //��������(avail-1)���Ĵ� ��� 0���� �ʱ�ȭ �Ǿ��ֱ� ������ �̷��� ����� �ᵵ �����ϴ�.
										terms[z].expon = terms[z + 1].expon;
									}
									*avail = *avail - 1; //���� �ϳ��� �����Ǿ����Ƿ� *avail�� ���� �ϳ� �ٿ��ش�.
									goto t;
								}
								else //����� 0�� �ƴ� ���
								{
									goto t;
								}
							}
							else
							{
								continue;
							}
						} //��Ī���ϰ� ���´�. ���Ŀ� �߰��Ǵ� ���� ������ �ִ� �׺��� ������ ũ�� �� ���̿� �־�����Ѵ�.
						for (k = *avail - 1; k >= 0; k--)
						{
							if ((i + j) < terms[k].expon)
							{
								for (z = *avail; z >= k + 2; z--)
								{
									terms[z].coef = terms[z - 1].coef;
									terms[z].expon = terms[z - 1].expon;
								}
								terms[k + 1].coef = a.coef[i] * b.coef[j];
								terms[k + 1].expon = i + j;
								*avail = *avail + 1;
								goto t;
							}
							else
							{
								continue;
							}
						}
					t:;
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

int main(void)
{
	polynomial a;
	polynomial b;
	int i, j, k;

	int a_coef;
	int b_coef;
	int a_exp;
	int b_exp;

	for (k = 0; k < 3; k++)
	{
		int avail = 0; //D�� ���õ� ����, D�� ���� ������ �Ǵ� ���̴�.
		int a_num = 3;
		int b_num = 3;

		for (j = 0; j < 10; j++)
		{
			terms[j].coef = 0;
			terms[j].expon = 0; //���׽� D�� �ʱ�ȭ���ش�.
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

		pmul(a, b, &avail);

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

		//printf("\n%d", avail); avail�� ���� �� �´��� Ȯ���غ��� ���� ����ߴ� �ڵ� �κ�
		printf("\nD(x) = ");
		for (j = 0; j < avail; j++)
		{
			if (terms[j].coef == 0)
			{
				continue;
			}
			if (j == 0)
			{
				printf("%dx%d", terms[j].coef, terms[j].expon);
			}
			else
			{
				if (terms[j].coef < 0)
				{
					printf(" - %dx%d", (-1) * terms[j].coef, terms[j].expon);
				}
				else
				{
					printf(" + %dx%d", terms[j].coef, terms[j].expon);
				}
			}
		}
		for (i = 0; i <= a.degree; i++)
		{
			a.coef[i] = 0;
		}
		for (i = 0; i <= b.degree; i++)
		{
			b.coef[i] = 0;
		} //���� ������ 3�� �ݺ��ؾ��ϹǷ� �ٽ� 0���� �ʱ�ȭ�Ѵ�.
		printf("\n\n");
	}
}