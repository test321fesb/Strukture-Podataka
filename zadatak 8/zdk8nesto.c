#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFA (64)

typedef struct _Node
{
	char data[BUFFA];
	struct _Node* child;
	struct _Node* sibling;
} Node;

typedef struct _Node* Position;

typedef struct _Dir
{
	char data[BUFFA];
	struct _Dir* next;

} Dir;

typedef struct _Dir* ptr;

Position CreateNode();
int AddData(Position);
int Birth(Position);
int Adoption(Position, Position);
int Menu();



int main()
{
	Node root;
	root.child = NULL;
	root.sibling = NULL;

	Menu(&root);










	CommandPrompt();


	getchar();

	return 0;
}

int Menu(Position curr)
{
	int input = -2;
	char check[10];
	do
	{
		fgets(check, 10, stdin);
		if (strcmp(check, "md") == 0)
		{
			Birth(curr);
			continue;
		}
		if (strcmp(check, "cd dir") == 0)
		{

		}
		if (strcmp(check, "cd..") == 0) input = 3;
		if (strcmp(check, "dir") == 0) input = 4;
		if (strcmp(check, "exit") == 0) input = 5;
		printf("'clear' is not recognized as an internal or external command, operable program or batch file.");
	} while (input != 5);
}

int CommandPrompt()
{
	printf("Microsoft Windows[Version 10.0.10240]\n(c) 2015 Microsoft Corporation.All rights reserved.\n");
	return 0;
}

Position CreateNode()
{
	Position temp = (Position)malloc(sizeof(Node));
	if (!temp)
	{
		printf("\n\tError!\n");
		return NULL;
	}
	else return temp;
}

int AddData(Position curr)
{
	return fgets(curr->data, BUFFA, stdin);
}

int Birth(Position curr)							//     <- birth
{
	Position temp = CreateNode();
	AddData(temp);
	if(curr->child == NULL) curr->child = temp;
	else Adoption(curr->child, temp);

	return 0;
}

int Adoption(Position curr, Position temp)
{
	Position tempNode = curr;

	if (curr->sibling == NULL)
	{
		curr->sibling = temp;
		return 1;
	}
	while (tempNode->sibling != NULL)
		tempNode = tempNode->sibling;
	tempNode->sibling = temp;
	return 0;
}

int Pedo()
{

}
