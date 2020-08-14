#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int quit = 1;

void handler(int t) {
	printf("%d\n", getpid());
	quit = 0;
}

int main() {
	
	struct sigaction action = { &handler, 0, 0, NULL, NULL };

	sigaction(SIGQUIT, &action, NULL);

	while(quit);

	return 0;   
}
