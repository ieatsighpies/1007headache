#include <stdio.h>
#include <stdlib.h>
# include <string.h>
#include <stdbool.h>

typedef struct _listnode
{
 int vertex;
 struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
 int V;
 int E;
 ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
 int size;
 QueueNode *head;
 QueueNode *tail;
} Queue;

typedef struct _stack
{
 int size;
 StackNode *head;
} Stack;

void insertAdjVertex(ListNode** AdjList,int vertex);
void removeAdjVertex(ListNode** AdjList,int vertex);
void printGraphList(Graph g);
int matching(Graph g);
int reverseAndCheckPath(int parent[], Graph g);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void printQ(QueueNode *cur);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////
int Prj, Std, Mtr; //Project, Student and Mentor;

int main()
{
   int maxMatch;
   scanf("%d %d %d", &Std, &Prj, &Mtr);

   int np,nm; //number of projects and number of mentors picked by a student
   //build graph
   Graph g;
   g.E = 0; g.V = Std+Std+Prj+Mtr+2; g.list = NULL;
   //form adj list
   ListNode** tempList = (ListNode**) malloc(g.V*sizeof(ListNode*));
   ListNode* temp;
   for(int row=0;row<g.V;row++){
      tempList[row]=NULL;
   }
   //source vertex connected to projects
   for(int i=1; i <= Prj; i++){
      insertAdjVertex(&tempList[0], i);
      g.E++;
   }
   //sink vertex connected to mentors
   for(int i=0; i < Mtr; i++){
      insertAdjVertex(&tempList[Std+Std+Prj+i+1], g.V-1);
      g.E++;
   }
   //for each student
   for(int i=0; i < Std;i++){
      //scan num of preferred projects & mentors
      scanf("%d %d ",&np, &nm);
      int proj, mentor;
      //append vertices for preferred projects
      for(int j=0; j < np; j++){
         scanf("%d ", &proj);
         insertAdjVertex(&tempList[proj], Prj+i+1);
         g.E++;
      }
      //dummy nodes of Std
      insertAdjVertex(&tempList[Prj+i+1], Prj+Std+i+1);
      // append vertices for preferred mentors
      for(int k=0; k < nm; k++){
         scanf("%d", &mentor);
         insertAdjVertex(&tempList[Prj+Std+i+1], mentor+Prj+Std+Std);
         g.E++;
      }
   }
   g.list = tempList;
   printGraphList(g);

   //apply Ford Fulkerson algorithm
   // use DFS or BFS to find a path
   maxMatch = matching(g);
   printf("%d \n", maxMatch);
   return 0;
}

int matching(Graph g)
{
   int count = 0;
   Stack s;
   s.size = 0;
   s.head = NULL;

   while(1){
      int *parent = (int*) malloc(sizeof(int)*g.V);
      for(int i=0; i<g.V; i++)
         parent[i] = -1;

      push(&s, 0);
      parent[0] = -2;

      while(!isEmptyStack(s)){
         int cur = peek(s);
         pop(&s);

         ListNode *temp = g.list[cur];
         while(temp){
            if(parent[(temp->vertex)] == -1){
               parent[(temp->vertex)] = cur;
               push(&s, temp->vertex);
            }
            temp = temp->next;
         }
      }
      if(!reverseAndCheckPath(parent, g))
         break;

      removeAllItemsFromStack(&s);
      free(parent);
      count++;
   }

   return count;
}

int reverseAndCheckPath(int parent[], Graph g){
   int sink = g.V-1;
   if(parent[sink] == -1){
      return 0;
   }

   int child = sink;
   while(parent[child] != -2){
      int root = parent[child];
      removeAdjVertex(&g.list[root],child);
      insertAdjVertex(&g.list[child],root);

      child = root;
   }
   return 1;
}

void printGraphList(Graph g){
   int i;
   ListNode* temp;

   for(i=0;i<g.V;i++)
   {
      printf("%d:\t",i);
      temp = g.list[i];
      while(temp!=NULL){
         printf("%d -> ",temp->vertex);
         temp = temp->next;
      }
      printf("\n");
   }
}
void removeAdjVertex(ListNode** AdjList,int vertex)
{
 ListNode *temp, *preTemp;
 if(*AdjList != NULL)
 {
    if((*AdjList)->vertex ==vertex){//first node
      temp = *AdjList;
      *AdjList = (*AdjList)->next;
      free(temp);
      return;
    }
    preTemp = *AdjList;
    temp = (*AdjList)->next;
    while(temp!=NULL && temp->vertex != vertex)
    {
      preTemp= temp;
      temp = temp->next;
    }
    preTemp->next = temp->next;
    free(temp);
   }
}

void insertAdjVertex(ListNode** AdjList,int vertex)
{
  ListNode *temp;
  if(*AdjList==NULL)
  {
     *AdjList = (ListNode *)malloc(sizeof(ListNode));
     (*AdjList)->vertex = vertex;
     (*AdjList)->next = NULL;
  }
  else{
     temp = (ListNode *)malloc(sizeof(ListNode));
     temp->vertex = vertex;
     temp->next = *AdjList;
     *AdjList = temp;
  }
}

void enqueue(Queue *qPtr, int vertex) {
  QueueNode *newNode;
  newNode = (QueueNode*) malloc(sizeof(QueueNode));
  if(newNode==NULL) exit(0);

  newNode->vertex = vertex;
  newNode->next = NULL;

  if(isEmptyQueue(*qPtr))
     qPtr->head=newNode;
  else
     qPtr->tail->next = newNode;

     qPtr->tail = newNode;
     qPtr->size++;
}

int dequeue(Queue *qPtr) {
   if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
     return 0;
   }
   else{
     QueueNode *temp = qPtr->head;
     qPtr->head = qPtr->head->next;
     if(qPtr->head == NULL) //Queue is emptied
         qPtr->tail = NULL;

     free(temp);
     qPtr->size--;
     return 1;
}
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
   if(q.size==0) return 1;
   else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
  while(dequeue(qPtr));
}

void printQ(QueueNode *cur){
 if(cur==NULL) printf("Empty");

 while (cur != NULL){
    printf("%d ", cur->vertex);
    cur = cur->next;
  }
 printf("\n");
}

void push(Stack *sPtr, int vertex)
{
  StackNode *newNode;
  newNode= (StackNode*) malloc(sizeof(StackNode));
  newNode->vertex = vertex;
  newNode->next = sPtr->head;
  sPtr->head = newNode;
  sPtr->size++;
}

int pop(Stack *sPtr)
{
  if(sPtr==NULL || sPtr->head==NULL){
     return 0;
  }
  else{
     StackNode *temp = sPtr->head;
     sPtr->head = sPtr->head->next;
     free(temp);
     sPtr->size--;
     return 1;
   }
}

int isEmptyStack(Stack s)
{
    if(s.size==0) return 1;
    else return 0;
}

int peek(Stack s){
   return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
   while(pop(sPtr));
}