#include <stdio.h>

int main() {

	int r = 0;
	int i = 0;
	int s = 0;
	scanf("%d", &s);
	s = s * 2 - 1;
	for (int j = 0; j < s; ++j) {
		scanf("%d", &i);
		r ^= i;
	}
	printf("%d\n", r);
	return 0;
}
