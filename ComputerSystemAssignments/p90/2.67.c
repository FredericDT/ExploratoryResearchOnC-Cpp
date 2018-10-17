#include<stdio.h>
#include<limits.h>

int bad_int_size_is_32() {
	unsigned i = UINT_MAX;
	int c = 0;
	while(i >>= 1) {
		++c;
	}
	return c == 31;
}

int main() {
	printf("%d", bad_int_size_is_32());
	return 0;
}
