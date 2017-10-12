#include<stdio.h>
int main() {
	/*
	 * This program is intend to solve the problem on page 2
	 * @author FredericDT
	 */ 
	char sex = ' ';
	printf("Please input sex: ");
	scanf("%c", &sex);
	int age = 0;
	printf("Please input age: ");
	scanf("%d", &age);
	float height = 0.0;
	printf("Please input height: ");
	scanf("%f", &height);
	printf("The sex is %c, the age is %d, and the height is %f.", sex, age, height);
	return 0;
}
