#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "shm_struct.h"

int main(int argc, char** argv) {
	int shm_id;
	key_t key;
	char pathname[30];
	strcpy(pathname, "/tmp\0");
	
	/* ftok - convert a pathname and a project identifier to a System V IPC key */
	key = ftok(pathname, 0x03);
	if (key == -1) {
		fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 1;
	}
	printf("key = %d\n", key);
	shm_id = shmget(key, sizeof(struct people), IPC_EXCL | 0600);
	if (shm_id == -1)
	{
		fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 2;
	}

	printf("shm_id = %d\n", shm_id);

	if (shmctl(shm_id, IPC_RMID, NULL)) {
		fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return errno;
	}

	return 0;
}

