#include <stdio.h>
/*
 * This program is intend to solve the problem on page 18.
 * It prints the count of the English characters, spaces, numbers and other characters.
 *
 * */
int main() {
    char input[100];
    //printf("please input a string: ");
    int length = 0;
    while (length < 100) {
        char current = getchar();
        if (current == '\n') {
            break;
        }
        input[length++] = current;
    }
    //printf("%s",input);
    int sumOfEngChar = 0, sumOfSpace = 0, sumOfNumber = 0, sumOfOther = 0, index = 0;
    for (index = 0; index < length; ) {
        if (('a' <= input[index] && input[index] <= 'z') || ('A' <= input[index] && input[index] <= 'Z')) {
            sumOfEngChar++;
        } else if (' ' == input[index]) {
            sumOfSpace++;
        } else if ('0' <= input[index] && input[index] <= '9') {
            sumOfNumber++;
        } else {
            sumOfOther++;
        }
        index++;
    }
    printf("The number of English characters, spaces, numbers, other characters are: %d %d %d %d",
           sumOfEngChar, sumOfSpace, sumOfNumber, sumOfOther);
    return 0;
}
