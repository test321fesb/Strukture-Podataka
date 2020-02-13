#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (128)
#define BUFF (1024)

typedef struct _Word* WordPosition;
typedef struct _Word
{
	char word[MAX];
	WordPosition next;
} Word;

typedef struct _Node* Position;
typedef struct _Node
{
	char firstName[MAX];
	char lastName[MAX];
	WordPosition word;
	Position left;
	Position right;
} Node;


int ReadFile(Position);
int Tree(Position, Position);
int CreateSentence(Position, char*);
int InsertAtEnd(Position, WordPosition);
Position CreateNode();
WordPosition CreateWord();
int PrintTree(Position, int);
int StartTree(Position, Position);


int main()
{
	Node root;
	root.left = NULL;
	root.right = NULL;
	root.word = NULL;
	strcpy(root.lastName," ");

	ReadFile(&root);
	PrintTree(&root, 0);

	system("pause");
	return 0;
}

int ReadFile(Position root)
{
	FILE* ulz;
	Position person;
	int n = 0;
	char* buffer = (char*)malloc(BUFF*sizeof(char));
	ulz = fopen("quotes.txt", "r");

	if(ulz == NULL) return 0;

	while(!feof(ulz))
	{
		fgets(buffer, BUFF, ulz);
		person = CreateNode();
		sscanf(buffer,"%s %s %n",person->firstName, person->lastName, &n);
		buffer = buffer + n;
		CreateSentence(person, buffer);
		printf("AAAAAAA");
		StartTree(root, person);
	}
	fclose(ulz);
	return 0;
}

int StartTree(Position root, Position person)
{
	if(strcmp(root->lastName, " ") == 0)
	{
		root = person;
		return 0;
	}
	Tree(root, person);
	return 0;
}

int Tree(Position location, Position person)
{
	if(strcmp(location->lastName,person->lastName)>0)
	{
		if(location->left == NULL)
		{
			location->left = person;
			return 0;
		}
		Tree(location->left, person);
	}
	else
	{
		if(strcmp(location->lastName, person->lastName)<0)
		{
			if(location->right == NULL)
			{
				location->right = person;
				return 0;
			}
			Tree(location->right, person);
		}
		else
		{
			if(strcmp(location->firstName, person->firstName)>0)
			{
				if(location->left == NULL)
				{
					location->left = person;
					return 0;
				}
				Tree(location->left, person);
			}
			else
			{
				if(location->right == NULL)
				{
					location->right = person;
					return 0;
				}
				Tree(location->right, person);
			}
		}
	}
	return 0;
}

int PrintTree(Position location, int n)
{
	int i = 0;
	if(location->right != NULL)
		PrintTree(location->right, n+1);
	printf("\n");
	for(i = 0; i < n; i++) printf("\t");
	printf("%s %s\n",location->firstName, location->lastName);
	if(location->left != NULL)
		PrintTree(location->left, n+1);
	return 0;
}

int CreateSentence(Position person, char* buffer)
{
	int n = -1;
	WordPosition temp;
	while(n!=1)
	{
		temp = CreateWord();
		sscanf(buffer, "%s %n", temp->word, &n); 
		if(n == 1)
			break;
		InsertAtEnd(person, temp);
		buffer = buffer + n;
	}
	return 0;
}

int InsertAtEnd(Position person, WordPosition wrd)
{
	WordPosition temp = person->word;
	if(person->word == NULL)
	{
		person->word = wrd;
		return 0;
	}
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = wrd;
	return 0;
}

WordPosition CreateWord()
{
	WordPosition temp = (WordPosition)malloc(sizeof(Word));
	if(temp == NULL)
	{
		printf("\n\tAllocation Error!\n\n");
		return NULL;
	}
	else
	{
		temp->next = NULL;
		return temp;
	}
}

Position CreateNode()
{
	Position temp = (Position)malloc(sizeof(Node));
	if(temp == NULL)
	{
		printf("\n\tAllocation Error!\n\n");
		return NULL;
	}
	else
	{
		temp->left = NULL;
		temp->right = NULL;
		temp->word = NULL;
		return temp;
	}
}
