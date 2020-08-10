#include <sys/types.h>
#include <unistd.h>

#include <sys/types.h>

#include <stdio.h>

int main() {
	pid_t fork_pid = fork();

	printf("fork() = %d, getpid() = %d, getppid() = %d\n", fork_pid, getpid(), getppid());

	return 0;
}
