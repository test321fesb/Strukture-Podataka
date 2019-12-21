#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFFA (48)
#define TempB (32)

typedef struct _Node
{
    char data[BUFFA];
    char timeData[BUFFA];
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

typedef struct _ST
{
    struct _Dir* headBranch;
    struct _Dir* tempStack;
    struct _Node* headNode;
    struct _Node* current;
} ST;
typedef struct _ST* pST;

Position CreateNode();
ptr CreatePtr(Position);
int AddTime(Position);
int Start(pST);
int SwitchCase(pST, char*, char*);
int CommandPrompt();
int Birth(Position, char*);
int Adoption(Position, Position);
int Pedo(ptr, Position, char*);
int Pop(ptr);
int Push(ptr, Position);
int PrintDirectory(Position, ptr);
int PrintSiblings(Position);
int Menu(ptr);
void PrintMenu(ptr);
int FamilyReunion(pST);
Position SiblingFinder(Position, ptr, int*);
void tempPrint(ptr head);

int main()
{
    Node root;
    root.child = NULL;
    root.sibling = NULL;
    strcpy(root.data, "Users\\Jozo");
    
    Dir stack;
    stack.next = NULL;

    Dir temp;
    temp.next = NULL;

    ST mainST;
    mainST.headBranch = &stack;
    mainST.tempStack = &temp;
    mainST.headNode = &root;
    mainST.current = mainST.headNode;

    CommandPrompt();

    Start(&mainST);

    return 0;
}

int Start(pST head)             // cita unos i salje u switch case
{
    head->headBranch->next = CreatePtr(head->current);
    char* readLine = (char*)malloc(BUFFA * sizeof(char));
    int n = 0, input = 0;
    char check[10];
    do
    {
        Menu(head->headBranch);
        fgets(readLine, TempB, stdin);
        sscanf(readLine, "%s %n", check, &n);
        readLine = readLine + n;

        input = SwitchCase(head, check, readLine);
        head->current = head->headBranch->next->NodePosition;
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
    if (curr->next == NULL) return;
    PrintMenu(curr->next);
    printf("\\%s", curr->next->NodePosition->data);
}

int SwitchCase(pST head, char* check, char* line)        // vrti unos i salje u odredene funkcije
{
    if (strcmp(check, "md") == 0)
    {
        Birth(head->current, line);
        return 1;
    }
    if (strcmp(check, "cd") == 0)
    {
        Pedo(head->headBranch, head->current, line);
        return 2;
    }
    if (strcmp(check, "cd..") == 0)
    {
        if (head->headBranch->next->next == NULL) printf(" \nLocation: ROOT\n");
        else Pop(head->headBranch);
        return 3;
    }
    if (strcmp(check, "dir") == 0)
    {
        PrintDirectory(head->current, head->headBranch);
        return 4;
    }
    if (strcmp(check, "list") == 0)
    {
        FamilyReunion(head);
        return 6;
    }
    if (strcmp(check, "exit") == 0) return 5;
    printf("\n'%s' is not recognized as an internal or external command, operable program or batch file.\n", check);
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
    ptr temp = (ptr)malloc(sizeof(Dir));
    if (!temp)
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
}

int AddTime(Position temp)
{
    time_t t;
    struct tm* timeinfo;
    time(&t);
    timeinfo = localtime(&t);

    strcpy(temp->timeData, asctime(timeinfo));
    temp->timeData[strlen(temp->timeData) - 1] = 0;
    return 0;
}                                                               // -------------------------------

int Birth(Position curr, char* line)							//     <- birth  stvori dite
{
    line[strlen(line) - 1] = 0;
    Position temp = CreateNode();
    strcpy(temp->data, line);
    AddTime(temp);
    if (curr->child == NULL) curr->child = temp;
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
    line[strlen(line) - 1] = 0;
    Position temp = Curr->child;
    while (temp != NULL)
    {
        if (strcmp(temp->data, line) == 0)
        {
            Push(Stack, temp);
            return 1;
        }
        temp = temp->sibling;
    }
    printf("\nDatoteka ne postoji!\n");
    return 0;
}

int Pop(ptr head)            //free sa stoga, iduci na stogu postaje current
{
    if (head->next == NULL)
    {
        printf("\nError.\n");
        return 1;
    }
    ptr temp = head->next;
    head->next = head->next->next;
    free(temp);
    return 0;
}

int Push(ptr head, Position NewCurr)         // stvara ptr, stavlja ga na stog i pamti curr koji je bija, novi curr je sibling od childa
{
    ptr temp = CreatePtr(NewCurr);
    temp->next = head->next;
    head->next = temp;
    return 0;
}

int PrintDirectory(Position curr, ptr head)                // ispisuje dicu currenta
{
    tempPrint(head);
    printf("\n\n\t\t0 files\n\t\t%d directories\n\n", PrintSiblings(curr));
    return 0;
}

int PrintSiblings(Position curr)
{
    int counter = 0;
    Position temp = curr->child;
    if (temp == NULL) return 0;
    while (temp != NULL)
    {
        counter++;
        printf("\n%s\t<DIR>\t\t%s", temp->timeData, temp->data);
        temp = temp->sibling;
    }
    return counter;
}

void tempPrint(ptr head)
{
    printf("\n  Volume in drive C is OS\n  Volume Serial Number is D8D7-06C0\n\n  Directory of ");
    Menu(head);
    puts("");
}

int FamilyReunion(pST head)
{
    Position current = head->headNode;
    int i = 0, n = 0;
    do
    {
        i = 0;
        while (i != n)
        {
            printf("  ");
            i++;
        }
        printf("\t- %s\n", current->data);
        if (current->child != NULL)
        {
            Push(head->tempStack, current);
            current = current->child;
            n++;
            continue;
        }
        if (current->sibling != NULL)
        {
            current = current->sibling;
            continue;
        }
        current = SiblingFinder(current, head->tempStack, &n);
    } while (current != NULL);
    return 0;
}

Position SiblingFinder(Position current, ptr head, int* n)
{
    if (head->next == NULL) return NULL;
    if (current->sibling == NULL)
    {
        current = head->next->NodePosition;
        Pop(head);
        *n = *n - 1;
        current = SiblingFinder(current, head, n);
    }
    else return current->sibling;
}
