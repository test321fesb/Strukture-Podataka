#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	int data;
	struct _node* next;
} node;

node* InputList ();
node* CreateNode ();
int InsertAtEnd(node**);

int main()
{
	node L1, L2;
	L1.next = NULL;
	L2.next = NULL;
	L1.next = InputList();
	node* TEMP = &L1;
	TEMP = TEMP->next;
	int i = 0;

	for (i = 0; i < 4; i++)
	{
		printf("%d ", TEMP->data);
		TEMP = TEMP->next;
	}
	scanf("%d", &i);
	return 0;
}

node* InputList()
{
	int brojClanova = 0, i = 0;

	node* head = NULL;

	printf("\nUnesi broj clanova: ");
	scanf("%d", &brojClanova);
	for (i = 0; i < brojClanova; i++)
	{
		InsertAtEnd(&head);
	}
	return head;
}

int InsertAtEnd(node** head)
{
	node* tempNode = *head;
	node* temp = CreateNode();
	temp->next = NULL;
	if ((*head) == NULL)
	{
		(*head) = temp;
		return 1;
	}
	while (tempNode -> next != NULL)
		tempNode = tempNode->next;
	tempNode -> next = temp;
	return 0;
}

node* CreateNode() 
{
	node* temp = (node*)malloc(sizeof(node));
	if (temp == NULL)
	{
		printf("\n\tError 124-6: Memory Allocation Error!\n");
		return NULL;
	}
	printf("\nUnesi clan: ");
	scanf("%d", &temp->data);
	return temp;
}
