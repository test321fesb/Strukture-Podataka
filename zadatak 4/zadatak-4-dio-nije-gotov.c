#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW_MAX (128)

int Global = 0;

typedef struct _member
{
	int coefficient;
	int power;
} member;

typedef struct _node
{
	member data;
	struct _node* next;
} node;


int AddDataToNode(node*);
node* AllocateNode();
int SwapNodes(node* , node*);
int CompareNodes(node*, node*);
int SortNumber(node*, node*);

node* CreateNode (int c, int p);

node* CreatePolynom(char*);

int InsertAtHead (node** head, node* new);

int printPolynom (node*);

int main()
{
	FILE *ulz = NULL;
	char row[ROW_MAX];

	node HeadP1, HeadP2;
	HeadP1.next = NULL;
	HeadP2.next = NULL;

	ulz = fopen("polinomi.txt", "r");
	if (ulz == NULL)
	{
		printf("\n\tError 124-5: Document Error!\n");
	}

	fgets(row, ROW_MAX, ulz);

	printf("\nPrvi\n");
	HeadP1.next = CreatePolynom(row);
	printPolynom(&HeadP1);

	fgets(row, ROW_MAX, ulz);

	printf("\nDrugi\n");
	HeadP2.next = CreatePolynom(row);
	printPolynom(&HeadP2);


	return 0;
}

node* CreatePolynom(char* row)
{
	int c = 0, p = 0, offset = 0;
	node* temp = NULL;
	node* polynom = NULL;

	while( sscanf(row, "%d %d%n", &c, &p, &offset)!=EOF) {
		temp = CreateNode(c, p);
		InsertAtHead(&polynom, temp);
		SortNode(&polynom, temp);
		row = row + offset;
	}

	return polynom;
}

node* CreateNode (int c, int p) {

	node* Temp = AllocateNode();
	Temp->data.coefficient = c;
	Temp->data.power = p;
	Temp->next = NULL;

	if (Temp)
		return Temp;
	else
		return NULL;
}

node* AllocateNode()
{
	node* Temp = (node*)malloc(sizeof(node));
	if(Temp == NULL)
	{
		printf("\n\tError 124-6: Memory Allocation Error!\n");
		return NULL;
	}
  else
		return Temp;
}

int InsertAtHead(node** head, node* new)
{
	if(*head == NULL) {
		*head = new;
		return 0;
	}
	new->next=(*head);
	(*head)=new;
	
	if(*head) return 0;
	else return -1;
}

int printPolynom (node* head) {
	node* temp = head->next;
	if(head == NULL) {                          //head->next?
		printf("Error: prazna lista!");
		return -1;
	}

	printf("\nPolinom: ");
	while (temp != NULL)
	{
		printf("%dx^%d", temp->data.coefficient, temp->data.power);
		if (temp->next != NULL)
			printf(" + ");
		temp = temp->next;
	}

	return 0;
}

int SortNode(node** head, node* temp)
{
    node* TempNode = (*head)->next;
    while(TempNode!=NULL)
    {
        if(temp->data.power>TempNode->data.power) SwapNodes(TempNode,temp);
        TempNode=TempNode->next;
        temp=temp->next;
    }
    return 0;
}

int SwapNodes(node* TempNode, node* SortNode)
{
    member Temp = TempNode->data;
    TempNode->data = SortNode->data;
    SortNode->data = Temp;
    return 0;
}

/*

int SortNumber(node* head, node* SortNode)
{
    head=SortNode;
    SortNode->next = NULL;
    node* TempNode=head;

		#if 0
    if(head==NULL){
        SortNode->next=NULL;
        head=SortNode;
        return 1;
    }
		#endif

    while(TempNode!=NULL){
        CompareNodes(TempNode,SortNode);
        TempNode=TempNode->next;
    }
    return 0;
}

int CompareNodes(node* TempNode, node* SortNode)
{
    if (SortNode->data.power > TempNode->data.power)
    {
        SwapNodes(TempNode, SortNode);
        return 1;
    }
    return 0;
}

int SwapNodes(node* TempNode, node* SortNode)
{
    polynom Temp = TempNode->data;
    TempNode->data = SortNode->data;
    SortNode->data = Temp;
    return 0;
}

int PrintBothPolynoms(node* HeadP1, node* HeadP2)
{
    node* TempNode = HeadP1;
    int PolynomNumber=1;

    while(TempNode!=NULL)
    {
        printf("%dx^%d",TempNode->data.coefficient,TempNode->data.power);
        TempNode=TempNode->next;
        if(TempNode == NULL){
            printf("\n");
            if(PolynomNumber = 1){
                PolynomNumber = 2;
                TempNode=HeadP2;
            }
            continue;
        }
        puts(" + ");
    }
}

*/
