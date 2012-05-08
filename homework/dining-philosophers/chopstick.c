/*
 * chopstick.c
 *
 * Functions for philosophers to use in handling chopsticks
 */

#include "chopstick.h"
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
