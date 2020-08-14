COMMON_FLAG=-Wall
all: exec exit fork getpid kill signal wait

clean: 
	rm exec exit fork getpid kill signal wait

exec: exec.c
	gcc ${COMMON_FLAG} -o exec exec.c

exit: exit.c
	gcc ${COMMON_FLAG} -o exit exit.c

fork: fork.c
	gcc ${COMMON_FLAG} -o fork fork.c

getpid: getpid.c
	gcc ${COMMON_FLAG} -o getpid getpid.c

kill: kill.c
	gcc ${COMMON_FLAG} -o kill kill.c

signal: signal.c
	gcc ${COMMON_FLAG} -o signal signal.c

wait: wait.c
	gcc ${COMMON_FLAG} -o wait wait.c
