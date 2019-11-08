#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ROW_MAX (128)

typedef struct _polynom
{
	int coefficient;
	int power;
}polynom;
typedef struct _node
{
	polynom data;
	struct _node* next;
}node;

int LoadPolynom(node*);

int main()
{
	node HeadP1;
	HeadP1.next=NULL;
	node HeadP2;
	HeadP2.next=NULL;
}
node* CreateNode(node* head)
{
	node* Temp = (node*)malloc(sizeof(node));
	if(Temp == NULL)
	{
		printf("\n\tError 124-6: Memory Allocation Error!\n");
		return NULL;
	}
	
	else 
	{	
		Temp = AddDataToNode(node* Temp);
		return Temp;
	}
	
}

node* AddDataToNode(node* Temp)
{
	Temp->next=NULL;
}

int LoadPolynom(node* head)
{
	FILE *ulz;
	
	char row[ROW_MAX];
	
	ulz = fopen("polinomi.txt","r");
	if(ulz == NULL)
	{
		printf("\n\tError 124-5: Document Error!\n");
		return -1;
	}

	CreateNode(

	fscanf(ulz,"%d %d",



}
