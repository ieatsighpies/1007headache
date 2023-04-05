#include <stdio.h>
#include <stdlib.h>

typedef struct _arraynode
{
    int *itemArray;
    int sizeArray;
    struct _arraynode *next;
}ArrayNode;

typedef struct _arraylist{
   int size; //the size of a possible sequence
   ArrayNode *head;
} ArrayList;

typedef struct _listnode
{
    int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int sum; //the number of possible sequences
   int size;
   ListNode *head;
} LinkedList;

// You should not change the prototypes of these functions
//////LinkedList///////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int coin);
int removeNode(LinkedList *ll, int index);
ListNode *findNode(LinkedList ll, int index);
void removeAllItems(LinkedList *ll);
///////////////////////////////////////////////////

void sumToC(LinkedList* ll, int C, ArrayList* al);
int main()
{
    int C;
    printf("Enter a number:\n");
    scanf("%d",&C);

    LinkedList ll;
    ll.head = NULL;
    ll.sum = 0;
    ll.size = 0;
    ArrayList al;
    al.head = NULL;
    al.size = 0;

    sumToC(&ll,C,&al);
    ArrayNode* temp;
    int i,j;
    temp = al.head;
    for(i=0;i<al.size;i++){
        for(j=0;j<temp->sizeArray;j++)
            printf(" %d ",temp->itemArray[j]);
        printf("\n");
        temp = temp->next;
    }

    return 0;
}

///////////////////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

        if (index == 0){
		cur = ll->head;
		ll->head = (ListNode*) malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}

	return 0;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		ll->sum -= ll->head->item;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 1;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return 0;

		cur = pre->next;
		ll->sum -= cur->item;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 1;
	}

	return 0;
}

ListNode *findNode(LinkedList ll, int index){

	ListNode *temp;

	if (index < 0 || index >= ll.size)
		return NULL;

	temp = ll.head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
	ll->sum =0;
}


void sumToC(LinkedList* ll, int C, ArrayList* al)
{
    al->head = NULL; al->size = 0;
	//find the possible sequences
	ll->head = (ListNode*) malloc(sizeof(ListNode));
	//set first node as 1
	ll->head->item = 1; ll->sum = 1; ll->size = 1;

	ListNode *temp = NULL,*cur;

	while(ll->head->item <= C){
		cur = findNode(*ll, ll->size-1);

		if(ll->sum < C){
			insertNode(ll,ll->size,(cur->item + 1));
		}
		if(ll->sum == C){
			//copy sequence into array
			ArrayNode *tracker = al->head;
			//if arraylist is empty
			if(al->head==NULL){
				//new array node
				ArrayNode* newNode = (ArrayNode*) malloc(sizeof(ArrayNode));
				newNode->sizeArray = ll->size;
				newNode->itemArray = (int*) malloc(sizeof(int)* (newNode->sizeArray) );
				newNode->next = al->head;
				al->head = newNode;
				//copying sequence into array
				int i=0;
				temp = ll->head;
				while(temp){
					newNode->itemArray[i] = temp->item;
					i++;
					temp = temp->next;
				}
			} // adding on to the arraylist
			else{
				ArrayNode* newNode = (ArrayNode*) malloc(sizeof(ArrayNode));
				newNode->sizeArray = ll->size;
				newNode->itemArray = (int*) malloc(sizeof(int)* (newNode->sizeArray) );
				newNode->next = al->head;
				//append new node to arraylist
				al->head = newNode;
				//copying sequence into array
				int i=0;
				temp = ll->head;
				while(temp){
					newNode->itemArray[i] = temp->item;
					i++;
					temp = temp->next;
				}
			// 	//keep track of last array node in the al
			// 	//tracker = tracker->next;
			}

			//increase size since added a sequence into al
			// al->size++;
            temp = ll->head;
            while(temp){
                printf("%d ", temp->item);
                temp = temp->next;
            }
			//remove last LL node to continue while loop
			removeNode(ll,ll->size-1);
			//increment the last number to find more sequences
			temp = findNode(*ll,ll->size-1);
			temp->item += 1;
			ll->sum++;
		}
		if(ll->sum > C){
			//remove last number
			removeNode(ll, ll->size-1);
			//find the end of the list and increment that number, update sum
			temp = findNode(*ll, ll->size-1);
			temp->item += 1;
			ll->sum++;
		}
	}
	//insert C into al
	// tracker = al->head;
	// while(tracker->next != NULL){
	// 	tracker = tracker->next;
	// }
	// ArrayNode* cNode = (ArrayNode*) malloc(sizeof(ArrayNode) );
	// tracker->next = cNode;
	// cNode->next = NULL;
	// cNode->itemArray = (int*) malloc(sizeof(int));
	// cNode->sizeArray = 1;
	// cNode->itemArray[0] = C;
	// al->size++;

}
