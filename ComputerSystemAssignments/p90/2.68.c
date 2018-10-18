#include<stdio.h>

int lower_one_mask(int n) {
	return ((unsigned) 0xffffffff) >> (32 - n);
}

/*
int lower_one_mask(int n) {
	int r = 1;
	n == 2 && r = 3;
	n == 3 && r = 7;
	...
	return r;
}
*/

int main() {
	printf("%X", lower_one_mask(17));
	return 0;
}
