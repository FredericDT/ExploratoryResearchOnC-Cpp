#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h> 
#include <unistd.h>

void *create(void *arg) {
    char *str;
    str = arg;
    printf("The parameter passed from main is %s\n", str);
 
    return (void *)0;
}
 
int main() {
    int error;
    pthread_t id1;
    char *str1 = "Hello!";
    char *attr = str1;
    error = pthread_create(&id1, NULL, create, (void *)attr);
 
    if(error) {
    	fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return errno;
	}
    sleep(1);
 	pthread_join(id1, NULL);
    printf("pthread is created..\n");
    return 0;
}

