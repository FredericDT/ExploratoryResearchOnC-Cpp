#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

void *clean(void *arg) {
	printf("%s:%d: cleanup: %s\n", __FILE__, __LINE__, (char *)arg);
	return (void *)0;
}

void *thread_function_1(void *arg) {
	printf("%s:%d: thread 1 started\n", __FILE__, __LINE__);

	pthread_cleanup_push((void *)clean, "thread 1 handler 1");
	pthread_cleanup_push((void *)clean, "thread 1 handler 2");

	printf("%s:%d: thread1 push completed\n", __FILE__, __LINE__);

	if (arg) {
		return (void *)1;
	}

	pthread_cleanup_pop(1); // pop accordingly line 13
	pthread_cleanup_pop(1); // pop accordingly line 12
	
	return (void *)2;	
}

void *thread_function_2(void *arg) {
	printf("%s:%d: thread 2 started\n", __FILE__, __LINE__);
	
	pthread_cleanup_push((void *)clean, "thread 2 handler 1");
	pthread_cleanup_push((void *)clean, "thread 2 handler 2");
	
	printf("%s:%d: thread2 push completed\n", __FILE__, __LINE__);
	
	if (arg) {
	    return (void *)3;
	}   
	
	pthread_cleanup_pop(1); // pop accordingly line 31
	pthread_cleanup_pop(0); // pop accordingly line 30, cleanup not executed
	    
	return (void *)4;   
}

int main() {
	int res;
	pthread_t tid1, tid2;
	
	void *thread_ret;

	res = pthread_create(&tid1, NULL, thread_function_1, (void *)1);
	if (res) {
		printf("%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 1;
	}

	res = pthread_create(&tid2, NULL, thread_function_2, (void *)0);
	if (res) {
		printf("%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 1;
	}
	res = pthread_join(tid1, &thread_ret);
	if (res) {
		printf("%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 2;
	}
	printf("%s:%d: thread1 exit code: %d\n", __FILE__, __LINE__, (int) thread_ret);

	res = pthread_join(tid2, &thread_ret);
	if (res) {
		printf("%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 2;
	}
	printf("%s:%d: thread2 exit code: %d\n", __FILE__, __LINE__, (int) thread_ret);
	
	return 0;
}
