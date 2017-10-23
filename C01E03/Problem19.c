#include <stdio.h>
#include <math.h>
/*
 * This program is intend to solve the problem on page 23.
 * It prints the result of the quadratic equation.
 *
 * */
int main() {
    float input[3];
    printf("Please input three float numbers: ");
    scanf("%f%f%f", input, input + 1, input + 2);
    if (fabsf(input[0]) <= 1e-6) {
        printf("The equation is not quadratic.");
        return 0;
    }
    float deltaSquare = powf(input[1], 2) - 4 * input[0] * input[2];
    if (fabsf(deltaSquare) <= 1e-6) {
        float root = - input[1] / input[0] / 2.0;
        printf("The equation has two equal roots: %.4f", root);
        return 0;
    }
    if (deltaSquare >= 1e-6) {
        float root0 = (- input[1] + sqrtf(deltaSquare)) / input[0] / 2.0;
        float root1 = (- input[1] - sqrtf(deltaSquare)) / input[0] / 2.0;
        printf("The equation has two distinct real roots: %.4f and %.4f", root0, root1);
        return 0;
    }
    float real = - input[1] / input[0] / 2.0;
    float imageAbs = fabsf(sqrtf(fabsf(deltaSquare)) / input[0] / 2.0);
    printf("The equation has two complex roots: %.4f + %.4fi and %.4f - %.4fi", real, imageAbs, real, imageAbs);
    return 0;
}
