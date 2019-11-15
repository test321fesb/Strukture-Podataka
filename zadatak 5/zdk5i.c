#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	int data;
	struct _node* next;
} node;

node* InputList ();
int InsertAtHead (node**, node*);
int InsertAtEnd (node**, node*);
node* CreateNode ();
int DataInput (node*);
int CompareNodes (node*, node*);
int PrintList (node*);
node* Intersection (node*, node*);
node* Union(node*, node*);
int ExistsIn(node*, node**);

int main()
{

	node L1, L2, LI, LU;
	L1.next = NULL;
	L2.next = NULL;
	LI.next = NULL;
	LU.next = NULL;
	L1.next = InputList();
	L2.next = InputList();
	LI.next = Intersection (L1.next, L2.next);
	LU.next = Union (L1.next, L2.next);

	printf("\n_______________________\nPrva Lista:\n");
  PrintList(L1.next);

	printf("\n\nDruga Lista:\n");
	PrintList(L2.next);

	printf("\n\nPresjek: \n");
	PrintList(LI.next);

	printf("\n\nUnija: \n");
	PrintList(LU.next);

	return 0;
}

node* InputList()
{
	int numberOfElements = 0, i = 0;

	node* head = NULL;

	printf("\nUnesi broj clanova: ");
	scanf("%d", &numberOfElements);

	for (i = 0; i < numberOfElements; i++)
	{
    node* temp = CreateNode();
		InsertAtEnd(&head, temp);
	}

	return &head;
}

int InsertAtHead(node** head, node* temp)
{
	if (*head == NULL)
	{
		*head = temp;
		return 1;
	}
	temp->next = *head;
	*head = temp;
	return 0;
}

int InsertAtEnd(node** head, node* temp)
{
    node* tempNode = *head;

		node* tempX = temp;

    if(*head == NULL)
    {
        *head = tempX;
        return 1;
    }
    while(tempNode->next!=NULL)
			tempNode=tempNode->next;
    tempNode->next = tempX;

		printf("\n___\n");
		PrintList(*head);
		printf("\n___\n");
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
	temp->next = NULL;
	DataInput(temp);
	return temp;
}

int DataInput(node* temp)
{
  printf("\nUnesi clan: ");
	scanf("%d", &temp->data);
	return 0;
}

int CompareNodes(node* node1, node* node2)
{
    if(node1->data > node2->data) return 1;
    else if(node1->data == node2->data) return 0;
    else return -1;
}

int PrintList(node* head)
{
    node* temp = head;
		if(head == NULL) {
			printf("\nPrazna lista\n");
			return -1;
		}
    while(temp->next != NULL)
    {
        printf("%d ",temp->next->data);
        temp = temp->next;
    }
    return 0;
}

node* Intersection(node* head1, node* head2)
{
    node* head = NULL;
    node* tempNode1 = head1;
    node* tempNode2 = head2;
    while(tempNode1 != 0)
    {
				if(!ExistsIn(tempNode1, &head2)) {
        	InsertAtEnd(&head, tempNode2);
				}
        tempNode1 = tempNode1->next;
    }
    return head;
}

node* Union(node* head1, node* head2)
{
    node* head = NULL;
    node* tempNode1 = head1;
    node* tempNode2 = head2;
    while(tempNode1 != 0)
    {
        InsertAtEnd(&head, tempNode1);
        tempNode1 = tempNode1->next;
    }
    while(tempNode2 != 0)
    {
				if(!ExistsIn(tempNode2, &head)) {
        	InsertAtEnd(&head,tempNode2);
				}
        tempNode2 = tempNode2->next;
    }
    return head;
}

int ExistsIn (node* n, node** head) {
	int check = 0;
	node* temp = *head;

	while(temp != NULL) {
		if(temp->data == n->data) {
			check = 1;
		}
		temp = temp->next;
	}

	return check;
}
