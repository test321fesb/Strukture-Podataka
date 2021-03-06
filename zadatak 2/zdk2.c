#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (32)

typedef struct _osoba
{
  char ime[MAX];
  char prezime[MAX];
  int godiste;
} osoba;

typedef struct _node
{
  osoba podatci;
  struct _node* next;
} node;

int DodajPocetak(node**);
int DodajKraj(node**);
int UnosPodataka(node*);
node* KreirajNode();
int PronalaziPrezime(node**);
int Ispis(node*);
int brisanje(node**);
int IspisiMenu();
int IspisiOsobu(node*);

int main()
{
    node* head = NULL;
    int input = -1;

    while(input != 0)
    {
        IspisiMenu();
        scanf("%d", &input);
        switch(input)
        {
        case 1:
            DodajPocetak(&head);
            break;
        case 2:
            DodajKraj(&head);
            break;
        case 3:
            brisanje(&head);
            break;
        case 4:
            PronalaziPrezime(&head);
            break;
        case 5:
            Ispis(head);
            break;
        default:
            printf("\n--Pogresan unos!--\n");
        }
    }

    return 0;
}

int UnosPodataka(node* Temp)
{
    printf("---Unesi podatke---\n(ime prezime godiste): ");
    scanf("%s %s %d", Temp->podatci.ime, Temp->podatci.prezime, &Temp->podatci.godiste);
    Temp->next = NULL;
    return 0;
}

node* KreirajNode()
{
    node* TempNode = (node*)malloc(sizeof(node));
    if(TempNode) {
      UnosPodataka(TempNode);
      return TempNode;
    }
    else {
        printf("Problem s alokacijom.");
        return NULL;
    }
}

int DodajPocetak(node** head)
{
    node* TempNode = KreirajNode();
    TempNode->next = (*head);
    (*head) = TempNode;
    return 0;
}

int DodajKraj(node** head)
{
    node* TempKraj = *head;

    node* TempNode = KreirajNode();

    if(*head == NULL){
      *head = TempNode;
      return 0;
    }

    while(TempKraj->next != NULL)
    {
        TempKraj=TempKraj->next;
    }

    TempKraj->next = TempNode;
    return 0;
}

int Ispis(node* head)
{
    node* TempIspis = head;

    puts("\n\t----------ISPIS-----------");

    while(TempIspis != NULL)
    {
      IspisiOsobu(TempIspis);
      TempIspis = TempIspis->next;
    }

    puts("\n\t--------------------------");

    return 0;
}


int PronalaziPrezime(node** head)
{
    node* TempNode = *head;
    char TempPrez[MAX];

    printf("\nUnesi trazeno prezime: ");
    scanf("%s", TempPrez);

    while(TempNode != NULL)
    {
      if ( strcmp(TempNode->podatci.prezime, TempPrez) == 0 ) {
        IspisiOsobu(TempNode);
        return 0;
      }
      TempNode=TempNode->next;
    }

    printf("Ne postoji trazena osoba. Unesite neku drugu.\n");
    return 0;
}

int brisanje(node** head)
{
    node* TempNode = *head;
    node* TempNodePrev;
    char TempPrez[MAX];

    if(TempNode == NULL) {
      printf("Lista je prazna.\n");
      return 0;
    }

    printf("\n\t-----BRISANJE-----\n\n\t Unesi prezime osobe: ");
    scanf("%s", TempPrez);

    if( strcmp(TempNode->podatci.prezime, TempPrez) == 0 )
    {
      *head = TempNode->next;
      free(TempNode);
      return 0;
    }

    while(TempNode != NULL)
    {
      if( strcmp(TempNode->podatci.prezime, TempPrez) == 0) {
        TempNodePrev->next = TempNode->next;
        free(TempNode);
        return 0;
      }

      TempNodePrev = TempNode;
      TempNode = TempNode->next;
    }

    printf("Ne postoji trazena osoba. Unesite neku drugu.\n");
    return 0;
}

int IspisiMenu()
{
    printf("\n--------------------");
    printf("\n------IZBORNIK------");
    printf("\n--------------------\n");
    printf(" 0 - Izlaz\n");
    printf(" 1 - Dodaj na pocetak\n");
    printf(" 2 - Dodaj na kraj\n");
    printf(" 3 - Brisanje osobe\n");
    printf(" 4 - Pronalazak\n");
    printf(" 5 - Ispis\n");
    printf("\nVas izbor: ");
}

int IspisiOsobu(node* Temp) {
  if(!Temp)
  {
    return -1;
  }
  printf("\n\t<%s %s %d>\n", Temp->podatci.ime, Temp->podatci.prezime, Temp->podatci.godiste);
  return 0;
}
