#ifndef CROSS_COVER_H
#define CROSS_COVER_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

//#define DEBUG //print debug info

struct cc_n {
    int m;
    int p;
};

struct cc_i {
    int *a;
    int s;
};

// 1 for equal 0 for not equal
int eq(struct cc_n s1, struct cc_n s2) {
    return s1.m == s2.m ? s1.p == s2.p : 0;
}

// list of cc_n
struct cc_l_n {
    int s;
    struct cc_n *v;
};

// convert cc_i into list of cc_n
struct cc_l_n * pr_cc_i(struct cc_i i) {
    struct cc_l_n *l = malloc(sizeof(struct cc_l_n));
    l->s = i.s;
    l->v = malloc(sizeof(struct cc_n) * i.s);
    int *c = malloc(sizeof(int) * (l->s + 1));
    memset(c, 0, (l->s + 1) * sizeof(int) / sizeof(unsigned char));
#ifdef DEBUG
    printf("\n");
    for (int k = 0; k < l->s + 1; ++k) {
        printf("%d ", c[k]);
    }
    printf("\n");
#endif
    for (int j = 0; j < l->s; ++j) {
        l->v[j].m = i.a[j];
        l->v[j].p = ++c[l->v[j].m];
    }
    free(c);
    return l;
}

void swap_int(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// quick sort
void sort(int *array, int start, int end) {
    if (start >= end) {
        return;
    }
    int pivot = end;
    int wall = start;
    for (int i = start; i <= end; i++) {
        if (array[i] < array[pivot]) {
            swap_int(array + i, array + wall++);
        }
    }
    swap_int(array + wall, array + pivot);
    sort(array, start, wall - 1);
    sort(array, wall + 1, end);
}

// return may cause memory leak
int * g_child(struct cc_i p1, struct cc_i p2) {
    struct cc_l_n *l_p1 = pr_cc_i(p1);
    struct cc_l_n *l_p2 = pr_cc_i(p2);
#ifdef DEBUG
    for (int i = 0; i < p1.s; ++i) {
        printf("(%d,%d)", l_p1->v[i].m, l_p1->v[i].p);
    }
    printf("\n");
    for (int i = 0; i < p2.s; ++i) {
        printf("(%d,%d)", l_p2->v[i].m, l_p2->v[i].p);
    }
    printf("\n");
#endif
    srand(time(0)); // init the rand func

#ifdef DEBUG
    int a = 2;
    int b = 5;
#else
    int a = rand() % (l_p1->s);
    int b = rand() % (l_p1->s - a + !a) + a;
#endif


    int l = b - a;
    int *c = malloc(sizeof(int) * l);
    memset(c, 0, l * sizeof(int) / sizeof(unsigned char));
    //int c_v[l] = {0};
    for (int i = 0; i < l; ++i) {
        int p1_id = i + a;
        for (int j = 0; j < l_p2->s; ++j) {
            if (eq(l_p1->v[p1_id], l_p2->v[j])) {
                c[i] = j;
                //c_v[l] = l_p1.v[p1_id].m;
                break;
            }
        }
    }
    sort(c, 0, l - 1);
    int *r = malloc(sizeof(int) * l_p1->s);
    for (int i = a; i < b; ++i) {
        r[i] = l_p1->v[i].m;
    }
    int c_id = 0;
    int m_p = 0;
    while (m_p >= a && m_p < b) {
        ++m_p;
    }
    for (int i = 0; i < l_p1->s; ++i) {
        //if (i >= a && i < b) {
        //    continue;
        //}
        if (i == c[c_id]) {
            ++c_id;
        } else {
            r[m_p] = l_p2->v[i].m;
            ++m_p;
            while(m_p >= a && m_p < b) {
                ++m_p;
            }
        }
    }
    free(c);
    free(l_p1->v);
    free(l_p1);
    free(l_p2->v);
    free(l_p2);
    return r;
}

#endif
