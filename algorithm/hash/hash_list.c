/*
 *  开放链表法
 *     _______   _________   __________
 *     |__1__|-->|val_|_--|->|val_|_--|-> NULL
 *     |__2__|-->NULL
 *     |__3__|-->NULL   
 *     |__4__|   _________   __________
 *     |__5__|-->|val_|_--|->|val_|_--|-> NULL
 *     |__6__|   _________   __________
 *     |     |-->|val_|_--|->|val_|_--|-> NULL
 *     |  .  |
 *     |  .  |
 *     |  .  |
 *     |     |
 *     |     |
 *     |     |
 *     |     |
 *     |_n-1_|-->NULL
 * */
#include <stdio.h>
#include <stdlib.h>

#define bool  char
#define true 1
#define false 0

#define BUCKET 1000

typedef struct {
    void *value;
    struct ElemType *next;
} ElemType;

typedef struct {
    ElemType *elem[BUCKET];
    int count;
} HashTable;

// success: 1 fail: -1
bool InitHashTable(HashTable *H) {

    int i;
    H->count = BUCKET;
    if (NULL == (H->elem = (ElemType **)malloc(BUCKET * sizeof(struct ElemType*)))) {
        fprintf(stderr, "malloc hashtable failed!"); 
        return false;
    }
    for (i = 0; i < BUCKET; i++) {
        H->elem[i] = NULL;
    }
    return true;
}

int Hash(void *value) {
    key = *((int*)value);
    return key%BUCKET;
}
        

void InsertHash(HashTable *H, void *value) {
    int key = *((int *)value);
    int slot = Hash(key);
    ElemType *it = (ElemType*)malloc(sizeof(struct ElemType)); 
    it->value = value; //wheather need to allocate memory for store key??
    it->next = NULL;
    if(H->elem[slot] != NULL) {
        ElemType *n; 
        for(n = H->elem[slot]; n != NULL; n = n->next) {
            int nval = *((int *)n->value);
            if (nval == key) return;
            if (n->next == NULL) n->next = it;
        }
    } else {
        H->elem[slot] = it;
    }
    return;
}

bool SearchHash(HashTable *H, void *value, int *addr) {

    return true;
}

int main() {

}
