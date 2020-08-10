#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void *pthread1() {
	for (int i = 0; i < 5; ++i) {
		printf("pthread1\n");
		sleep(2);
	}
} 

void *pthread2() {
	for (int i = 0; i < 5; ++i) {
		printf("pthread2\n");
		sleep(2);
	}
} 

int main() {

	pthread_t id1, id2;
	int res = pthread_create(&id1, NULL, pthread1, NULL);
	if (res) {
		printf("%s\n", strerror(errno));
		return 1;
	}

	res = pthread_create(&id2, NULL, pthread2, NULL);
	if (res) {
		printf("%s\n", strerror(errno));
		return 1;
	}

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

	return 0;
}
