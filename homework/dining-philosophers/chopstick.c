/*
 * chopstick.c
 *
 * Functions for philosophers to use in handling chopsticks.
 * 
 * This implementation assumes that a chopstick is to the left of
 * the philosopher of the same ID number.
 */

#include "chopstick.h"

#include "sync.h"

#include <stdio.h>
#include <stdlib.h>

#define FREE -1


/*
 * wait() function used by a philosopher to wait until a given chopstick is
 * ready, after which the chopstick is marked as being held by that philosopher
 */
void wait(int chopstick, int phil) {
        //test:
        printf("Philosopher %d is trying to get the lock for chopstick %d\n",
               phil, chopstick);
    //Acquire the lock/wait for the chopstick:
    //pthread_mutex_lock(mutexes + chopstick * sizeof(pthread_mutex_t));
    pthread_mutex_lock(&mutexes[chopstick]);
        //test:
        printf("Philosopher %d got the lock for chopstick %d\n",
               phil, chopstick);
    
    //When done waiting, set the given chopstick to
    //the philosopher's ID:
    chopsticks[chopstick] = phil;
        //test:
        printf("Chopstick %d is registered with philosopher %d\n",
               chopstick, phil);
}

/*
 * signal() function used by a philosopher to indicate that the given chopstick
 * is now available.
 */
void signal(int chopstick, int phil) {
    chopsticks[chopstick] = FREE;
    
    //Release the lock for the chopstick:
    pthread_mutex_unlock(mutexes + chopstick * sizeof(pthread_mutex_t));
}


/*
 * Prints out the current status of an array of chopsticks.
 * If a chopstick is available, it is represented as a '|' character.
 * If the philosopher to the left is holding it, it is represented as
 * a '<' character.
 * If the philosopher to the right is holding it, it is represented as
 * a '>' character.
 */
void print_status(int total) {
    char *errormsg =
    "\n******ILLEGAL OPERATION! PHILOSOPHER %d IS HOLDING CHOPSTICK %d******\n";

    //Chopstick 0 is an edge case--the philosopher to the left
    //is philosopher total-1
    if (total > 0) {
        if (chopsticks[0] == 0) {
            printf(">0");
        } else if (chopsticks[0] == total - 1) {
            printf("<0");
        } else if (chopsticks[0] == FREE) {
            printf("|0");
        } else {
            printf(errormsg, chopsticks[0], 0);
            exit(1);
        }
    }
    
    //The rest of the chopsticks:
    int i;
    for (i = 1; i < total; i++) {
        if (chopsticks[i] == i - 1) {
            printf("<%d", i);
        } else if (chopsticks[i] == i) {
            printf(">%d", i);
        } else if (chopsticks[i] == FREE) {
            printf("|%d", i);
        } else {
            printf(errormsg, chopsticks[i], i);
            exit(1);
        }
    }
}
