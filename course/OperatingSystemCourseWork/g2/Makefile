all: pthread_clean       pthread_composite   pthread_create      pthread_exit        pthread_join        pthread_self

clean:
	rm pthread_clean       pthread_composite   pthread_create      pthread_exit        pthread_join        pthread_self

pthread_clean:
	gcc -Wall -o pthread_clean pthread_clean.c -lpthread

pthread_composite:
	gcc -Wall -o pthread_composite pthread_composite.c -lpthread

pthread_create:
	gcc -Wall -o pthread_create pthread_create.c -lpthread

pthread_exit:
	gcc -Wall -o pthread_exit pthread_exit.c -lpthread

pthread_join:
	gcc -Wall -o pthread_join pthread_join.c -lpthread

pthread_self:
	gcc -Wall -o pthread_self pthread_self.c -lpthread
