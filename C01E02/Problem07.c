#include <stdio.h>
/*
 * This program is intend to solve the problem on page 12.
 * It returns the integer splitting by space.
 *
 * */
int main() {
    char *s;
    printf("Please input an integer:");
    scanf("%s", s);
    printf("After the splitting, you can get:");
    int length = 0;
    while (s[length] != '\0') {
        if (length) {
            printf(" ");
        }
        printf("%c", s[length++]);
    }
    printf("\n");
    return 0;
}
