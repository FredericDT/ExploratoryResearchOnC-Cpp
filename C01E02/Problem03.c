#include <stdio.h>
/*
 * This program is intend to solve the problem on page 9.
 * It returns the result of a integer number powering a non-negative integer.
 *
 * */
int main() {
    int bottom = 0, power = 0;
    printf("Please input two integers: ");
    scanf("%d%d", &bottom, &power);
    int result = 1;
    for (int i = 0; i < power; i++) {
        result *= bottom;
    }
    printf("The result of %d to power %d is %d.", bottom, power, result);
    return 0;
}
