#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void *thread(void *str) {
	for (int i = 0; i < 4; ++i) {
		sleep(2);
		printf("%s:%d: thread: %d\n", __FILE__, __LINE__, i);
	}
	return NULL;
}

int main() {
	
	pthread_t pth;

	int i;	

	int ret = pthread_create(&pth, NULL, thread, (void *)(i));
	pthread_join(pth, NULL);
	for (i = 0; i < 3; ++i) {
		sleep(1);
		printf("%s:%d: main: %d\n", __FILE__, __LINE__, i);
	}
	
	return 0;
}
