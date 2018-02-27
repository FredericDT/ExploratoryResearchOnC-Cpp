#include <stdio.h>
/*
 * This program is intend to solve the problem on page 18.
 * It prints the square of the sum of the numbers which can be divided into 3 or 7.
 *
 * */
int main() {
    int input = 0;
    printf("Please input an integer: ");
    scanf("%d", &input);
    int sum = 0;
    for (int i = 21; i < input; i += 21) {
        sum += i;
    }
    sum *= sum;
    printf("The result is: %d", sum);
    return 0;
}
