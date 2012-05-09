/*
 * philosopher.c
 */

#include "philosopher.h"

#include "chopstick.h"
#include "sync.h"
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
 * float chance: The likelihood that, after every second of thinking
 *               or eating, the philosopher will be done
 */
void phloop(int phil, int total, float chance) {
    int hungry = 0;
    while (1) {
        
        //Think:
        while (!hungry) {
            sleep(1);
            unsigned int eatseed = time();
            //If a 0 is randomly generated in this turn, get hungry
            //and break out of the loop:
            if (!(int)((1 / chance) * rand() / RAND_MAX)) {
                hungry = 1;
            }
        }
        
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
        while (hungry) {
            sleep(1);
            unsigned int eatseed = time();
            //If a 0 is randomly generated in this turn, get full
            //and break out of the loop:
            if (!(int)((1 / chance) * rand() / RAND_MAX)) {
                hungry = 0;
            }
        }
        
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
