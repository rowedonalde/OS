/*
 * dining_philosophers_runner.c
 *
 * This program runs a Dining Philosophers simulation. It
 * takes two arguments from the command line: an int n:n>1
 * number of philosophers and an int t:t>0 second wait bound.
 *
 * This file defines a thread interface for the philosopher
 * loop. The main() function first initializes the chopstick
 * mutex array. Then, it initializes the threads that run
 * each philosopher loop. This process will run indefinitely
 * until it is killed.
 */

#include "chopstick.h"
#include "sync.h"
#include <stdio.h>
#include <stdlib.h>

void *runner(void* args);

int main(int argc, char** argv) {
    int i;
    
    //Initial input validation:
    int total = atoi(argv[1]);
    int maxwait = atoi(argv[2]);
    if (argc != 3 ||total <= 1 || maxwait <= 0) {
        printf("This program requires two arguments after the filename:\n");
        printf("an int n:n>1 number of philosophers and an int t:t>0 second wait bound.");
        return 1;
    }
    
        //test:
    
    //Initialize the array of chopsticks:
    chopsticks = malloc(total * sizeof(int));
    for (i = 0; i < total; i++) {
        chopsticks[i] = -1;
    }
    
    //Initialize the chopstick mutex array:
    mutexes = malloc(total * sizeof(pthread_mutex_t));
    //Initialize the mutex locks:
    initSync(total);
    
    //Initialize the philosopher loop threads:
    pthread_t *tid;
    tid = malloc(total * sizeof(pthread_t));
    pthread_attr_t *attr;
    attr = malloc(total * sizeof(pthread_attr_t));
    //args to be passed to runner:
    //int *args;
    //args = malloc(3 * sizeof(int));
    //args[1] = total;
    //args[2] = maxwait;
    
    for (i = 0; i < total; i++) {
            //test:
            //printf("Got to top of thread init loop\n");
            
        //Thread:
        pthread_attr_init(attr + i * sizeof(pthread_attr_t));
        
        //args to be passed to runner:
        int *args;
        args = malloc(3 * sizeof(int));
        args[0] = i;
        args[1] = total;
        args[2] = maxwait;
        pthread_create(tid + i * sizeof(pthread_t),
                       attr + i * sizeof(pthread_attr_t),
                       runner,
                       args);
        
            //test:
            //printf("Got to end of thread init loop #%d\n", i);
    }
    
    //Joins:
    for (i = 0; i < total; i++) {
        pthread_join(*(tid + i * sizeof(pthread_t)), NULL);
    }
    
    free(chopsticks);
    free(mutexes);
    free(tid);
    free(attr);
    //free(args);
    
    return 0;
}

void *runner(void* p) {
    int *args = p;
        //test:
        //printf("Initializing a new phloop\n");
    phloop(args[0], args[1], args[2]);
    
    free(args);
    
    pthread_exit(0);
}
