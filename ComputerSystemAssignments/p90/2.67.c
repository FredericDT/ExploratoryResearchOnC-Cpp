#include<stdio.h>
#include<limits.h>

int bad_int_size_is_32() {
	return (long) INT_MAX == 2147483647L;
}

int main() {
	printf("%d", bad_int_size_is_32());
	return 0;
}
