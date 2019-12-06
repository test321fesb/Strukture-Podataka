#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX (100)

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

int main() {
	Node Stack;
	int i = 0, x = 0, n = 0;
	char* row;
	row = readFile();
	printf("\t%s", row);

	Stack.next = NULL;

	printf("\nBroj brojeva\n");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		push(&Stack, x);
	}

	printf("\nStog:\n");

	printStack(&Stack);

	scanf("%d", &i);
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
	head = head->next;
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
