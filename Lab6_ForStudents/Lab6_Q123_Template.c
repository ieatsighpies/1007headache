#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }

    calDegreeV(g,degreeV);

    printGraphMatrix(g);
    printDegreeV(degreeV,g.V);

    adjM2adjL(&g);

    calDegreeV(g,degreeV);

    printGraphList(g);
    printDegreeV(degreeV,g.V);

    adjL2adjM(&g);
    printGraphMatrix(g);

    return 0;
}

void printGraphMatrix(Graph g)
{
    int i,j;
    if(g.type == ADJ_LIST) {printf("Error"); return;}

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n");
    }

}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void adjM2adjL(Graph *g)
{
 // Question 1
 // Write your code here
    if(g->type==ADJ_LIST) return;
    if(g->V<=0) return;

    int row=0, col=0;
    ListNode* temp=NULL;

    ListNode** tempList = (ListNode**) malloc(g->V*sizeof(ListNode*));
    for(row=0;row<g->V;row++){
        tempList[row]=NULL;
    }
    for(row=0;row<g->V;row++){
        for(col=0;col<g->V;col++){
            if(g->adj.matrix[row][col]==1){
                if(tempList[row]==NULL){
                    tempList[row] = (ListNode*) malloc(sizeof(ListNode));
                    tempList[row]->vertex=col+1;
                    tempList[row]->next = NULL;
                    temp = tempList[row];
                }
                else{
                    temp->next= malloc(sizeof(ListNode));
                    temp->next->vertex = col+1;
                    temp->next->next = NULL;
                    temp = temp->next;
                }
            }
        }
    }
    g->type = ADJ_LIST;

    //free adjacency matrix
    for(row=0;row<g->V;row++){
        free(g->adj.matrix[row]);
    }
    free(g->adj.matrix);

    g->adj.list = tempList;
}

void adjL2adjM(Graph *g){
	// Question 2
    // Write your code here
    int row=0,col=0;
    int** tempAr;

    if(g->V<=0) return;
    if(g->type==ADJ_MATRIX) return;

    tempAr = (int**) malloc(g->V*sizeof(int*));
    for(row=0;row<g->V;row++){
        tempAr[row] = (int *) malloc(g->V*sizeof(int));
    }
    for(row=0;row<g->V;row++){
        for(col=0;col<g->V;col++)
            tempAr[row][col]=0;
    }

    for(row=0;row<g->V;row++){
        ListNode*cur=g->adj.list[row];

        while(cur!=NULL){
            tempAr[row][(cur->vertex)-1]=1;
            cur=cur->next;
        }
    }
    g->type=ADJ_MATRIX;

    for(row=0;row<g->V;row++)
        free(g->adj.list[row]);
    free(g->adj.list);

    g->adj.matrix = tempAr;
}

void calDegreeV(Graph g, int *degreeV)
{
	// Question 3
    // Write your code here
    if(g.V<=0) return;

    int i=0,j=0;
    if(g.type==ADJ_MATRIX){
        for(i=0;i<g.V;i++){
            degreeV[i]=0;

            for(j=0;j<g.V;j++){
                if(g.adj.matrix[i][j]==1)
                    degreeV[i]+= g.adj.matrix[i][j];
            }
        }
    }
    if(g.type==ADJ_LIST){
        for(i=0;i<g.V;i++){
            degreeV[i]=0;

            ListNode*cur=g.adj.list[i];
            while(cur){
                degreeV[i]++;
                cur=cur->next;
            }
        }
    }
}

