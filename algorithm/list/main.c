#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int ElemType;

typedef struct Node { 
    ElemType val;   
    struct Node* next;
} Node;

typedef struct List {
    struct Node *head;
} List;

List *Init() {
    List* l = (List *)malloc(sizeof(List));
    l->head = NULL;
    return l;
}

void Insert(List *l, ElemType val) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (n == NULL)
        return;
    n->val = val;
    n->next = l->head;
    l->head = n;
}

void Delete(List *l) {
    Node* n = l->head;
    if (n != NULL) {
       l->head = n->next;
       free(n);
    }
    return;
}

void Release(List *l) {
    if(l == NULL || l->head == NULL) {
        return;  
    }
    Node *n = l->head;
    while(n) {
        Node *tmp = n; 
        n = n->next;
        free(tmp);
    }
    free(l);
    return;
}

/*
    1->2->3->4-> ... -> n
*/
void ReverseList(List* l) {
    if(l == NULL || l->head == NULL) {
        return; 
    }
    Node *head, *tail,*cur;
    head = l->head;
    if (head->next == NULL) {
        return; 
    }
    cur = head->next;
    tail = head;
    Node* p;
    while(cur) {
       tail->next = cur->next; 
       p = cur->next;
       cur->next = head;
       head = cur;
       cur = p;
    }
    l->head = head;
    return;
}

//k>0: 从头开始第k个节点
//k<0: 从尾部开始第k个节点
Node *FindKNode(List *l, int k) {
    if(l->head == NULL) {
        return NULL; 
    }
    Node *node_k, *node_n_k;
    node_k = node_n_k = l->head;

    if(k > 0) {
        while(--k > 0) {
            if (node_k == NULL)
                return NULL;
            node_k = node_k->next;    
        } 
        return node_k;
    } else {
        k = -k;
        while(--k > 0) {
            if (node_k == NULL)
                return NULL;
            node_k = node_k->next;    
        }
        while(node_k->next) {
            node_k = node_k->next;    
            node_n_k = node_n_k->next;
        }
        return node_n_k;
    }
    return NULL;
}

void PrintList(List *l) {
    if (l->head == NULL)
        fprintf(stderr, "empty list");
    Node *n = l->head;
    while(n) {
        printf("%d->", n->val); 
        n = n->next;
    }
    printf("null\n");
    return;
}

#define N 10
int main(int argc, char *argv[]) {
    List* l = Init();
    ElemType arr[N] = {1,2,3,4,5,6,7,8,9,10};
    int i;
    for(i = 0; i < N; i++) {
        Insert(l,arr[i]); 
    }
    PrintList(l);
    int k = 3;
    Node *node_k = FindKNode(l, k);
    printf("%d node in list is %d\n", k, node_k->val);

    k = -3;
    node_k = FindKNode(l,k);
    printf("%d node in list is %d\n", k, node_k->val);
    k = -1;
    node_k = FindKNode(l,k);
    printf("%d node in list is %d\n", k, node_k->val);

    ReverseList(l);
    printf("reverse list: ");
    PrintList(l);
}
