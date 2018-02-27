#include<stdio.h>
#define SINGLE_FORM "byte"
#define PLURAL_FORM "bytes"
int main() {
	/*
	 * This program is intend to solve the problem on page 4
	 * @author FredericDT
	 */ 
	char a = '0';
	short b = 0;
	int c = 0;
	long d = 0;
	long long e = 0;
	float f = 0.0;
	double g = 0.0;
	printf("Please input seven parts: \n");
	scanf("%c%hi%i%li%lli%f%lf", 
		&a, 
		&b,
		&c,
		&d,
		&e,
		&f,
		&g
	);
	//carry these sizes of those variables
	int sizeOfChar = sizeof(a);
	int sizeOfShort = sizeof(b);
	int sizeOfInt = sizeof(c);
	int sizeOfLong = sizeof(d);
	int sizeOfLongLong = sizeof(e);
	int sizeOfFloat = sizeof(f);
	int sizeOfDouble = sizeof(g);
	printf("The result is: \n"
		"The \'char\' variable is %c, it takes %i %s.\n"
		"The \'short\' variable is %hi, it takes %i %s.\n"
		"The \'int\' variable is %i, it takes %i %s.\n"
		"The \'long\' variable is %li, it takes %i %s.\n"
		"The \'long long\' variable is %lli, it takes %i %s.\n"
		"The \'float\' variable is %f, it takes %i %s.\n"
		"The \'double\' variable is %F, it takes %i %s.\n", 
    a, sizeOfChar, sizeOfChar > 1 ? PLURAL_FORM : SINGLE_FORM,
	b, sizeOfShort, sizeOfShort > 1 ? PLURAL_FORM : SINGLE_FORM, 
	c, sizeOfInt, sizeOfInt > 1 ? PLURAL_FORM : SINGLE_FORM,
	d, sizeOfLong, sizeOfLong > 1 ? PLURAL_FORM : SINGLE_FORM, 
	e, sizeOfLongLong, sizeOfLongLong > 1 ? PLURAL_FORM : SINGLE_FORM,
	f, sizeOfFloat, sizeOfFloat > 1 ? PLURAL_FORM : SINGLE_FORM,
	g, sizeOfDouble, sizeOfDouble > 1 ? PLURAL_FORM : SINGLE_FORM
	);
	return 0;
}
