#include<stdio.h>

int lower_one_mask(int n) {
	int r = 1;
	for (int i = 1; i < n; ++i) {
		r <<= 1;
		r += 1;
	}
	return r;
}

int main() {
	printf("%X", lower_one_mask(17));
	return 0;
}
