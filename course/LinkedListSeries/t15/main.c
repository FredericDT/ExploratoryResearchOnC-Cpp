#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char value;
    struct node *next;
} *Node;

void *newNode() {
    return malloc(sizeof(struct node));
}

void printList(Node h) {
    if (!(h->next)) {
        printf("EMPTY LIST\n");
        return;
    }
    while (h->next) {
        if (h->next->next) {
            printf("%c ", h->next->value);
        } else {
            printf("%c\n", h->next->value);
        }
        h = h->next;
    }
}

void freeList(Node h) {
    if (h->next) {
        freeList(h->next);
    }
    free(h);
}

Node insertNode(Node n, char value) {
    Node i = newNode();
    i->value = value;
    i->next = 0;
    n->next = i;
    return i;
}

Node parseHash(const int hash[128],int i, Node n) {
    for (int k = 0; k < hash[i]; ++k) {
        n = insertNode(n, (char) i);
    }
    return n;
}

int main() {
    int hash[128] = {0};
    //input
    char c[2];
    while (scanf("%s", c)) {
        
        if (! strcmp("-1", c)) {
            break;
        }
        ++hash[c[0]];
    }
    Node oHead = newNode();
    Node iHead = newNode();
    Node lHead = newNode();

    Node o = oHead;
    Node i = iHead;
    Node l = lHead;
    //o
    for (int j = 0; j < 48; ++j) {
        o = parseHash(hash, j, o);
    }
    //i
    for (int j = 48; j < 58; ++j) {
        i = parseHash(hash, j, i);
    }
    //o
    for (int j = 58; j < 65; ++j) {
        o = parseHash(hash, j, o);
    }
    //L
    for (int j = 65; j < 91; ++j) {
        l = parseHash(hash, j, l);
    }
    //o
    for (int j = 91; j < 97; ++j) {
        o = parseHash(hash, j, o);
    }
    //l
    for (int j = 97; j < 123; ++j) {
        l = parseHash(hash, j, l);
    }
    //o
    for (int j = 123; j < 128; ++j) {
        o = parseHash(hash, j, o);
    }

    printf("o ");
    printList(oHead);
    printf("i ");
    printList(iHead);
    printf("l ");
    printList(lHead);

    freeList(o);
    freeList(i);
    freeList(l);
    return 0;
}
