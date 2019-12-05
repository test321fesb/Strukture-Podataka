#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _Node {
  int data;
  struct _Node* next;
} Node;

typedef Node* Position;

Position CreateNode(int x);
int enQueue(Position head, int x);
int deQueue(Position head);
int push(Node* head, int x);
int pop(Node* head);
Position top(Node* head);
int printList(Position head);
int randomNumber();

int main()  {
  Node Stack, Queue;
  int n = 0, i = 0, a = 0;

  srand(time(0));

  Stack.next = NULL;
  Queue.next = NULL;

  printf("broj brojeva?\n");
  scanf("%d", &n);

  for(i=0; i<n; i++) {
    a = 10 + randomNumber();
    enQueue(&Queue, a);
    push(&Stack, a);
  }

  printf("\nRed:\n");
  printList(&Queue);

  printf("\nStog:\n");
  printList(&Stack);

  printf("\n");

  printf("koliko da izbacimo sa reda pa sa stoga\n");
  scanf("%d %d", &n, &a);

  for(i=0; i<n; i++)
  {
    deQueue(&Queue);
  }

  for(i=0; i<a; i++)
  {
    pop(&Stack);
  }

  printf("\nRed:\n");
  printList(&Queue);

  printf("\nStog:\n");
  printList(&Stack);

  return 0;
}

Position CreateNode(int x) {
  Position temp = (Position)malloc(sizeof(Node));
  if(temp == NULL)
    return NULL;
  temp->data = x;
  temp->next = NULL;
  return temp;
}

int enQueue(Position head, int x) {
  Position temp = head->next;
  Position new = CreateNode(x);

  if(head->next == NULL) {
    head->next = new;
    return 0;
  }

  while(temp->next != NULL)
  {
    temp = temp->next;
  }
  temp->next = new;

  return 0;
}

int deQueue (Position head) {
  Position temp = head->next;
  *head = *(head->next);
  free(temp);
  return 0;
}

int push(Node* head, int x) {
    Node* temp = CreateNode(x);
    temp->next = head->next;
    head->next = temp;
    return 0;
}

int pop(Node* head) {
  Position temp = head->next;
  *head = *(head->next);
  free(temp);
  return 0;
}

Position top(Node* head) {
  if(head->next == NULL)
    return NULL;
  return head->next;
}

int randomNumber() {
    return rand()%90;
}

int printList(Position head) {
  Position temp = head->next;
  while(temp != NULL){
    printf("%d ", temp->data);
    temp = temp->next;
  }
  return 0;
}
