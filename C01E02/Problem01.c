#include <stdio.h>
int main() {
    int a = 0, b = 0;
    printf("Please input two integers: ");
    scanf("%d%d", &a, &b);
    if (a < b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    printf("The larger number is %d, the smaller number is %d.", a, b);
    return 0;
}
