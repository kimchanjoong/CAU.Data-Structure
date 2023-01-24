#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char word[11];
	int count;
} element;

typedef struct Node {
	element data;
	struct Node* leftchild;
	struct Node* rightchild;
}node;
typedef node* treePointer;

treePointer modifiedSearch(treePointer tree, char target[11])
{
	if (tree == NULL)
	{
		return NULL;
	}
	else
	{
		while (tree)
		{
			if (strcmp(target, tree->data.word) == 0) //������ word�� ã���� count ���� +1, NULL�� ����
			{
				tree->data.count++;
				return NULL;
			}
			else
			{
				if (target[0] < tree->data.word[0])
				{
					if (tree->leftchild == NULL)
					{
						return tree;
					}
					tree = tree->leftchild;
				}
				else
				{
					if (tree->rightchild == NULL)
					{
						return tree;
					}
					tree = tree->rightchild;
				}
			}
		}
	}
}

void insert(treePointer* tree, char target[11]) //*tree�� Ʈ���� ���������� ����Ű�� ������
{
	treePointer ptr;
	treePointer temp = modifiedSearch(*tree, target);
	if (temp || !(*tree))
	{
		ptr = (treePointer)malloc(sizeof(node));
		ptr->data.count = 1;
		strcpy_s(ptr->data.word, 11, target);
		ptr->leftchild = ptr->rightchild = NULL;
		if (*tree) //*tree�� NULL�̸� *tree�� ����Ű�� ��尡 �� ptr�� �Ǿ���Ѵ�.
		{
			if (target[0] < temp->data.word[0])
			{
				temp->leftchild = ptr;
			}
			else
			{
				temp->rightchild = ptr;
			}
		}
		else
		{
			*tree = ptr;
		}
	}
}

void inorder(treePointer ptr)
{
	if (ptr)
	{
		inorder(ptr->leftchild);
		printf("%s : %d      ", ptr->data.word, ptr->data.count);
		inorder(ptr->rightchild);
	}
}

void freeTree(treePointer ptr)
{
	if (ptr == NULL)
	{
		return;
	}
	else
	{
		freeTree(ptr->leftchild);
		freeTree(ptr->rightchild);
		free(ptr);
	}
}

int main(void)
{
	printf("next word ? ");
	char wording[11];
	gets_s(wording, sizeof(wording));
	if (strcmp(wording, "END") == 0)
	{
		return 0;
	}
	treePointer first = (treePointer)malloc(sizeof(node)); //�ʱ� ��带 NULL�� �ʱ�ȭ
	first->leftchild = NULL;
	first->rightchild = NULL;
	strcpy_s(first->data.word, 11, wording);
	first->data.count = 1;
	inorder(first);
	printf("\n\n");

	do
	{
		printf("next word ? ");
		gets_s(wording, sizeof(wording));
		if (strcmp(wording, "END") == 0)
		{
			break;
		}
		insert(&first, wording);
		inorder(first);
		printf("\n\n");
	} while (strcmp(wording, "END") != 0);

	freeTree(first);
}