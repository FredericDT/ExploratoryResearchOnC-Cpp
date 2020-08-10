#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "shm_struct.h"

int main(int argc, char** argv) {
	
	int shm_id,i;
	key_t key;
	struct people* p_map;
	char pathname[30];
	strcpy(pathname, "/tmp\0");
	key = ftok(pathname,0x03);
	if (key == -1) {
		fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return errno;
	}
	printf("key = %d\n", key);
	shm_id = shmget(key, 0, 0);
	if (shm_id == -1) {
		fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return errno;
	}
	printf("shm_id = %d\n", shm_id);
	p_map = (struct people*) shmat(shm_id, NULL, 0);
	for(i=0; i<3; ++i) {
		printf("name:%s\n",(*(p_map+i)).name);
		printf("age:%d\n",(*(p_map+i)).age);
	}
	if (shmdt(p_map) == -1 ) {
		fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, strerror(errno));
		return errno;
	} 

	return 0;
}
