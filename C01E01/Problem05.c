#include<stdio.h>
#define SINGLE_FORM "byte"
#define PLURAL_FORM "bytes"
int main() {
	/*
	 * This program is intend to solve the problem on page 4
	 * @author FredericDT
	 */ 
	char character = '0';
	short shortInteger = 0;
	int integer = 0;
	long longInteger = 0;
	long long longLongInteger = 0;
	float floatNumber = 0.0;
	double doubleNumber = 0.0;
	printf("Please input seven parts: \n");
	scanf("%c%hi%i%li%lli%f%lf", 
		&character, 
		&shortInteger,
		&integer,
		&longInteger,
		&longLongInteger,
		&floatNumber,
		&doubleNumber
	);
	//carry these sizes of those variables
	int sizeOfChar = sizeof(char);
	int sizeOfShort = sizeof(short);
	int sizeOfInt = sizeof(int);
	int sizeOfLong = sizeof(long);
	int sizeOfLongLong = sizeof(long long);
	int sizeOfFloat = sizeof(float);
	int sizeOfDouble = sizeof(double);
	printf("The result is: \n"
		"The \'char\' variable is %c, it takes %i %s.\n"
		"The \'short\' variable is %hi, it takes %i %s.\n"
		"The \'int\' variable is %i, it takes %i %s.\n"
		"The \'long\' variable is %li, it takes %i %s.\n"
		"The \'long long\' variable is %lli, it takes %i %s.\n"
		"The \'float\' variable is %f, it takes %i %s.\n"
		"The \'double\' variable is %F, it takes %i %s.\n"
	, character, sizeOfChar, sizeOfChar > 1 ? PLURAL_FORM : SINGLE_FORM, 
	shortInteger, sizeOfShort, sizeOfShort > 1 ? PLURAL_FORM : SINGLE_FORM, 
	integer, sizeOfInt, sizeOfInt > 1 ? PLURAL_FORM : SINGLE_FORM,
	longInteger, sizeOfLong, sizeOfLong > 1 ? PLURAL_FORM : SINGLE_FORM, 
	longLongInteger, sizeOfLongLong, sizeOfLongLong > 1 ? PLURAL_FORM : SINGLE_FORM,
	floatNumber, sizeOfFloat, sizeOfFloat > 1 ? PLURAL_FORM : SINGLE_FORM,
	doubleNumber, sizeOfDouble, sizeOfDouble > 1 ? PLURAL_FORM : SINGLE_FORM
	);
	return 0;
}
