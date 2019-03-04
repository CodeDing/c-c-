#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>


#define bool char
#define true 1
#define false 0

typedef struct LinkNode {
    int val; // void *val
    struct LinkNode *pre, *next; 
} LinkNode;

typedef struct List {
    int len;
    struct LinkNode *head, *tail;
} List;

//Make sure l has allocated memory space
void Init(List *l) {
   assert(l != NULL);
   l->head = l->tail = l;
   l->len = 0; 
}

void Push(List *l, LinkNode *n) {
    assert(l != NULL);
    if (l->len == 0) {
        n->pre = n->next = n;
        l->head = l->tail = n;
        l->len++;
        return;
    }
    n->next = l->head;
    n->pre = l->tail;
    l->tail->next = n;
    l->tail = n;
    l->len++;
    //printf("[DEBUG] head => %d, tail => %d\n", l->head->val, l->tail->val);
    //printf("[DEBUG] head => %d, head.next => %d, tail => %d, tail.next => %d\n", l->head->val, l->head->next->val, l->tail->val, l->tail->next->val);
    //printf("[DEBUG] head => 0x%x, head.next => 0x%x, tail => 0x%x, tail.next => 0x%x\n", l->head, l->head->next, l->tail, l->tail->next);
}

void PushFront(List *l, LinkNode *n) {
    assert(l != NULL);
    if (l->len == 0) {
        n->pre = n->next = n;
        l->head = l->tail = n;
        l->len++;
        return;
    }
    n->next = l->head;
    n->pre = l->tail;
    l->head->pre = n;
    l->head = n;
    l->tail->next = l->head;
    //printf("[DEBUG] head => %d, head.next => %d, tail => %d, tail.next => %d\n", l->head->val, l->head->next->val, l->tail->val, l->tail->next->val);
    //printf("[DEBUG] head => 0x%x, head.next => 0x%x, tail => 0x%x, tail.next => 0x%x\n", l->head, l->head->next, l->tail, l->tail->next);
    l->len++;
}

void PushVal(List *l, int v) {
    LinkNode *n = (LinkNode*)malloc(sizeof(struct LinkNode));
    if (n == NULL) {
        fprintf(stderr, "allocated LinkNode memmory failed!\n");
        exit(-1);
    }
    n->val = v;
    Push(l, n);
    return;
}

void PushValFront(List *l, int v) {
    LinkNode *n = (LinkNode*)malloc(sizeof(struct LinkNode));
    if (n == NULL) {
        fprintf(stderr, "allocated LinkNode memmory failed!\n");
        exit(-1);
    }
    n->val = v;
    PushFront(l, n);
    return;

}

LinkNode* Pop(List *l) {
    if (l == NULL || l->len == 0) {
        return NULL; 
    }
    LinkNode *n;
    n = l->tail;
    //TODO: may optimize
    if (l->len == 1) {
        l->head = l->tail = l;
        l->len--;
        return n;
    }
    l->tail = l->tail->pre;
    l->tail->next = l->head;
    l->head->pre = l->tail;
    return n;
}

LinkNode* PopFront(List *l) {
    if (l == NULL || l->len == 0) {
        return NULL; 
    }
    LinkNode *n;
    n = l->head; 
    //TODO: may optimize
    if (l->len == 1) {
        l->head = l->tail = l;
        l->len--;
        return n;
    }
    l->head = l->head->next;
    l->head->pre = l->tail;
    l->tail->next = l->head;
    l->len--;
    return n;
}


int PopVal(List *l) {
    LinkNode *end;
    if ((end = Pop(l)) != NULL) {
        return end->val; 
    }
    return -1;
}

int PopValFront(List *l) {
    LinkNode *head;
    if ((head = PopFront(l)) != NULL) {
        return head->val; 
    }
    return -1;
}

void InsertAt(LinkNode *at, LinkNode *n) {
    LinkNode *next = at->next;
    at->next = n;
    n->pre = at;
    n->next = next;
    return;
}

LinkNode* GetNodeByIndex(List *l, int index) {
    if (l == NULL || l->len == 0) {
        fprintf(stderr, "empty list"); 
        return NULL;
    }
    int direction = 1;
    if (index < 0) {
        direction = -1; 
        index = -index;
    }
    if (index > l->len-1) {
        fprintf(stderr, "[ERROR] Outbound index => %d, list len => %d\n", index, l->len); 
        return NULL;
    }
    int i;
    LinkNode *p;
    if (direction == 1) {
        p = l->head;
        for(i = 0; i < index; i++)
            p = p->next; 
    } else {
        p = l->tail;
        for(i = 0; i < index; i++)
            p = p->pre;
    } 
    return p;
            
}

bool SearchVal(List *l, int val, LinkNode **n) {
    if (l == NULL || l->len == 0) {
        n == NULL;
        return false; 
    }
    LinkNode *p = l->head;
    if (p->val == val) {
        *n = p; 
        return true;
    }
    p = p->next;
    for( ;p != l->head ;p = p->next) {
        if (p->val == val) {
            *n = p;
            return true; 
        }
    }
    return false;
}

void printList(List *l) {
    if (l == NULL || l->len == 0) {
       fprintf(stderr, "empty list!");
       return;
    }
    printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("list len => %d\n", l->len);
    printf("list head => %d, tail => %d\n", l->head->val, l->tail->val);
    LinkNode *n = l->head;
    printf("%d ", n->val);
    n = n->next;
    while (n != l->head) {
       printf("-> %d ", n->val); 
       n = n->next;
    }
    printf("\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
    return;

}

void Qsort(List *l) {

}

int main() {

    LinkNode *n;
    List *l = (List*)malloc(sizeof(struct List));
    Init(l);
    PushVal(l, 1);
    PushVal(l, 2);
    PushVal(l, 3);
    PushVal(l, 4);
    PushValFront(l, 5);

    printList(l);
    if ((n = Pop(l)) != NULL) {
         printf("Pop node => %d\n", n->val);
    }
    printList(l);
    if ((n = PopFront(l)) != NULL) {
         printf("PopFront node => %d\n", n->val);
    }
    printList(l);

    //if ((n = PopFront(l)) != NULL) {
    //     printf("PopFront node => %d\n", n->val);
    //}
    //printList(l);

    bool hit;
    LinkNode *p;
    if ((hit = SearchVal(l, 3, &p))) {
        printf("Find value => %d\n", p->val); 
    }
    if ((hit = SearchVal(l, 13, &p)) == false) {
        printf("Do not found value => %d\n", 13); 
    }

    if ((p = GetNodeByIndex(l, 2)) != NULL) {
        printf("Get Index => %d, value => %d\n", 2, p->val); 
    }
    if ((p = GetNodeByIndex(l, -2)) != NULL) {
        printf("Get Index => %d, value => %d\n", -2, p->val); 
    }
    if ((p = GetNodeByIndex(l, -10)) != NULL) {
        printf("Get Index => %d, value => %d\n", -2, p->val); 
    }
    return 0;
}
