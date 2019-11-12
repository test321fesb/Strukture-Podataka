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
int InsertAtEnd (node** head, node* new);

int printPolynom (node*);

node sumOfPolynoms (node, node);

node productOfPolynoms (node, node);

int SortNode(node**, node*);

int FindGreatestPower (node** head);

node MergeInsidePolynom(node*);

int MultiplyWithAndStore (node* member, node* multiplyWith, node** store);

int main()
{
	FILE *ulz = NULL;
	char row[ROW_MAX];

	node HeadP1, HeadP2, HeadSum, HeadProduct;
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

	printf("\nZbroj\n");
	HeadSum = sumOfPolynoms(HeadP1, HeadP2);
	printPolynom(&HeadSum);

	printf("\nUmnozak\n");
	HeadProduct = productOfPolynoms(HeadP1, HeadP2);
	printPolynom(&HeadProduct);



	return 0;
}

node* CreatePolynom(char* row)
{
	int c = 0, p = 0, offset = 0;
	node* temp = NULL;
	node* polynom = NULL;

	while( sscanf(row, "%d %d%n", &c, &p, &offset) != EOF) {
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

int InsertAtEnd(node** head, node* new)
{
	node* temp = *head;
	if(*head == NULL) {
		*head = new;
		return 0;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;

	if(temp) return 0;
	else return -1;
}

int printPolynom (node* head) {
	node* temp = head->next;
	if(head == NULL) {                          //head->next?
		printf("Error: prazna lista!");
		return -1;
	}

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
    while(TempNode != NULL)
    {
        if(temp->data.power > TempNode->data.power)
					SwapNodes(TempNode,temp);
        TempNode = TempNode->next;
        temp = temp->next;
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

node sumOfPolynoms (node HeadP1, node HeadP2) {
	node* temp = NULL;
	node* polynom = HeadP1.next;
  node* temp2 = HeadP2.next;
	InsertAtEnd(&polynom, temp2);
	*polynom = MergeInsidePolynom(polynom);
	return *polynom;

}

node productOfPolynoms (node HeadP1, node HeadP2) {
	node* temp = HeadP1.next;
	node* polynom = NULL;
  node* temp2 = HeadP2.next;

	while(temp != NULL)
	{
		MultiplyWithAndStore(temp, temp2, &polynom);

		temp = temp->next;
	}
  *polynom = MergeInsidePolynom(polynom);
  return *polynom;
}

int MultiplyWithAndStore (node* member, node* multiplyWith, node** store)
{
	node* new = NULL;
	node* temp = multiplyWith;
	while(temp != NULL) {
    new = CreateNode(member->data.coefficient * temp->data.coefficient, member->data.power + temp->data.power);
		InsertAtHead(store, new);
    temp = temp->next;
	}
  return 0;
}

node MergeInsidePolynom (node* head)
{
	int x = FindGreatestPower(&head);
	int i = 0;
	int c = 0;
	node* temp = head;
	node* new = NULL;
	node* polynom = NULL;

	for(i=0; i<=x; i++)
	{
		while(temp != NULL) {
			if(temp->data.power == i)
				c = c + temp->data.coefficient;

			temp = temp->next;
		}
		new = CreateNode(c, i);
		InsertAtHead(&polynom, new);

		// hardcode test
		if(i == x)
			{
				new = CreateNode(c, i);
				InsertAtHead(&polynom, new);
			}

		temp = head;
		c = 0;
	}

	return *polynom;
}

int FindGreatestPower (node** head)
{
	node* temp = (*head)->next;
	int x = 0;
	while(temp != NULL)
	{
		if(temp->data.power > x)
			x = temp->data.power;
		temp = temp->next;
	}
	return x;
}
