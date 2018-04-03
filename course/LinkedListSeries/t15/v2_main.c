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

void inputData(Node h) {
    char c[3];
    while (scanf("%s", c)) {

        if (! strcmp("-1", c)) {
            break;
        }
        h->next = newNode();
        h->next->value = c[0];
        h = h->next;
        h->next = 0;
    }
}

int getCharType(char i) {
    if (i < 58 && i >= 48) {
        return 1;
    }
    if (i < 91 && i >= 65) {
        return 2;
    }
    if (i < 123 && i >= 97) {
        return 2;
    }
    return 0;
}

int main() {
    Node inputOriginData = newNode();

    inputData(inputOriginData);

    Node separatedList[3] = {newNode(), newNode(), newNode()};
    // o i l

    Node proces[3] = {separatedList[0], separatedList[1], separatedList[2]};

    while (inputOriginData->next) {
        Node o = inputOriginData;
        Node min = 0;
        while (o->next) {
            if (min) {
                if (o->next->value < min->next->value) {
                    min = o;
                }
            } else {
                min = o;
            }
            o = o->next;
        }
        int type = getCharType(min->next->value);
        proces[type]->next = min->next;
        min->next = min->next->next;
        proces[type]->next->next = 0;
        proces[type] = proces[type]->next;
    }

    printf("o: ");
    printList(separatedList[0]);
    printf("i: ");
    printList(separatedList[1]);
    printf("l: ");
    printList(separatedList[2]);

    for (int i = 0; i < 3; ++i) {
        freeList(separatedList[i]);
    }

    freeList(inputOriginData);

    return 0;
}
