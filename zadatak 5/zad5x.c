#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (32)
#define MAX_ROW (128)

typedef struct _node
{
	int data;
	struct _node* next;
} node;

int InsertAtEnd(node**, node*);
int UnosPodataka(node*);
node* KreirajNode();
int Ispis(node*);
int IspisiOsobu(node*);

/*
int sortiranje(node**);
int zamijeni(node*, node*);
int provjeraZamjene(node*);
*/

node* Intersection (node*, node*);
node* Union(node*, node*);
int ExistsIn(node*, node**);

int main()
{
	node* head1 = NULL;
	node* head2 = NULL;
	node* head3 = NULL;
	node* head4 = NULL;

	node* tempNode1 = NULL;
	node* tempNode2 = NULL;

	int x = 0, i = 0, a = 0;
	node* TempNode;

	scanf("%d", &x);
	for(i=0; i<x; i++)
	{
		TempNode = KreirajNode();
		InsertAtEnd(&head1, TempNode);
	}
	scanf("%d", &x);
	for(i=0; i<x; i++)
	{
		TempNode = KreirajNode();
		InsertAtEnd(&head2, TempNode);
	}

	Ispis(head1);
	Ispis(head2);

	tempNode1 = head1;
	tempNode2 = head2;

	while(tempNode1->next != NULL)
	{
			if(ExistsIn(tempNode1, &head2)) {
				InsertAtEnd(&head3, tempNode2);
			}
			tempNode1 = tempNode1->next;
	}

		Ispis(head3);

		/*
	head4 = Union(head1, head2);
		Ispis(head4);
*/





	return 0;
}

int UnosPodataka(node* Temp)
{
	printf("---Unesi broj---\n");
	scanf("%d", &Temp->data);
	Temp->next = NULL;
	return 0;
}

node* KreirajNode()
{
	node* TempNode = (node*)malloc(sizeof(node));
	if (TempNode) {
		UnosPodataka(TempNode);
		return TempNode;
	}
	else {
		printf("Problem s alokacijom.");
		return NULL;
	}
}

int InsertAtEnd(node** head, node* TempNode)
{
	node* TempKraj = *head;

	if (*head == NULL) {
		*head = TempNode;
		return 0;
	}

	while (TempKraj->next != NULL)
	{
		TempKraj = TempKraj->next;
	}

	TempKraj->next = TempNode;

	return 0;
}

int Ispis(node* head)
{
	node* TempIspis = head;

	puts("\nIspis\n");

	while (TempIspis != NULL)
	{
		IspisiOsobu(TempIspis);
		TempIspis = TempIspis->next;
	}

	puts("\n");

	return 0;
}

int IspisiOsobu(node* Temp) {
	if (!Temp)
	{
		return -1;
	}
	printf("%d ", Temp->data);
	return 0;
}

/*
int sortiranje(node** head) {
  int zamijenjen = 1;
  node *temp;
  node *najveciTemp = NULL;

  if (*head == NULL) {
      printf("Lista prazna.\n");
      return 1;
  }

  while (zamijenjen) {
    temp = *head;
    zamijenjen = 0;

    while (temp->next != najveciTemp)
      {
          zamijenjen = provjeraZamjene(temp);
          temp = temp->next;
      }

      najveciTemp = temp;

  }

  printf("Lista je sortirana.\n");
  return 0;
}

int provjeraZamjene (node* temp) {
  if ( strcmp(temp->podatci.prezime, temp->next->podatci.prezime) > 0 )
  {
    zamijeni(temp, temp->next);
    return 1;
  }
  else {
    return 0;
  }
}

int zamijeni(node* a, node * b)
{
  osoba temp = a->podatci;
  a->podatci = b->podatci;
  b->podatci = temp;
}

*/

node* Intersection(node* head1, node* head2)
{
    node* head = NULL;
    node* tempNode1 = head1;
    node* tempNode2 = head2;
    while(tempNode1 != NULL)
    {
				if(ExistsIn(tempNode1, &head2)) {
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
    while(tempNode1 != NULL)
    {
        InsertAtEnd(&head, tempNode1);
        tempNode1 = tempNode1->next;
    }
    while(tempNode2 != NULL)
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
