CC = gcc
CFLAGS = -Wall -static -O2
all: list.o
	${CC} ${CFLAGS} list.o -o list && chmod u+x list

list: list.c
	${CC} ${CFLAGS} list.c -o list.o

clean:
	rm list list.o
