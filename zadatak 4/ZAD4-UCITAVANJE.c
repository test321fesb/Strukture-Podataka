#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Hello World\n");
    FILE *ulz;

    char row[128];
    char row3[128];
    char row2[128];
    int n=0,i=0;
    int length=0;

    ulz=fopen("aaa.txt","r");
    /*
    while(){
        printf("%s",row2);
    }*/
    fgets(row2,128,ulz);
    fclose(ulz);
    length=strlen(row2)+1;


    for(i=0;i<length/4;i++)
    {
        sscanf(row2+n,"%s %s",row,row3);
        printf("%s %s\n",row,row3);
        n+=4;
    }
    return 0;
}
