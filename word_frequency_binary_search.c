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
			if (strcmp(target, tree->data.word) == 0) //동일한 word를 찾으면 count 값을 +1, NULL을 리턴
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

void insert(treePointer* tree, char target[11]) //*tree는 트리의 시작지점을 가리키는 포인터
{
	treePointer ptr;
	treePointer temp = modifiedSearch(*tree, target);
	if (temp || !(*tree))
	{
		ptr = (treePointer)malloc(sizeof(node));
		ptr->data.count = 1;
		strcpy_s(ptr->data.word, 11, target);
		ptr->leftchild = ptr->rightchild = NULL;
		if (*tree) //*tree가 NULL이면 *tree가 가리키는 노드가 곧 ptr이 되어야한다.
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
	treePointer first = (treePointer)malloc(sizeof(node)); //초기 노드를 NULL로 초기화
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