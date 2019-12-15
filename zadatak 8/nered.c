#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFA (32)
#define TempB (32)

typedef struct _Node
{
	char data[BUFFA];
	struct _Node* child;
	struct _Node* sibling;
} Node;

typedef struct _Node* Position;

typedef struct _Dir
{
	Position NodePosition;
	struct _Dir* next;

} Dir;

typedef struct _Dir* ptr;

Position CreateNode();
ptr CreatePtr(Position);
int Start(Position);
int SwitchCase(Position, ptr, char*, char*);
int CommandPrompt();
int Birth(Position, char*);
int Adoption(Position, Position);
int Pedo(ptr, Position, char*);
int Pop(ptr, Position);
int Push(ptr, Position, Position);
int FamilyReunion(Position);
int Menu(ptr);
void PrintMenu(ptr);



int main()
{
	Node root;
	root.child = NULL;
	root.sibling = NULL;
	strcpy(root.data,"\\Users\\Jozo");
	
	CommandPrompt();

	Start(&root);


	getchar();

	return 0;
}

int Start(Position head)             // cita unos i salje u switch case
{
    Position curr = head;
    Dir stack;
	stack.next = CreatePtr(curr);
	
	char* readLine = (char*) malloc (BUFFA*sizeof(char));
	int n = 0, input = 0;
	char check[10];
	
	do
	{
	    printf("\n\t%s\n",curr->data);
	    Menu(&stack);
		fgets(readLine, TempB, stdin);
		sscanf(readLine,"%s %n",check,&n);
		readLine = readLine + n;
		
		input = SwitchCase(curr, &stack, check, readLine);
	} while (input != 5);
	return 0;
}

int CommandPrompt()
{
	printf("Microsoft Windows[Version 10.0.10240]\n(c) 2015 Microsoft Corporation.All rights reserved.\n\n");
	return 0;
}

int Menu(ptr head)          // pocetak ispisa
{
    printf("C:");
    PrintMenu(head);
    printf("> ");
    return 0;
}

void PrintMenu(ptr curr)     // rekurzija
{
    if(curr->next == NULL) return;
    PrintMenu(curr->next);
    printf("\\%s",curr->next->NodePosition->data);
}

int SwitchCase(Position curr, ptr head, char* check, char* line)        // vrti unos i salje u odredene funkcije
{
    if(strcmp(check,"md") == 0)
    {
        Birth(curr, line);
        return 1;
    }
    if(strcmp(check,"cd") == 0)
    {
        Pedo(head, curr, line);
        return 2;
    }
    if(strcmp(check,"cd..") == 0)
    {
        Pop(head, curr);
        return 3;
    }
    if(strcmp(check,"dir") == 0)
    {
        FamilyReunion(curr);
        return 4;
    }
    if(strcmp(check,"exit") == 0) return 5;
	printf("'%s' is not recognized as an internal or external command, operable program or batch file.",check);
	return 0;
}

Position CreateNode()                                   // --------------- alokacije ------------
{
	Position temp = (Position)malloc(sizeof(Node));
	if (!temp)
	{
		printf("\n\tError!\n");
		return NULL;
	}
	else
	{
	    temp->sibling = NULL;
	    temp->child = NULL;
	    return temp;
	}
}

ptr CreatePtr(Position Curr)
{
    ptr temp = (ptr) malloc (sizeof(Dir));
    if(!temp)
    {
        printf("\n\tError!\n");
        return NULL;
    }
    else
    {
        temp->NodePosition = Curr;
        temp->next = NULL;
        return temp;
    }
}                                   // -------------------------------

int Birth(Position curr, char* line)							//     <- birth  stvori dite
{
    line[strlen(line)-1] = 0;
	Position temp = CreateNode();
	strcpy(temp->data,line);
	if(curr->child == NULL) curr->child = temp;
	else Adoption(curr->child, temp);
	return 0;
}

int Adoption(Position curr, Position temp)          //   stavlja siblinga na kraj liste
{
	Position tempNode = curr;

	if (curr->sibling == NULL)
	{
		curr->sibling = temp;
		return 1;
	}
	while (tempNode->sibling != NULL)
		tempNode = tempNode->sibling;
	tempNode->sibling = temp;
	return 0;
}

int Pedo(ptr Stack, Position Curr, char* line)              //   udi u dite, trazi postoji li dite i salje na push
{
    line[strlen(line)-1] = 0;
    Position temp = Curr;
    while(temp->child!=NULL)
    {
        printf("\n\t%s\n",temp->child->data);
        if(strcmp(temp->child->data,line) == 0)
        {
            Push(Stack, Curr, temp->child);
            return 1;
        }
        temp->child = temp->child->sibling;
    }
    printf("\nDatoteka ne postoji!\n");
    return 0;
}

int Pop(ptr head, Position curr)            //free sa stoga, iduci na stogu postaje current
{
    if(head->next->next == NULL)
    {
        printf("\nLocation: Root!\n");
        return 1;
    }
    curr = head->next->next->NodePosition;
    ptr temp = head->next;
    head->next = head->next->next;
    free(temp);
    curr = head->next->NodePosition;
    return 0;
}

int Push(ptr head, Position Curr, Position NewCurr)         // stvara ptr, stavlja ga na stog i pamti curr koji je bija, novi curr je sibling od childa
{
    printf("\n\t\t\t%s",NewCurr->data);
    ptr temp = CreatePtr(NewCurr);
    temp->next = head->next;
    head->next = temp;
    
    printf("\n\t\t\t%s",NewCurr->data);
    
    printf("\n\t\t\t%s",Curr->data);
    Curr = NewCurr;
    
    printf("\n\t\t\t%s",Curr->data);
    return 0;
}

int FamilyReunion(Position curr)                // ispisuje dicu currenta
{
    Position temp = curr->child;
    if(temp == NULL)
    {
        printf("\nPrazna datoteka\n");
        return 1;
    }
    while(temp!=NULL)
    {
        printf("\n\tDIR\t%s",temp->data);
        temp = temp->sibling;
    }
    puts("\n");
    return 0;
}
