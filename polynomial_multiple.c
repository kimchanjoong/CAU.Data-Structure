#include<stdio.h>

typedef struct
{
	int degree;
	int coef[10];
}polynomial;

typedef struct
{
	int coef; //계수
	int expon; //지수
}polyD; //D의 다항식은 항배열방식이라 다른 구조체를 선언한다.
polyD terms[10];

void pmul(polynomial a, polynomial b, int* avail)
{
	int i, j, k, z; //k는 다항식 D를 서치하기 위해 필요하다!
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
						terms[*avail].coef = a.coef[i] * b.coef[j];
						terms[*avail].expon = i + j;
						*avail = *avail + 1;
					}
					else //이제부턴 곱셈 후 서치가 필요하다.
					{
						for (k = 0; k < *avail; k++) //서칭을 위한 for문
						{
							if (terms[k].expon == i + j) //차수가 겹친다면 avail을 추가할 필요가 없이 항을 업데이트하면 된다.
							{
								terms[k].coef = terms[k].coef + a.coef[i] * b.coef[j];
								if (terms[k].coef == 0) //항 배열법에선 계수가 0인 경우 저장하지 않는다.
								{
									terms[k].expon == 0; //계수가 0이 된 항을 초기화해준다.
									for (z = k; z < *avail - 1; z++) //초기화된 항이 k번째 항이므로 k번째 이후의 항을 한칸씩 앞당겨준다.
									{
										terms[z].coef = terms[z + 1].coef; //마지막항(avail-1)이후는 모두 0으로 초기화 되어있기 때문에 이러한 방법을 써도 무난하다.
										terms[z].expon = terms[z + 1].expon;
									}
									*avail = *avail - 1; //항이 하나가 삭제되었으므로 *avail의 값을 하나 줄여준다.
									goto t;
								}
								else //계수가 0이 아닌 경우
								{
									goto t;
								}
							}
							else
							{
								continue;
							}
						} //서칭을하고 나온다. 이후에 추가되는 항이 이전에 있던 항보다 차수가 크면 그 사이에 넣어줘야한다.
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
		int avail = 0; //D와 관련된 변수, D의 항의 개수가 되는 것이다.
		int a_num = 3;
		int b_num = 3;

		for (j = 0; j < 10; j++)
		{
			terms[j].coef = 0;
			terms[j].expon = 0; //다항식 D를 초기화해준다.
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

		//printf("\n%d", avail); avail의 값이 잘 맞는지 확인해보기 위해 사용했던 코드 부분
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
		} //위의 과정을 3번 반복해야하므로 다시 0으로 초기화한다.
		printf("\n\n");
	}
}