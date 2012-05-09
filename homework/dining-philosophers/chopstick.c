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

#define FREE -1


/*
 * wait() function used by a philosopher to wait until a given chopstick is
 * ready, after which the chopstick is marked as being held by that philosopher
 */
void wait(int* chopstick, int phil) {
    while (*chopstick > FREE) {
        //wait
    }
    
    //When done waiting, set the given chopstick to
    //the philosopher's ID:
    *chopstick = phil;
}

/*
 * signal() function used by a philosopher to indicate that the given chopstick
 * is now available.
 */
void signal(int* chopstick) {
    *chopstick = FREE;
}


/*
 * Prints out the current status of an array of chopsticks.
 * If a chopstick is available, it is represented as a '|' character.
 * If the philosopher to the left is holding it, it is represented as
 * a '<' character.
 * If the philosopher to the right is holding it, it is represented as
 * a '>' character.
 */
void print_status(int* chopstick, int total, int* waitlist) {
    char *errormsg =
    "\n******ILLEGAL OPERATION! PHILOSOPHER %d IS HOLDING CHOPSTICK %d******\n";

    //Chopstick 0 is an edge case--the philosopher to the left
    //is philosopher total-1
    if (total > 0) {
        if (chopstick[0] == 0) {
            printf(">0");
        } else if (chopstick[0] == total - 1) {
            printf("<0");
        } else if (chopstick[0] == FREE) {
            printf("|0");
        } else {
            printf(errormsg, chopstick[0], 0);
        }
    }
}
