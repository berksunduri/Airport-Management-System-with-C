#include <stdio.h>
#include <stdlib.h>

// Node
typedef struct node {
    int data;

    // Lower values indicate higher priority
    int priority;
    int talep;
    struct node* next;

} Node;

struct Ucak
{
    int oncelikID;
    int ucakID;
    int talepSaat;
    int talepSaat2;
    int inenSaat;
}ucak[1000];

struct Kalkis
{
    int oncelikID;
    int ucakID;
    int talepSaat;
    int gecikmeSuresi;
    int kalkisSuresi;
}kalkis[1000];


// Function to Create A New Node
Node* newNode(int d, int p,int x)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->talep=x;
    temp->next = NULL;

    return temp;
}

// Return the value at head
int peek(Node** head)
{
    return (*head)->data;
}
int peekP(Node** head)
{
    return (*head)->priority;
}
int peekT(Node** head)
{
    return (*head)->talep;
}

// Removes the element with the
// highest priority form the list
void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

// Function to push according to priority
void push(Node** head, int d, int p,int x)
{
    Node* start = (*head);

    // Create new Node
    Node* temp = newNode(d, p, x);

    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > p) {

        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {

        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
            start->next->priority < p) {
            start = start->next;
        }

        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}

// Function to check is list is empty
int isEmpty(Node** head)
{
    return (*head) == NULL;
}

int canGoDown(int num_planes)
{

    int time[25] = {0}; // not using element [0]

    for (int i = 0; i < num_planes; i++)
    {
        int found = 0;
        for (int attempts = 0; attempts < 3; attempts++)
        {
            if (time[ucak[i].talepSaat] != 0)
            {
                if (++ucak[i].talepSaat> 24)
                {

                    ucak[i].talepSaat= -1;// for marking the ones which goes above the 24h time limit
                    break;
                }
            }
            else
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            ucak[i].inenSaat= ucak[i].talepSaat;
            time[ucak[i].talepSaat] = 1;
        }
    }
}

// Driver code
int main()
{
    FILE* input;
    input=fopen("C://Users//Berk//Desktop//prolab3//input.txt","r");
    if(input==NULL)
    {
        printf("In Dosya acilamadi");
    }

     FILE* out;
    out=fopen("C://Users//Berk//Desktop//prolab3//output.txt","w");
    if(out==NULL)
    {
        printf("Out Dosya acilamadi");
    }

    int line[1000];
    int f;
    int index=0;
    while(fgets(line,sizeof(line),input))
    {
        f++;
        if(f>1)
        {
            fscanf(input,"%d %d %d",&ucak[index].oncelikID,&ucak[index].ucakID,&ucak[index].talepSaat);
            //printf("%d %d %d\n",ucak[index].oncelikID,ucak[index].ucakID,ucak[index].talepSaat);
            ucak[index].talepSaat2=ucak[index].talepSaat;
            index++;
        }

    }
   for(int i=0; i<(index)-1; i++)
    {
        for(int j=0; j<(index)-1-i; j++)
        {
            if(ucak[j].oncelikID>ucak[j+1].oncelikID)
            {
               int temp=ucak[j].oncelikID;
               ucak[j].oncelikID=ucak[j+1].oncelikID;
               ucak[j+1].oncelikID=temp;

               int temp2=ucak[j].ucakID;
               ucak[j].ucakID=ucak[j+1].ucakID;
               ucak[j+1].ucakID=temp2;

               int temp3=ucak[j].talepSaat;
               ucak[j].talepSaat=ucak[j+1].talepSaat;
               ucak[j+1].talepSaat=temp3;

               int temp4=ucak[j].talepSaat2;
               ucak[j].talepSaat2=ucak[j+1].talepSaat2;
               ucak[j+1].talepSaat2=temp4;
            }
        }
    }
    canGoDown(index);

    for(int i=0;i<index;i++)
    {
        printf("OncelikID:%d ucakID:%d talepEdilenSaat:%d inisSaati:%d\n",ucak[i].oncelikID,ucak[i].ucakID,ucak[i].talepSaat2,ucak[i].inenSaat);

    }
    printf("\n\n\n");
   for(int i=0; i<index; i++)
   {
       kalkis[i].oncelikID=ucak[i].oncelikID;
       kalkis[i].ucakID=ucak[i].ucakID;
       kalkis[i].talepSaat=ucak[i].inenSaat;
       if(ucak[i].inenSaat<=0)
       {
        kalkis[i].gecikmeSuresi=0;
       }
       else
       {
       kalkis[i].gecikmeSuresi=(ucak[i].inenSaat)-(ucak[i].talepSaat2);
       }

       if(ucak[i].inenSaat==24)
       {
            kalkis[i].kalkisSuresi=1;
       }
       if(ucak[i].inenSaat==0)
       {
           kalkis[i].kalkisSuresi=0;
       }
       else
        {
        kalkis[i].kalkisSuresi=ucak[i].inenSaat+1;
        }

   }
     for(int i=0;i<index;i++)
    {
        printf("oncelikID:%d ucakID:%d talepEdilenSaat:%d kalkisSaati:%d gecikmeSuresi:%d\n",kalkis[i].oncelikID,kalkis[i].ucakID,kalkis[i].talepSaat,kalkis[i].kalkisSuresi,kalkis[i].gecikmeSuresi);
    }

         for(int i=0;i<index;i++)
    {
        fprintf(out,"oncelikID:%d ucakID:%d talepEdilenSaat:%d kalkisSaati:%d gecikmeSuresi:%d\n",kalkis[i].oncelikID,kalkis[i].ucakID,kalkis[i].talepSaat,kalkis[i].kalkisSuresi,kalkis[i].gecikmeSuresi);
    }
    /*while (!isEmpty(&pq)) {
        printf("%d ", peek(&pq));
        pop(&pq);
    }*/
    //while (!isEmpty(&inis)) {
     //   printf("%d %d %d\n",peekP(&inis), peek(&inis),peekT(&inis));
       // pop(&inis);
    //}

    return 0;
}
