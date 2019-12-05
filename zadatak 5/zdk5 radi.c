#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node* position;
typedef struct _node
{
    int data;
    position next;
} node;

int LoadList (position);
int PrintOut (position);

position CreateNode();
int AddData (position);

int InsertAtHead (position, position);
int InsertAtPosition (position, position);

int SortNode (position, position);
int CompareNodes (position, position);

int Union (position,position,position);
int Intersection (position,position,position);

int main()
{
    node head1;
    node head2;
    node headU;
    node headI;
    head1.next = NULL;
    head2.next = NULL;
    headU.next = NULL;
    headI.next = NULL;
    
    printf("\n\tUnos 1. liste!\n");
    LoadList(&head1);
    printf("\n\tUnos 2. liste!\n");
    LoadList(&head2);
    
    printf("\n\tIspis 1. liste!\n");
    PrintOut(head1.next);
    printf("\n\tIspis 2. liste!\n");
    PrintOut(head2.next);
    
    Union(&headU,&head1,&head2);
    printf("\n\tIspis Unije!\n");
    PrintOut(headU.next);
    
    Intersection(&headI,&head1,&head2);
    printf("\n\tIspis Presjeka!\n");
    PrintOut(headI.next);
    
    
    return 0;
}

int LoadList(position head)
{
    int n = 0, i = 0;
    
    printf("\nUnesi broj clanova liste: ");
    scanf("%d",&n);
    
    for(i = 0; i < n; i++)
    {
        position temp = NULL;
        temp = CreateNode();
        AddData(temp);
        SortNode(head,temp);
    }
    return 0;
}

position CreateNode()
{
    position temp = (position)malloc(sizeof(node));
    if(temp == NULL)
    {
        printf("\n\tMemory Allocation Error\n");
        return NULL;
    }
    else{
        temp->next = NULL;
        return temp;
    }
}

int AddData(position temp)
{
    printf("\nUnesi broj: ");
    scanf("%d",&temp->data);
    return 0;
}

int InsertAtHead(position head, position temp)
{
    if(head->next==NULL)
    {
        head->next = temp;
        return 1;
    }
    
    temp->next = head->next;
    head->next = temp;
    
    return 0;
}

int PrintOut(position head)
{
    position temp = head;
    while(temp!=NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    return 0;
}

int SortNode(position head, position tempNode)
{
    position temp = head;
    int input = 0;
    if(head->next==NULL)
    {
        InsertAtPosition(head,tempNode);
        return 1;
    }
    while(temp->next!=NULL)
    {
        input = CompareNodes(tempNode,temp->next);
        if(input==0){
            free(tempNode);
            return 2;
        }
        else if(input==1) temp=temp->next;
        else{
            InsertAtPosition(temp,tempNode);
            return 3;
        }
    }
    InsertAtPosition(temp,tempNode);
    return 0;
}

int CompareNodes(position node1, position node2)
{
    if(node1->data == node2->data) return 0;
    else if(node1->data > node2->data) return 1;
    else return -1;
}

int InsertAtPosition(position location, position node)
{
    node->next = location->next;
    location->next = node;
    return 0;
}

int Union(position headU, position Head1, position Head2)
{   
    position tempNode = NULL;
    position temp = NULL;
    temp = Head1->next;
    int input = 0;
    
    while(input != 2)
    {
    while(temp!=NULL)
    {
        position tempNode = NULL;
        tempNode = CreateNode();
        tempNode->data = temp->data;
        SortNode(headU,tempNode);
        temp=temp->next;
    }
    temp = Head2->next;
    input++;
    }
    return 0;
}

int Intersection(position headI, position Head1, position Head2)
{
    position temp1 = Head1->next;
    position temp2 = Head2->next;
    position location = headI;
    int input = 0;
    
    while(temp1!=NULL && temp2!=NULL)
    {
        input = CompareNodes(temp1,temp2);
        if(input == 0)
        {
            position temp = CreateNode();
            temp->data = temp1->data;
            InsertAtPosition(location,temp);
            location=location->next;
            temp1=temp1->next;
            temp2=temp2->next;
        }
        else if(input==1) temp2=temp2->next;
        else temp1=temp1->next;
    }
    return 0;
}
