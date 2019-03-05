#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256
#define MAXLEN 256

#define true 1
#define false 0

typedef  char bool;
typedef struct TrieNode {
    int count;
    struct TrieNode *next[MAX];
}TrieNode;

void Insert(char *word, TrieNode *root) {
    if(word[0] == '\0') return;
    int i;
    TrieNode *cur;
    cur = root;
    for(i = 0; word[i] != '\0'; i++) {
        if (cur->next[word[i]] == NULL) {
            TrieNode *new = (TrieNode*)malloc(sizeof(TrieNode)); 
            memset(new, 0, sizeof(TrieNode));
            cur->next[word[i]] = new;
        } 
        cur = cur->next[word[i]];
    }
    cur->count++;
    return;
}

void Construct(TrieNode **root) {
    char inStr[MAXLEN];
    int size = 0;
    *root = (TrieNode *)malloc(sizeof(TrieNode));
    memset(*root, 0, sizeof(TrieNode));
    while(1) {
        scanf("%s", inStr); 
        printf("Input str: %s\n", inStr);
        if(strcmp(inStr, "*") == 0) break;
        Insert(inStr, *root);
    }
    return ;
}

void Traverse(TrieNode *cur) {
    static char theWord[MAXLEN];
    static int pos = 0;
    int i;
    if(cur == NULL) return;
    if(cur->count) {
        printf("pos = %d\n", pos);
        theWord[pos] = '\0';
        printf("word => %s : count => %d\n", theWord, cur->count);
    }
    for(i = 0; i < MAX; i++) {
        theWord[pos++] = i; 
        //printf("i = %d, pos = %d\n", i, pos);
        Traverse(cur->next[i]);
        pos--;
        //printf("pos-- = %d\n", pos);
    }
    return;
}

bool Find(TrieNode *root, char *word) {
    int i;
    TrieNode *cur;
    cur = root;
    for(i = 0; word[i] != '\0'; i++) {
        if(cur->next[word[i]] == NULL) return false;
        cur = cur->next[word[i]];
    }
    if(cur->count) return true;
    return false;
}

int main() {
    TrieNode *root;
    char str[MAXLEN];
    Construct(&root);
    printf("\n");
    Traverse(root);
    printf("\n");
    while(1) {
        scanf("%s", str); 
        if (strcmp(str, "*") == 0) break; 
        printf("%s: %d\n", str, Find(root,str));    
    }
    return 0;
}
