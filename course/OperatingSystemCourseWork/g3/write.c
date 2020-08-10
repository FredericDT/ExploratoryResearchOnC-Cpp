#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "shm_struct.h"

int main(int argc, char** argv) {
	int shm_id, i;
	key_t key;
	char temp[8];
	struct people *people_shm_map;
	char pathname[30];
	strcpy(pathname, "/tmp\0");
	
	/* ftok - convert a pathname and a project identifier to a System V IPC key */
	key = ftok(pathname, 0x03);
	if (key == -1) {
		fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 1;
	}
	printf("key = %d\n", key);
	shm_id = shmget(key, sizeof(struct people), IPC_CREAT | IPC_EXCL | 0600);
	if (shm_id == -1)
	{
		fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return 2;
	}

	printf("shm_id = %d\n", shm_id);
	people_shm_map = (struct people *) shmat(shm_id, NULL, 0);
	memset(temp, 0x00, sizeof(temp));
	strcpy(temp, "name_");
	temp[5]='0';
	temp[6]='\0';

	for (i=0; i<3; ++i) {
		temp[5] += 1;
		strncpy((people_shm_map + i)->name, temp, 7);
		(people_shm_map + i)->age = 0 + i;
	}

	shmdt(people_shm_map);
	return 0;
}

