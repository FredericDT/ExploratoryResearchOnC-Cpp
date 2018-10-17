#include<stdio.h>

int odd_ones(unsigned x) {
	return x >> 1 ? !(odd_ones(x >> 1) ^ (x & 1)) : 0;
}

int main() {
	printf("%d", odd_ones(8));
	return 0;
}
