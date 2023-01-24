#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct person {
	char name[7]; //각각 사람의 이름은 6글자를 넘어가지 않는다.
};

 struct Stack{ //R(a,b)의 처리를 도와주기위한 스택
	int data;
	struct Stack* next;
};

struct Stack* top;

int stack_empty()
{
	if (top == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void addrear_stack(int val)
{
	struct Stack* newnode = (struct Stack*) malloc(sizeof(struct Stack));
	newnode->data = val;
	newnode->next = top;

	top = newnode;
}

int pop_stack() //스택의 맨 뒤의 것을 pop해주는 것, 인자를 넘겨 받을 필요가 없다.
{
	if (!stack_empty())
	{
		struct Stack* temp = top;
		int data = temp->data;
		top = temp->next;
		free(temp);
		return data;
	}
}

struct Node {
	int data;
	struct Node* next;
};

struct Que {
	struct Node* front, * rear;
};

void init_Que(struct Que* q)
{
	q->front = q->rear = NULL;
}

int Que_empty(struct Que* q)
{
	return (q->front == NULL);
}

void addrear_Que(struct Que* q, int val)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = val;
	temp->next = NULL;
	if (Que_empty(q))
	{
		q->front = temp;
		q->rear = temp;
	}
	else
	{
		q->rear->next = temp;
		q->rear = temp;
	}
}

int pop_que(struct Que* q)
{
	struct Node* temp;
	int val;
	if (Que_empty(q))
	{
		printf("Que is empty");
	}
	else
	{
		temp = q->front;
		val = temp->data;
		q->front = temp->next;
		if (q->front == NULL)
		{
			q->rear = NULL;
		}
		free(temp);
		return val;
	}
}

struct person p[16] = {
		{"DDD"},  {"Tom"}, {"Kate"}, {"Wang"},
		{"Lucy"}, {"Ford"}, {"Luna"}, {"Wing"},
		{"Lina"}, {"Mike"}, {"Lisa"}, {"Luke"},
		{"Mina"}, {"Pyke"}, {"Rosa"}, {"Eric"}
}; //a라는 구조체 배열에 15명의 이름을 저장, 0번째 index내에는 안들어간다. 0번째에는 임의의 문자열을 넣어준다.	p[0].name = 'DDD';

int search_locate(char b[7], struct person p[16]) //에러 입력에 대하여 취급하지 않는다는 과제의 조건에 의해 예외 케이스는 제외한다. C4715의 경우 예외 케이스 적용을 안했기 때문에 발생
{
	int i;
	for (i = 1; i <= 15; i++)
	{
		if (!strcmp(b, p[i].name))
		{
			return i;
		}
	}
}

void Descendant(char b[7])
{
	int id;
	id = search_locate(b, p) / 2;
	if (id == 0)
	{
		printf("Unknown");
	}
	else
	{
		while (id != 0)
		{
			printf("%s ", p[id].name);
			id = id / 2;
		}
	}
}

void Ancestor(char b[7])
{
	struct Que que;
	init_Que(&que);
	int id, id1, id2, j;
	id = search_locate(b, p);
	if (id * 2 > 15)
	{
		printf("Unknown");
	}
	else
	{
		id1 = id * 2;
		id2 = id * 2 + 1;
		addrear_Que(&que, id1);
		addrear_Que(&que, id2);
		while (!Que_empty(&que))
		{
			j = pop_que(&que);
			printf("%s ", p[j].name);
			if (j * 2 < 15)
			{
				id1 = j * 2;
				id2 = j * 2 + 1;
				addrear_Que(&que, id1);
				addrear_Que(&que, id2);
			}
		}
	}
}

void Relation(char b1[7], char b2[7])
{
	int id_b1, id_b2;
	id_b1 = search_locate(b1, p);
	id_b2 = search_locate(b2, p);
	int count = 0;
	int name_locate;

	while (id_b2 >= id_b1)
	{
		addrear_stack(id_b2);
		id_b2 = id_b2 / 2;
		count++;
	}

	printf("%s", p[pop_stack()].name);
	while (count != 1)
	{
		name_locate = pop_stack();
		if (name_locate % 2 == 0)
		{
			printf(" -> M -> %s", p[name_locate].name);
		}
		else
		{
			printf(" -> F -> %s", p[name_locate].name);
		}
		count--;
	}
}

int main(void)
{
	char menu_name[20];
	do
	{
		char* a = NULL;
		printf("\n? ");
		gets_s(menu_name, sizeof(menu_name));
		if (menu_name[0] == 'A')
		{
			char* tempb1 = strtok_s(menu_name, "(", &a);
			char* tempb2 = strtok_s(NULL, ")", &a);
			printf("A(%s) = ", tempb2);
			Ancestor(tempb2);
			printf("\n");
		}
		else if (menu_name[0] == 'D')
		{
			char* tempd1 = strtok_s(menu_name, "(", &a);
			char* tempd2 = strtok_s(NULL, ")", &a);
			printf("D(%s) = ", tempd2);
			Descendant(tempd2);
			printf("\n");
		}
		else if (menu_name[0] == 'R')
		{
			char* tempr1 = strtok_s(menu_name, "(", &a);
			char* tempr2 = strtok_s(NULL, ",", &a);
			char* tempr3 = strtok_s(NULL, ")", &a);
			printf("R(%s,%s) = ", tempr2, tempr3);
			Relation(tempr2, tempr3);
			printf("\n");
		}
		else
		{
			break;
		}
	} while (strcmp(menu_name, "END"));
}