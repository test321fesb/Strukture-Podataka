#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buffer (64)

typedef struct _Node
{
	int data;
	struct _Node* left;
	struct _Node* right;
} Node;
typedef struct _Node* Position;

int AddEl(Position);

int main()
{
	Node root;
	root.left = NULL;
	root.right = NULL;

	
	AddEl();
	return 0;
}

Position CreateNode(int var)
{
	Position temp = (Position)malloc(sizeof(Node));
	if (!temp)
	{
		printf("\n\tAllocation Error! ");
		return NULL;
	}
	else {
		temp->left = NULL;
		temp->right = NULL;
		temp->data = var;
		return temp;
	}
}

int AddEl(Position head)
{
	int i = 0;
	printf("\nUnesi element: ");
	sscanf("%d", &i);
	if (head->data == NULL)
	{
		head->data = i;
		return 0;
	}
	Position temp = CreateNode(i);
	if ()
}

Position FindElement(Position temp, int var)
{
	if()
}

int AddLeft(Position temp)
{

}

int AddRight()
