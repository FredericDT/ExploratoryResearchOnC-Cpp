#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} *Node;

void *newNode() {
    return malloc(sizeof(struct node));
}

void input(Node n, const char *name) {
    printf("Please input %s:", name);
    int i = 0;
    while (scanf("%d", &i)) {
        if (i < 0) {
            n->next = 0;
            break;
        }
        n->next = newNode();
        n->next->value = i;
        n->next->next = 0;
        n = n->next;
    }
}

void printList(Node h) {
    if (!(h->next)) {
        printf("EMPTY LIST\n");
        return;
    }
    while (h->next) {
        if (h->next->next) {
            printf("%d ", h->next->value);
        } else {
            printf("%d\n", h->next->value);
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

int main() {
    Node headA = newNode();
    Node headB = newNode();

    input(headA, "A");
    input(headB, "B");

    Node a = headA;
    Node b = headB;

    if (b->next) {
        while (a->next) {
            if (a->next->value > b->next->value) {
                Node an = a->next;
                a->next = b->next;
                b->next = b->next->next;
                a->next->next = an;
            } else if (a->next->value == b->next->value) {
                while (b->next && a->next->value == b->next->value) {
                    b = b->next;
                }
            } else {
                a = a->next;
            }
        }

        while (b->next) {
            while (b->next->next && b->next->value == b->next->next->value) {
                b = b->next;
            }
            a->next = b->next;
            b->next = b->next->next;
            a->next->next = 0;
            a = a->next;
        }

    }

    printf("A");
    printList(headA);
    printf("B");
    printList(headB);
    freeList(headA);
    freeList(headB);

    return 0;
}
