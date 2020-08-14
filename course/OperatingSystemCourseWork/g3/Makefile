all: read write remove

clean:
	rm read write remove

read: read.c shm_struct.h
	gcc -Wall -o read read.c

write: write.c shm_struct.h
	gcc -Wall -o write write.c

remove: remove.c shm_struct.h
	gcc -Wall -o remove remove.c

