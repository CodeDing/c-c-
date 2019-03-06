#ifndef __LIST_H__
#define __LIST_H__

typedef int ElemType;

typedef struct Node {
    ElemType val;
    struct Node *next;
    struct List *list;
} Node;

typedef struct List {
    struct Node *head, *tail;
} List;

void Insert(Node *p, ElemType i);
void Delete(Node *p);
Node* FindKNode(Node *head, int index);
Node* ReverseNode(Node *head);

#endif
