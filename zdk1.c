#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (20)
#define MAX_ROW (100)

typedef struct _student
{
  int bod;
  char ime[20];
  char prezime[20];
} student;

int brojRedova(char[MAX]);

int main () {
    float aps;
    int br=0,i=0,max=0;
    char FileName[MAX] = "studenti.txt";
    student S;
    FILE *ulz;
    student* niz = NULL;

    br = brojRedova(FileName);
    niz = (student*)malloc(br * sizeof(student));

    ulz = fopen("studenti.txt", "r");
    rewind(ulz);

     while(!feof(ulz))
     {
       fscanf(ulz, "%d %s %s", &S.bod, S.ime, S.prezime);
       niz[i] = S;
       if(S.bod>=max) max = S.bod;
       i++;
     }

     for(i=0; i<br; i++) {
       aps = (float)niz[i].bod/max*100;

       printf("%d %s %s --- %.2f\n", niz[i].bod, niz[i].ime, niz[i].prezime, aps);
     }

     fclose(ulz);

     return 0;
}

int brojRedova(char FileName[MAX])
{
    int br=0;
    char row[MAX_ROW];

    FILE *ulz;
    ulz = fopen(FileName, "r");

    while( fgets(row, 100, ulz) ) {
      br++;
    }

     fclose(ulz);
     return br;
}
