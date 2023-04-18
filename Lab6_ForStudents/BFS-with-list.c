#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    int *visited;
    ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void BFS (Graph G, int v);

void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

int main()
{
    Graph g;
    int i,j;
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.list = (ListNode **)malloc(g.V*sizeof(ListNode *));
    for(i=0;i<g.V;i++)
        g.list[i] = NULL;

    g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        V1= V1-1;

        if(g.list[V1]==NULL)
        {
            temp = (ListNode*) malloc(sizeof(ListNode));
            temp->vertex = V2;
            temp->next = g.list[V1];
            g.list[V1] = temp;
        }
        else{
            temp = (ListNode *) malloc(sizeof(ListNode));
            temp->next = g.list[V1];
            temp->vertex = V2;
            g.list[V1] = temp;
        }
        g.E++;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for BFS:\n");
    scanf("%d", &i);
    printGraphMatrix(g);
    BFS(g,i);

    return 0;
}

void BFS(Graph g, int v){
    // Write your code here
    Queue q;
    q.size = 0;
    q.head = NULL;
    q.tail = NULL;
    int i,j, cur;
    if(v<=0) return;
    if(g.V<=0 || g.E<=0) return;

    // start from vertex v
    enqueue(&q, v);
    g.visited[v-1] = 1;
    printf("%d ", v);

    while(!isEmptyQueue(q)){
        cur = getFront(q);
        dequeue(&q);
        ListNode *temp = g.list[cur-1];

        while(temp){
            if(g.visited[(temp->vertex)-1]==0){
                g.visited[(temp->vertex)-1]=1;
                printf("%d ",temp->vertex);
                enqueue(&q, temp->vertex);
            }
            temp = temp->next;
        }
    }
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        ListNode *temp = g.list[i];
        printf("%d : ",i+1);
        while(temp){
            printf("%d, ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }

}


void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
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
       int headValue = qPtr->head->vertex;
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return headValue;
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