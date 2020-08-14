#include <stdio.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

void func() {
	printf("It is signal 17 processing function!\n");
}

int main() {
	int i;
	signal(17, func); 
	if ((i = fork())) {
		printf("Parent:Signal 17 will be send to child!\n"); 
		kill(i, 17); 
		wait(NULL); 
		printf("Parent:finished!\n");
	} else {
		sleep(10); 
		printf("Chi1d:A signal from my Parent is received!\n"); 
		exit(0);
	}
	return 0;
}
