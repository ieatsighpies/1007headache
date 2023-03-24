#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 3

typedef struct _listnode{
    int key;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} HashTableNode;

typedef struct _hashTable{
   int hSize;
   int nSize;
   HashTableNode *Table;
} HashTable;

int Hash(int,int);

ListNode* HashSearch(HashTable, int);
int HashInsert(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);

int main()
{
    int opt;
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q3Hash;
    Q3Hash.hSize = 0;
    Q3Hash.nSize = 0;
    Q3Hash.Table = NULL;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Print the hash table            |\n");
    printf("|5. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=4){
        switch(opt){
        case 1:
            printf("Enter number of data to be inserted:\n");
            scanf("%d",&size);

            Q3Hash.hSize = (int)size/ LOAD_FACTOR;
            Q3Hash.nSize = 0;

            Q3Hash.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q3Hash.hSize));

            for(i=0;i<Q3Hash.hSize;i++){
               Q3Hash.Table[i].head = NULL;
               Q3Hash.Table[i].size = 0;
            }
            printf("HashTable is created.\n");
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);

            if(HashInsert(&Q3Hash,key))
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key);
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q3Hash, key);

            if(node!=NULL)
                printf("%d is found.\n",key);
            else
                printf("%d is not found.\n",key);
            break;
        case 4:
            HashPrint(Q3Hash);
            break;
        }

    printf("Enter selection: ");
    scanf("%d",&opt);
    }

    for(i=0;i<Q3Hash.hSize;i++)
    {
        while(Q3Hash.Table[i].head)
        {
            ListNode *temp;
            temp = Q3Hash.Table[i].head;
            Q3Hash.Table[i].head = Q3Hash.Table[i].head->next;
            free(temp);
        }
    }
    free(Q3Hash.Table);

    return 0;

}

int Hash(int key,int hSize)
{
    return key%hSize;
}

ListNode* HashSearch(HashTable Q3Hash, int key)
{
    // ListNode *temp=NULL;
    // for(int i=0;Q3Hash.hSize;i++){
    //     temp =Q3Hash.Table[i].head;
    //     while(temp){
    //         if(key==temp->key){
    //             return temp;
    //         }
    //         temp=temp->next;
    //     }
    // }
    // if(temp==NULL) return NULL;
    int index; ListNode *temp;
    //sanity check
    if(Q3Hash.hSize!=0) 
        index = Hash(key,Q3Hash.hSize);
    else
        return NULL;
    
    temp = Q3Hash.Table[index].head;
    while(temp){
        if(temp->key==key)
            return temp;
        temp=temp->next;
    }
    return NULL;
    //logic is the same, but use if-else to check the hSize in sanity check!
}

int HashInsert(HashTable* Q3HashPtr, int key)
{
    // ListNode *temp=NULL;

    // if(Q3HashPtr->nSize==0 || Q3HashPtr->Table==NULL){
    //     Q3HashPtr->Table[0]->head= malloc(sizeof(HashTableNode));
    //     Q3HashPtr->Table[0]->head->key=key;
    //     Q3HashPtr->Table[0].head->next = NULL;
    //     Q3HashPtr->nSize++;
    // }
    // for(int i=0;i<Q3HashPtr->hSize;i++){
    //     temp = Q3HashPtr->Table[i].head;
    //     while(temp){

    //     }
    // }
    int index; 
    ListNode *newNode;
    //sanity check for duplicates
    if(HashSearch(*Q3HashPtr,key)!=NULL)
        return 0;
    //sanity check for available slots
    if(Q3HashPtr->hSize!=0)
        //create the index using hash function!
        index = Hash(key, Q3HashPtr->hSize);
    //insert from the front of LL at index
    newNode = (ListNode *) malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->next = Q3HashPtr->Table[index].head;
    Q3HashPtr->Table[index].head = newNode;

    Q3HashPtr->Table[index].size++;
    Q3HashPtr->nSize++;
    return 1;
}

void HashPrint(HashTable Q3Hash)
{
    int i;
    ListNode *temp;
    for(i=0;i<Q3Hash.hSize;i++)
    {
        temp =Q3Hash.Table[i].head;
        printf("%d:  ",i);
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}
