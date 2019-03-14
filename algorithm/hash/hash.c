/*
 *  开放定址法
 * */
#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 12
#define NULLKEY -32768

#define bool char
#define true 1
#define false 0

typedef struct {
    int *elem;
    int count;
}HashTable;

int m = 0;

int InitHashTable(HashTable *H) {
    int i;
    m = HASHSIZE;
    H->count = m;
    H->elem = (int *)malloc(m*sizeof(int));
    for(i = 0; i < m; i++)
        H->elem[i] = NULLKEY;
    return 1;
}

int Hash(int key) {
    return key%m;
}

void InsertHash(HashTable *H, int key) {
    int addr = Hash(key);
    while(H->elem[addr] != NULLKEY)
        addr = (addr+1)%m;
    H->elem[addr] = key;
}


bool SearchHash(HashTable *H, int key, int *addr) {
    int origin_index, index;    
    origin_index = index = Hash(key);

    while(H->elem[index] != key) {
        index = (index+1)%m;
        if(origin_index == index) 
            return false;
    }
    *addr = index;
    return true;
}

int main() {
    int a[12] = {12,67,56,16,25,37,22,29,15,47,48,34};
    HashTable H;
    int i;
    InitHashTable(&H);
    for(i = 0; i < m; i++)
        InsertHash(&H, a[i]);
    printf("插入之后的哈希表: ");
    for(i = 0; i < m; i++)
        printf("%d ", H.elem[i]);
    printf("\n");
    int addr;
    bool hit;
    hit =  SearchHash(&H, a[5], &addr);
    if (hit) {
        printf("a[5]=%d, 搜索到a[5]的地址是: %d\n", a[5], addr); 
    } else {
        printf("not found!"); 
    }
    return 0;
}

