#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

void *create() {
	printf("pthread created.\n");
	pthread_exit((void *)6);
}

int main() {
	
	pthread_t tid;
	int res;
	void *tmp;

	res = pthread_create(&tid, NULL, create, NULL);
	printf("main thread\n");

	if (res) {
		printf("%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 1;
	}

	res = pthread_join(tid, &tmp);
	if (res) {
		printf("%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 2;
	}

	printf("Thread exit code %d \n", (int)tmp);

	return 0;
}
