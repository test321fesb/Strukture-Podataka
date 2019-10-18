#include <stdio.h>
#include <stdlib.h>
#define Konst (32)

typedef struct _osoba* Pozicija;
typedef struct _osoba
{
    char ime[Konst];
    char prezime[Konst];
    int GodRod;
    Pozicija next;
}osoba;

void Ispis(Pozicija);
void UpisP(Pozicija);

int main()
{
    osoba OS;
    Pozicija OSLok = NULL;
    OS.next = NULL;
    
    //test -------------
    
    int i=0;
    
    while(i != 3)
    {
        UpisP(&OS);
        i++;
    }
    
    Ispis(OS.next);
    
    //kraj testa -------------

    return 0;
}
void UpisP(Pozicija P)
{
    Pozicija Temp = NULL;
    Temp=(Pozicija)malloc(sizeof(osoba));
    
    
    printf("Unesi ime: ");
    scanf("%s",Temp->ime);
    printf("Unesi prezime: ");
    scanf("%s",Temp->prezime);
    printf("Unesi godinu rodenja: ");
    scanf("%d",&Temp->GodRod);
    
    Temp->next=P->next;
    P->next = Temp;
}
void Ispis(Pozicija P)
{
    while (P != NULL)
		{
			printf("%s %s %d\n", P->ime, P->prezime, P->GodRod);
			P = P->next;
		}
}