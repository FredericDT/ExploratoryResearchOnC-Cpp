#include <cstdio>
#include <iostream>

template<typename T>
struct node {
    T value;
    struct node *next;
};

template<typename T>
int remove(struct node<T> *n, int k1, int k2, void (*f)(T v)) {
    if (k1 > k2) {
        return 1;
    }
    if (k1 == k2) {
        return 0;
    }
    int i = 1;
    while (n->next && i < k1) {
        n = n->next;
        ++i;
    }
    if (i != k1) {
        return 2;
    }
    while (n->next && i < k2) {
        struct node<T> *p = n->next;
        n->next = n->next->next;
        f(p->value);
        delete p;
        ++i;
    }
    if (i != k2) {
        return 2;
    }
    return 0;
}

template<typename T>
struct node<T> *create(T e[], int size) {
    struct node<T> *head = new struct node<T>();
    struct node<T> *c = head;
    for (int i = 0; i < size; ++i) {
        c->next = new struct node<T>();
        c = c->next;
        c->value = e[i];
    }
    return head;
}

template<typename T>
void reverse(T e[], int n) {
    int i = 0;
    --n;
    while (i < n) {
        T t = e[i];
        e[i] = e[n];
        e[n] = t;
        ++i;
        --n;
    }
}

template<typename T>
void freeLinkedList(struct node<T> *n, void (*f)(T v)) {
    if (n->next) {
        freeLinkedList(n->next, f);
    }
    f(n->value);
    delete n;
}

void f(int i) {}

int main(int argc, char **argv) {
    int i[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    struct node<int> *l = create(i, 10);
    remove(l, 2, 7, &f);
    reverse(i, 10);
    freeLinkedList(l, &f);
    std::cout << "hi";
    return 0;
}