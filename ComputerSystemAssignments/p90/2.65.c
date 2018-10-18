#include<stdio.h>

int odd_ones(unsigned x) {
	return x != 0 && (odd_ones(x >> 1) ^ (x & 0b1));
}

int main() {
	printf("%d", odd_ones(3));
	return 0;
}
