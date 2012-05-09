/*
 * philosopher.c
 */

#include "philosopher.h"

#include "chopstick.h"
#include "sync.h"
#include "utility.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>

/*
 * This procedure runs the wait-eat-think loop for a given philosopher.
 * If the philosopher is even-numbered, it picks up the left chopstick first
 * and the right chopstick second; vice-versa for odd-numbered philosopher.
 *
 * int phil: this philosopher's id number
 * int total: how many philosophers there are
 * int maxwait: The maximum time that a philosopher can eat or think.
 *     The length of each such waiting period will be a whole number
 *     of seconds between 0 inclusive and maxwait exclusive.
 */
void phloop(int phil, int total, int maxwait) {
    int hungry = 0;
    while (1) {
        
        //Think:
        randomwait(maxwait);
        
        printf("Philosopher %d is hungry\n", phil);
        
        //Wait for chopsticks:
        if (phil % 2) { //true == 1 -> odd -> left first
            wait(phil, phil);
            printf("Philosopher %d has picked up chopstick %d\n", phil, phil);
            print_status(total);
            wait((phil + 1) % total, phil);
            printf("Philosopher %d has picked up chopstick %d\n", phil,
                   (phil + 1) % total);
            print_status(total);
        } else {
            wait((phil + 1) % total, phil);
            printf("Philosopher %d has picked up chopstick %d\n", phil,
                   (phil + 1) % total);
            print_status(total);
            wait(phil, phil);
            printf("Philosopher %d has picked up chopstick %d\n", phil, phil);
            print_status(total);
        }
        
        //Eat:
        randomwait(maxwait);
        
        printf("Philosopher %d is done eating\n", phil);
        
        //Surrender chopsticks:
        if (phil % 2) { //true == 1 -> odd -> left first
            signal(phil, phil);
            signal((phil + 1) % total, phil);
        } else {
            signal((phil + 1) % total, phil);
            signal(phil, phil);
        }
    }
}
