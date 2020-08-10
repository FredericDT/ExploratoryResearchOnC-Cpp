#include<stdio.h> 
#include<sys/wait.h> 
#include<unistd.h> 
  
int main() {
    pid_t pid = fork();
    int wstats;
    if (pid == 0) {
        printf("HC: hello from child\n"); 
	sleep(1);
    } else { 
        printf("HP: hello from parent\n");
        kill(pid, SIGTERM);	
        wait(&wstats); 
        printf("CT: child has terminated: %x\n", WEXITSTATUS(wstats)); 
    } 
  
    printf("Bye\n"); 
    return 0; 
}
