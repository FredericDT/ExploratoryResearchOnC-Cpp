#include <stdio.h>
#include <math.h>
/*
 * This program is intend to solve the problem on page 10.
 * It returns the area of the triangle, which was defined by three integers,
 * recognized as the lengths of the lines.
 *
 * */
int main() {
    int input[3];
    printf("Please input three integers:");
    scanf("%d%d%d", input, input + 1, input + 2);
    float s = (0.0 + input[0] + input[1] + input[2]) / 2.0;
    float area = sqrtf(s * (s - input[0]) * (s - input[1]) * (s - input[2]));
    printf("The area of the triangle is %.3f.", area);
    return 0;
}
