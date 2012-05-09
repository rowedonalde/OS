/*
 * chopstick.h
 */

#ifndef __CHOPSTICK__
#define __CHOPSTICK__

void wait(int* chopstick, int phil);
void signal(int* chopstick);
void print_status(int* chopstick, int total, int* waitlist);

#endif
