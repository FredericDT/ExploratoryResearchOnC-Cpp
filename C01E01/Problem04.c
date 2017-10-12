#include<stdio.h>
#define PI 3.14159265
int main() {
	/*
	 * This program is intend to solve the problem on page 3
	 * @author FredericDT
	 */ 
	float radius = 0.0;
	printf("Please input a float number: ");
	scanf("%f", &radius);
	float perimeter = radius > 0.0 ? 2 * PI * radius : 0.0;
	float area = radius > 0.0 ? PI * radius * radius : 0.0;
	printf("The perimiter is %.4lf, the area is %.4lf.", perimeter, area);
	return 0;
}
