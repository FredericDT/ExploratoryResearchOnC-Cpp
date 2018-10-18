#include<stdio.h>

int lower_one_mask(int n) {
	int r = 1;
	n != 1 && (r = (lower_one_mask(n - 1) << 1) + 1);
	return r; 
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
