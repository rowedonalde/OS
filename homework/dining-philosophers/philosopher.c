/*
 * philosopher.c
 */

#include "philosopher.h"
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
 * int* chopstick: The array of Chopsticks to use
 */
void phloop(int phil, int total, float chance, int* chopstick) {
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
            wait(chopstick[phil], phil);
            printf("Philosopher %d has picked up chopstick %d\n", phil, phil);
            print_status();
            wait(chopstick[(phil + 1) % total], phil);
            printf("Philosopher %d has picked up chopstick %d\n", phil,
                   (phil + 1) % total);
            print_status();
        } else {
            wait(chopstick[(phil + 1) % total], phil);
            printf("Philosopher %d has picked up chopstick %d\n", phil,
                   (phil + 1) % total);
            print_status();
            wait(chopstick[phil], phil);
            printf("Philosopher %d has picked up chopstick %d\n", phil, phil);
            print_status();
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
            signal(chopstick[phil]);
            signal(chopstick[(phil + 1) % total]);
        } else {
            signal(chopstick[(phil + 1) % total]);
            signal(chopstick[phil]);
        }
    }
}
