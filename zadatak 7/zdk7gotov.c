#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX (50)

typedef struct _Node {
	int data;
	struct _Node* next;
} Node;

typedef struct _Node* Position;

int push(Position head, int x);
int pop(Position head);
Position CreateNode(int x);
int printStack(Position head);
char* readFile();
int postfiksCalculator(char*, Position);
int case1(Position);
int case2(Position);
int case3(Position,char*);

int main() {
	Node head;
	head.next = NULL;
	
	int REZ = 0;
	
	char* tempString;
	tempString = readFile();
	
	REZ = postfiksCalculator(tempString,&head);
	
	printf("\n\t%d\n",REZ);

	return 0;
}

int push(Position head, int x) {
	Position temp = CreateNode(x);
	temp->next = head->next;
	head->next = temp;
	return 0;
}

int pop(Position head) {
	Position temp = NULL;
	if (head->next == NULL) {
		printf("Stog prazan.");
		return -1;
	}
	temp = head->next;
	head->next = head->next->next;
	free(temp);
	return 0;
}

int printStack(Position head) {
	Position temp = head->next;
	if (head->next == NULL) {
		printf("Stog prazan.");
		return -1;	
	}
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	return 0;
}

Position CreateNode(int x) {
	Position temp = (Position)malloc(sizeof(Node));
	if (temp == NULL)
		return NULL;
	else {
		temp->data = x;
		temp->next = NULL;
		return temp;
	}
}

char* readFile()
{
	FILE *ulz;
	char* data = (char*)malloc(MAX * sizeof(char));

	ulz = fopen("postfiks.txt", "r");
	fgets(data, MAX, ulz);
	fclose(ulz);

	if (data) return data;
	return NULL;
}

int postfiksCalculator(char* postfiks, Position head)
{
    char check[10];
    int n = 0;
    
    do{
        sscanf(postfiks,"%s %n",check,&n);
        postfiks = postfiks + n;
        
        if(strcmp(check,"+")==0) case1(head);
        else if(strcmp(check,"*")==0) case2(head);
        else case3(head,check);
        
    } while(n != 1);
    
    return (head->next->data);
}

int caseSum(Position head)
{
    int tempVar = 0;
    tempVar+=head->next->data;
    pop(head);
    tempVar+=head->next->data;
    pop(head);
    push(head,tempVar);
    return 0;
}

int caseProd(Position head)
{
    int tempVar = 1;
    tempVar*= head->next->data;
    pop(head);
    tempVar*= head->next->data;
    pop(head);
    push(head,tempVar);
    return 0;
}

int caseInt(Position head, char* check)
{
    int checkInt = 0;
    sscanf(check,"%d",&checkInt);
    push(head,checkInt);
    return 0;
}
