/**
 * Utility implementation.
 */
#include "utility.h"

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int randomwait(int bound) {
    srand((unsigned int)time(NULL));
    int wait = rand() % bound;
    sleep(wait);
    return wait;
}
