#include <stdio.h>
/*
 * calc polygon
 */
int main() {
    int poly[100] = {0};
    int end = 0;
    int degree = 0;
    int maxDegree = 0;
    while (scanf("%d%d", &degree, &end) > 0) {
        poly[degree] += end;
        if (degree > maxDegree) {
            maxDegree = degree;
        }
    }
    for (int i = maxDegree; i >= 0; i--) {
        if (poly[i] > 0) {
            if (i != maxDegree) {
                printf("+");
            }
            printf("%d", poly[i]);
            if (i > 0) {
                printf("x");
                if (i > 1) {
                    printf("%d", i);
                }
            }
        }
    }
    return 0;
}
