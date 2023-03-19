#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
 // Write your code here
    int count=0,probe=hash(key),link=-1;
    //empty table, full table
    //hash takes u to empty slot/used slot
    
    while(count<TABLESIZE){
        if(hashTable[probe].indicator==EMPTY){
            hashTable[probe].key=key;
            hashTable[probe].indicator=USED;
            // if(link!=-1)
            //     hashTable[link].next=probe;
            return probe;   
        }
        else if(hashTable[probe].indicator==USED){
            count++;
            //no duplicates
            if(hashTable[probe].key==key)
                return -1;
            
            for(int i=probe;i<TABLESIZE;i++){
                if(hashTable[i].indicator==EMPTY){
                    link = i;
                    break;
                }
            }
            if(link==-1){
                for(int i=0;i<probe;i++){
                    if(hashTable[i].indicator==EMPTY){
                        link=i;
                        break;
                    }
                }
            }

            if(hashTable[probe].next== -1){    
                hashTable[probe].next = link;
                if(link!=-1)
                    probe = link;
            }
            else{
                probe = hashTable[probe].next;
            }
        }
    }
    if(count>=TABLESIZE)
        return count;
}

int HashFind(int key, HashSlot hashTable[])
{
    int empty=0,count=0,probe=hash(key);
    
    while(1){
        if(count>=TABLESIZE) return -1;
        if(hashTable[probe].indicator==EMPTY) return -1;
        if(hashTable[probe].indicator==USED){
            count++;
            if(hashTable[probe].key==key)
                return probe;
        }
        if(hashTable[probe].next!=-1){
                probe = hashTable[probe].next;
                count++;
            }
    }
    return -1;
}
