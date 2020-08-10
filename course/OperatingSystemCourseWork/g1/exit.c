#include<stdio.h> 
#include<sys/wait.h> 
#include<unistd.h> 
  
int main() 
{ 
    int wstats;
    if (fork() == 0) {
        printf("HC: hello from child\n"); 
    	_exit(0x10);
    } else { 
        printf("HP: hello from parent\n"); 
        wait(&wstats); 
        printf("CT: child has terminated: %x\n", WEXITSTATUS(wstats)); 
    } 
  
    printf("Bye\n"); 
    return 0; 
}
