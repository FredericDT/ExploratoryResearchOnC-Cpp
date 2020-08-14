all: main

clean:
	rm main

main: main.c semaphore_definitions.h trace_error.h
	gcc -Wall -o main main.c -lpthread
