#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	int data;
	struct _node* next;
} node;

node* InputList ();
int InsertAtHead (node**,node*);
int InsertAtHead(node**, node*);
int InsertAtLocation (node*, node*);
node* CreateNode ();
int DataInput (node*);
int SortNode (node**,node*);
int CompareNodes (node*, node*);
int PrintList (node*);
node* Conjunction(node*, node*);
node* Disjunction(node*, node*);
int AddNode(node*, node*, node*);

int main()
{
	node L1, L2, LK, LD;
	L1.next = NULL;
	L2.next = NULL;
	LK.next = NULL;
	LD.next = NULL;
	L1.next = InputList();
	L2.next = InputList();
	LK.next = Conjunction(L1.next,L2.next);
	LD.next = Disjunction(L1.next,L2.next);
	
	printf("\nPrva Lista:\n\n");
    PrintList(L1.next);
    
	printf("\nDruga Lista:\n\n");
	PrintList(L2.next);
	
	printf("\nKonjunkcija: \n\n");
	PrintList(LK.next);
	/*
	printf("\nDisjunkcija: \n\n");
	PrintList(LD.next);
	*/
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
	    DataInput(temp);
		SortNode(&head, temp);
	}
	return head;
}

int InsertAtHead(node** head, node* temp)
{
	if ((*head) == NULL)
	{
		(*head) = temp;
		return 1;
	}
	temp->next = (*head);
	(*head)= temp;
	return 0;
}

int InsertAtEnd(node** head, node* temp)
{
    node* tempNode = *head;
    if((*head)==NULL)
    {
        (*head) = temp;
        return 1;
    }
    while(tempNode->next!=NULL) tempNode=tempNode->next;
    tempNode->next = temp;
    return 0;
}

int InsertAtLocation(node* location,node* temp)
{
    temp->next = location->next;
    location->next = temp;
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
	return temp;
}

int DataInput(node* temp)
{
    printf("\nUnesi clan: ");
	scanf("%d", &temp->data);
	return 0;
}

int SortNode(node** head, node* temp)
{
    node* tempNode = (*head);
    node* tempTarget = NULL;
    if((*head)==NULL)
    {
        InsertAtHead(head,temp);
        return 3;
    }
    while(tempNode!=NULL)
    {
        if(CompareNodes(temp,tempNode)==1)
        {
            tempTarget = tempNode;
            tempNode=tempNode->next;
        }
        else if(CompareNodes(temp,tempNode)==0) return 2;
        else
        {
            if(tempNode==(*head)) InsertAtHead(head,temp);
            else InsertAtLocation(tempTarget,temp);
            return 1;
        }
    }
    InsertAtLocation(tempTarget,temp);
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
    while(temp != NULL)
    {
        printf("%d ",temp->data);
        temp = temp->next;
    }
    return 0;
}

node* Conjunction(node* head1, node* head2)
{
    node* head = NULL;
    node* temp = NULL;
    node* tempNode1 = head1;
    node* tempNode2 = head2;
    
    while(tempNode1!=NULL || tempNode2!=NULL)
    {
        if(CompareNodes(tempNode1,tempNode2)==1)
        {
            AddNode(head,temp,tempNode2);
        }
        else if(CompareNodes(tempNode1,tempNode2)==0)
        {
            tempNode1 = tempNode1->next;
            tempNode2 = tempNode2->next;
        }
        else {
            AddNode(head,temp,tempNode1);
        }
    }
    if(tempNode1 == NULL)
        while(tempNode2!=NULL)
            AddNode(head,temp,tempNode2);
    if(tempNode2 == NULL)
        while(tempNode1!=NULL)
            AddNode(head,temp,tempNode1);
    
    return NULL;
    
}

node* Disjunction(node* head1, node* head2)
{
    return NULL;
}

int AddNode(node* head, node* temp, node* tempNode)
{
    temp = CreateNode();
    temp->data = tempNode->data;
    InsertAtEnd(&head,temp);
    tempNode = tempNode->next;
    return 0;
}
