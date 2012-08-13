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
    
    printf("Philosopher %d is trying to get the lock for chopstick %d\n",
           phil, chopstick);
    //Acquire the lock/wait for the chopstick:
    pthread_mutex_lock(&mutexes[chopstick]);
    // JD: ^Commenting this out should expose concurrency problems, but does not.
    printf("Philosopher %d got the lock for chopstick %d\n",
           phil, chopstick);
    
    //When done waiting, set the given chopstick to
    //the philosopher's ID:
    chopsticks[chopstick] = phil;
    // JD: ^The check should happen here: prior to setting the chopstick state,
    //      check its *current* state to make sure that another philosopher
    //      isn't already holding it.  That would indicate that the critical
    //      section was violated.
    printf("Chopstick %d is registered with philosopher %d\n",
           chopstick, phil);
}

/*
 * signal() function used by a philosopher to indicate that the given chopstick
 * is now available.
 */
void signal(int chopstick, int phil) {
    chopsticks[chopstick] = FREE;
    // JD: ^An analogous check should happen here.  A philosopher should
    //      not be able to free a chopstick that he/she does not already
    //      have (again, this would be a critical section fail).

    //Release the lock for the chopstick:
    pthread_mutex_unlock(&mutexes[chopstick]);
    printf("Philosopher %d has released chopstick %d\n", phil, chopstick);
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

    // JD: Your error message here is noted, but hope you can see (based on
    //     the above comments) how it is in the wrong place.  The issue is
    //     not that the chopsticks array may hold bad values, it is that
    //     the array might be changed at the wrong moment.

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
    
    //Print a newline:
    printf("\n");
}
