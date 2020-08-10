#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void *create() {
	printf("%s:%d: thread id %u\n", __FILE__, __LINE__, pthread_self());
	printf("%s:%d: thred process pid %d\n", __FILE__, __LINE__, getpid());
	return NULL;
}

int main() {
	
	pthread_t tid;
	int res;
	printf("%s:%d: main\n", __FILE__, __LINE__);
	res = pthread_create(&tid, NULL, create, NULL);
	if (res) {
		printf("%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return errno;
	}

	printf("%s:%d: main pid: %d\n", __FILE__, __LINE__, getpid());
	sleep(1);

	return 0;
}
