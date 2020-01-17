#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MID (32)
#define NUM (11)

typedef struct _Node* Position;
typedef struct _Node
{
	char name[MID];
	char surname[MID];
	int ID;
	Position next;
} Node;

typedef struct _Table* TablePtr;
typedef struct _Table
{
	int numElem;
	Position list_next;
} Table;


TablePtr CreateTable();
Position CreateNode();
int AddData(Position);
int CreateStudent(TablePtr);
int GetNumber(char[MID]);
int ImportStudent(TablePtr, Position, int);
int Sort(TablePtr, Position);
Position FindPrev(TablePtr, Position);
int InsertAtHead(TablePtr, Position);
int InsertAtLocation(Position, Position);
int PrintTable(TablePtr);
int Print();


int main()
{
	TablePtr head = NULL;
	head = CreateTable();

	int input = 0;
	do {
		Print();
		scanf(" %d", &input);
		switch (input)
		{
		case 1:
			CreateStudent(head);
			break;
		case 2:
			PrintTable(head);
			break;
		case 0:
			break;
		default:
			input = -1;
			break;
		}
	} while (input != 0);

	printf("\n\tdone");

	return 0;
}

int Print()
{
	printf("\n\n\t-----MENI-----\n");
	printf("\n\t1 - Unesi studenta");
	printf("\n\t2 - Ispis Tablice");
	printf("\n\t0 - Izlaz\n");
	printf("\n\tVas izbor: ");
	return 0;
}

TablePtr CreateTable()
{
	TablePtr headTable = (TablePtr)malloc(NUM * sizeof(Table));
	int i = 0;
	do
	{
		(headTable+i*(sizeof(Table)))->list_next = NULL;
		i++;
	} while (i != 11);
	return headTable;
}

Position CreateNode()
{
	Position temp = (Position)malloc(sizeof(Node));
	if (temp == NULL)
	{
		printf("\n\tallocation error!\n\n");
		return NULL;
	}
	else
	{
		temp->next = NULL;
		return temp;
	}
}

int AddData(Position node)
{
	getchar();
	printf("\n\t---PODATCI---\n\tUnesi ime: ");
	fgets(node->name, MID, stdin);
	node->name[strlen(node->name) - 1] = '\0';
	printf("\n\tUnesi prezime: ");
	fgets(node->surname, MID, stdin);
	node->surname[strlen(node->surname) - 1] = '\0';
	printf("\n\tUnesi maticni broj: ");
	scanf(" %d", &node->ID);
	return 0;
}

int CreateStudent(TablePtr head)
{
	int data = 0;
	Position stud = CreateNode();
	AddData(stud);
	data = GetNumber(stud->name);
	ImportStudent(head, stud, data);
	return 0;
}

int GetNumber(char data[MID])
{
	int i = 0, number = 0;
	do {
		number = number + data[i];
		i++;
	} while (i != 5);
	return (number % 11);
}

int ImportStudent(TablePtr head, Position stud, int data)
{
	TablePtr temp = (head + data*sizeof(Table));
	Sort(temp, stud);
	return 0;
}

int Sort(TablePtr current, Position stud)
{
	if (current->list_next == NULL)
	{
		current->list_next = stud;
		return 0;
	}
	else
	{
		Position prev = FindPrev(current, stud);
		if (prev == NULL) InsertAtHead(current, stud);
		else InsertAtLocation(prev, stud);
		return 0;
	}
}

Position FindPrev(TablePtr current, Position stud)
{
	Position tempPrev = NULL;
	Position tempNode = current->list_next;
	do {
		if (strcmp(stud->surname, tempNode->surname) > 0)
		{
			tempPrev = tempNode;
			tempNode = tempNode->next;
		}
		else return tempPrev;
	} while (tempNode != NULL);
	return tempPrev;
}

int InsertAtHead(TablePtr current, Position stud)
{
	stud->next = current->list_next;
	current->list_next = stud;
	return 0;
}

int InsertAtLocation(Position prev, Position stud)
{
	stud->next = prev->next;
	prev->next = stud;
	return 0;
}

int PrintTable(TablePtr head)
{
	TablePtr tempStart = head;
	Position tempNode = tempStart->list_next;
	int i = 0;
	do {
		printf("\nRed [%d]", i + 1);
		if (tempNode == NULL) printf("\t\tEmpty!");
		else {
			while (tempNode != NULL)
			{
				printf("\t\t%s\t%s\t%d", tempNode->name, tempNode->surname, tempNode->ID);
				printf("\n");
				tempNode = tempNode->next;
			}
		}
		printf("\n");
		i++;
		tempStart = head + (i*sizeof(Table));
		tempNode = tempStart->list_next;
	} while (i != 11);
	return 0;
}
