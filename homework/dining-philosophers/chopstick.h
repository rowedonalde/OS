/*
 * chopstick.h
 */

#ifndef __CHOPSTICK__
#define __CHOPSTICK__

//chopsticks array needs to be allocated in main()
int *chopsticks;

void wait(int chopstick, int phil);
void signal(int chopstick, int phil);
void print_status(int total);

#endif
