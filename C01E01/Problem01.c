#include<stdio.h>
int main() {
	/*
	 * This program is intend to solve the problem on page 2
	 * @author FredericDT
	 */ 
	int number1 = 1;
	int number2 = 1;
	printf("Please input two integers: ");
	scanf("%d%d", &number1, &number2);
	int sum = number1 + number2;
	int diff = number1 - number2;
	printf("The sum is %d and the difference is %d.", sum, diff);
	return 0;
}
