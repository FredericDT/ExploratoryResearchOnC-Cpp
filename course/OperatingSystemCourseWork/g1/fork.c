#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char** argv) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        printf("hello from the child\n");
    } else if (pid > 0) {
        printf("hello from the parent\n");
    } else {
        printf("fork error\n");
        exit(0);
    }
    return 0;
}

