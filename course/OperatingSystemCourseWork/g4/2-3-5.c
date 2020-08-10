#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
 
static int a = 5;
 
void *create(void *arg)
{
    printf("New pthread...\n");
    printf("a = %d\n",a);
 
    return (void *)0;
}
 
int main(int argc, const char *argv[])
{
    int error;
    pthread_t id1;
 
    error = pthread_create(&id1, NULL, create, NULL);
    if(error != 0)
    {
        printf("new thread is not created!\n");
        return -1;
    }
    pthread_join(id1, NULL);
    printf("New thread is created...\n");
 
    return 0;
}

