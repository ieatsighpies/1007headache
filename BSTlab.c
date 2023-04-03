//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);

	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{
	if(*node==NULL) {
		*node = malloc(sizeof(BTNode));
		if (*node != NULL){
			(*node)->item = value;
			(*node)->left=NULL; (*node)->right=NULL;
		}
	}

    // //value isn't found in tree so add it in the right place
    if(value < (*node)->item){
        insertBSTNode(&((*node)->left), value);
    }
    else if(value > (*node)->item){
        insertBSTNode(&((*node)->right),value);
    }
	else {
		return;
	}
}

//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
	if(node==NULL) return;

	printBSTInOrder(node->left);
	printf("%d, ", node->item);
	printBSTInOrder(node->right);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
	if(node==NULL) return 0;

	if(node->item < max && node->item > min) return 1;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	if(node==NULL){
		return NULL;
	}
	//tree traversal
	if(node->item < value)
		node->left = removeBSTNode(node->left,value);
	if(node->item > value)
		node->right = removeBSTNode(node->right,value);
	
	//no children
	if(node->left==NULL && node->right==NULL){
		free(node);
		node = NULL;
	}
	//only left child 
	else if(node->left==NULL){
		BTNode *temp=node;
		node = node->right;
		free(temp);
	}
	//only right child
	else if(node->right==NULL){
		BTNode *temp=node;
		node = node->left;
		free(temp);
	}
	//2 children
	else {
		BTNode *temp = findMin(node->right);
		node->item = temp->item;
		node->right = removeBSTNode(node->right,temp->item);
		//alt method: findMax(node->left) as successor
	}
	return node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	BTNode *L, *R;
	if(p==NULL) return NULL;

	L = findMin(p->left);
	R = findMin(p->right);
	if(R->item < L->item){
		L = R; 
	}
	return L;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BTNode *findMax(BTNode *root){
	BTNode *L, *R;
	if(root==NULL) return NULL;
	
	L=findMax(root->left); 
	R=findMax(root->right);
	
	if(L->item < R->item)
		L = R;
	return L;
