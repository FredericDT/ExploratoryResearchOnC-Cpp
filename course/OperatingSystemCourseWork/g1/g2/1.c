#include<stdio.h> 
#include<sys/wait.h> 
#include<unistd.h> 

int main() {
	int i, j, k;
	int wstats;
	if (i = fork()) {
		j = wait(&wstats);
		printf("Parent process！\n");
		printf("i=%d  j=%d\n", i, j);
	} else {
		k = getpid();
		printf("Child process！\n");
		printf("i=%d  k=%d\n", i, k);
	}
	return 0;
}
