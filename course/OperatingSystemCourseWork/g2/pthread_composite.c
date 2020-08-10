#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define THREAD_NUMBER 3
#define REPEAT_NUMBER 5
#define DELAY_TIME_LEVELS 10.0

void *thread_function(void *arg) {
	int thread_number = (int) arg;
	int delay_time = 0;
	int count = 0;

	printf("%s:%d: Thread %d starting\n", __FILE__, __LINE__, thread_number);

	for (; count < REPEAT_NUMBER; ++count) {
		delay_time = (int) (rand() * DELAY_TIME_LEVELS / (RAND_MAX)) + 1;
		sleep(delay_time);
		printf("%s:%d:\tThread %d: job %d delay = %d\n", __FILE__, __LINE__, thread_number, count, delay_time);
	}

	printf("%s:%d: Thread %d finished\n", __FILE__, __LINE__, thread_number);
	pthread_exit(NULL);
}

int main() {
	pthread_t thread[THREAD_NUMBER];
	int no, res;
	void *thread_ret;
	
	srand(time(NULL));

	for (no = 0; no < THREAD_NUMBER; ++no) {
		res = pthread_create(&thread[no], NULL, (void *) thread_function, (void *) no);
		if (res) {
			fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
			exit(errno);
		}
	}

	printf("%s:%d: Threads created\n", __FILE__, __LINE__);
	for (no = 0; no < THREAD_NUMBER; ++no) {
		res = pthread_join(thread[no], &thread_ret);
		if (!res) {
			printf("%s:%d: Thread %d joined\n", __FILE__, __LINE__, no);
		} else {
			fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		}
	}
	
	return 0;
}
