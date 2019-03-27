#include "list.h"
#include <stdio.h>
#include <stdlib.h>

List *Init(ElemType *arr, int n) {
    
}

void Insert(Node *p, ElemType i) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->val = i;
    n->list = p->list;
    n->next = p->next;
    p->next = n;
}


//技巧: 修改p的值并将p的下一个指针指向下下一个间接实现删除p元素
void Delete(Node *p) {
    Node *temp;
    temp = p->next;
    p->val = p->next->val;
    p->next = p->next->next;
    free(temp);
}

//奇数个: n/2+1
//偶数个: n/2
Node *FindMidNode(Node *head) {
    Node *slow, *fast;
    slow = fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//找到倒数第K个Node节点
/*
       1 -> 2 -> 3 -> k ... -> n-k+1 -> n

       1 -> 2 -> 3 -> k ... -> n-k+1 -> n
       |              |
      temp1         temp2

       1 -> 2 -> 3 -> k ... -> n-k+1 -> n -> NULL
                                |       |
                               temp1  temp2
                            
*/
Node *FindKNode(Node *head, int index) {
    if (head == NULL) {
        return NULL; 
    }
    Node *temp1, *temp2;
    temp1 = temp2 = head;
    while(k--) {
        if(temp2 == NULL){
            return NULL;
        }
        temp2 =temp2->next;
    }
    while (temp2->next != NULL && temp2->next->next!=NULL) {
        temp1 = temp1->next;
        temp2 = temp2->next->next;
    }
    return temp1; 
}

//判断链表是否存在环, 如果存在,则返回环的长度

/*
        1 -> 2 -> 3 -> 4 -> 5 -> 6
       / \
   slow   fast
        1 -> 2 -> 3 -> 4 -> 5 -> 6
             |    |      
           slow  fast
        1 -> 2 -> 3 -> 4 -> 5 -> 6
                  |         |      
                slow       fast
        1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
                       |                |  
                     slow             fast
*/
int getLoopLength(Node* head){
    if(head == NULL) {
        return 0;
    }
    Node *slow, *fast;
    slow = fast = head;
    int length = 0;
    while(slow != fast && fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        length++;
    }
    if(fast == NULL) {
        return 0;
    }
    return length;
}
