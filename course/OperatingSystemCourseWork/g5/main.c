#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

/*
 * This file should be linked with -pthread
 */

#include <string.h>
#include <errno.h>

#include <stdlib.h>          /* For exit */
#include <unistd.h>          /* For sleep */
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/wait.h>        /* For wait */

#include "semaphore_definitions.h"
#include "trace_error.h"

#define CREATE_SEM(sem_target, name, oflag, mode, value) if ((sem_target = sem_open(name, oflag, mode, value)) == SEM_FAILED) { eprintf("%s\n", strerror(errno)); exit(errno); }

int quit = 1;

void handler() {
    iprintf("SIGINT: %d\n", getpid());
    quit = 0;
}

int main() {

    sem_t *sem_mutex, *sem_space_total, *sem_space_A, *sem_space_B, *sem_storage_A, *sem_storage_B;

    CREATE_SEM(sem_mutex, SEM_MUTEX, 0700, O_CREAT, SEM_MUTEX_INIT_VALUE)
    CREATE_SEM(sem_space_total, SEM_SPACE_TOTAL, 0700, O_CREAT, SEM_SPACE_TOTAL_INIT_VALUE)
    CREATE_SEM(sem_space_A, SEM_SPACE_A, 0700, O_CREAT, SEM_SPACE_A_INIT_VALUE)
    CREATE_SEM(sem_space_B, SEM_SPACE_B, 0700, O_CREAT, SEM_SPACE_B_INIT_VALUE)
    CREATE_SEM(sem_storage_A, SEM_STORAGE_A, 0700, O_CREAT, SEM_STORAGE_A_INIT_VALUE)
    CREATE_SEM(sem_storage_B, SEM_STORAGE_B, 0700, O_CREAT, SEM_STORAGE_B_INIT_VALUE)

    iprintf("sem_created\n");

    int mutex_sval = 0, space_total_sval = 0, space_A_sval = 0, space_B_sval = 0, storage_A_sval = 0, storage_B_sval = 0;

    EXIT_ERRNO(sem_getvalue(sem_mutex, &mutex_sval))
    EXIT_ERRNO(sem_getvalue(sem_space_total, &space_total_sval))
    EXIT_ERRNO(sem_getvalue(sem_space_A, &space_A_sval))
    EXIT_ERRNO(sem_getvalue(sem_space_B, &space_B_sval))
    EXIT_ERRNO(sem_getvalue(sem_storage_A, &storage_A_sval))
    EXIT_ERRNO(sem_getvalue(sem_storage_B, &storage_B_sval))

    iprintf("mutex_sval = %d, space_total_sval = %d, space_A_sval = %d, space_B_sval = %d, storage_A_sval = %d, storage_B_sval = %d\n", 
        mutex_sval, space_total_sval, space_A_sval, space_B_sval, storage_A_sval, storage_B_sval);

    struct sigaction action = { &handler, 0, 0, 0, 0 };
    sigaction(SIGINT, &action, NULL);
    
    if (fork() == 0) {

        iprintf("PRODUCE_A_PID = %d\n", getpid());

        while(quit) {

            sem_wait(sem_mutex);    
            EXIT_ERRNO(sem_getvalue(sem_space_A, &space_A_sval))
            EXIT_ERRNO(sem_getvalue(sem_space_total, &space_total_sval))
            
            if (space_total_sval >= PART_A_PER_TIME_PRODUCE && space_A_sval >= PART_A_PER_TIME_PRODUCE) {
            
                for (int i = 0; i < PART_A_PER_TIME_PRODUCE; ++i) {
                    sem_wait(sem_space_A);
                    sem_post(sem_storage_A);
                    sem_wait(sem_space_total);
                }
                iprintf("PART_A_PRODUCE_EVENT\n");
            }
            
            sem_post(sem_mutex);
            sleep(1);
        }

        iprintf("PRODUCE_A_END\n");

    } else if (fork() == 0) {
        iprintf("PRODUCE_B_PID = %d\n", getpid());

        while(quit) {
            sem_wait(sem_mutex);    
            EXIT_ERRNO(sem_getvalue(sem_space_B, &space_B_sval))
            EXIT_ERRNO(sem_getvalue(sem_space_total, &space_total_sval))
            
            if (space_total_sval >= PART_B_PER_TIME_PRODUCE && space_B_sval >= PART_B_PER_TIME_PRODUCE) {
            
                for (int i = 0; i < PART_B_PER_TIME_PRODUCE; ++i) {
                    sem_wait(sem_space_B);
                    sem_post(sem_storage_B);
                    sem_wait(sem_space_total);
                }
                iprintf("PART_B_PRODUCE_EVENT\n");
            }
            
            sem_post(sem_mutex);
            sleep(1);
        }
        iprintf("PROCUDE_B_END\n");
    } else if (fork() == 0) { 
        iprintf("COMSUMER_PID = %d\n", getpid());

        long product_count = 0;
        while (quit) {
            sem_wait(sem_mutex);
            
            EXIT_ERRNO(sem_getvalue(sem_storage_A, &storage_A_sval))
            EXIT_ERRNO(sem_getvalue(sem_storage_B, &storage_B_sval))
        
            if (storage_A_sval >= PART_A_REQUIRED && storage_B_sval >= PART_B_REQUIRED) {
                for (int i = 0; i < PART_A_REQUIRED; ++i) {
                    sem_wait(sem_storage_A);
                    sem_post(sem_space_A);
                    sem_post(sem_space_total);
                }
                for (int i = 0; i < PART_B_REQUIRED; ++i) {
                    sem_wait(sem_storage_B);
                    sem_post(sem_space_B);
                    sem_post(sem_space_total);
                }
                iprintf("COMSUMER_EVENT: product_count = %d\n", ++product_count);
            }
            
            sem_post(sem_mutex);
            sleep(1);
            
        }
        iprintf("COMSUMER_END\n");
        
    } else {

        wait(NULL);

        EXIT_ERRNO(sem_close(sem_mutex))
        EXIT_ERRNO(sem_close(sem_space_total))
        EXIT_ERRNO(sem_close(sem_space_A))
        EXIT_ERRNO(sem_close(sem_space_B))
        EXIT_ERRNO(sem_close(sem_storage_A))
        EXIT_ERRNO(sem_close(sem_storage_B))

        EXIT_ERRNO(sem_unlink(SEM_MUTEX))
        EXIT_ERRNO(sem_unlink(SEM_SPACE_TOTAL))
        EXIT_ERRNO(sem_unlink(SEM_SPACE_A))
        EXIT_ERRNO(sem_unlink(SEM_SPACE_B))
        EXIT_ERRNO(sem_unlink(SEM_STORAGE_A))
        EXIT_ERRNO(sem_unlink(SEM_STORAGE_B))

    }
    return 0;
}
