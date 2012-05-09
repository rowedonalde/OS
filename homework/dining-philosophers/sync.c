/**
 * Synchronization primitive implementation.
 *
 * Adapted from:
 * github.com/dondi/bazaar/blob/master/bounded-buffer/bb-sync.c
 */
#include "sync.h"

#include <pthread.h>

/*
 * Initializes array mutexes with total number of mutex locks
 */
void initSync(int total) {
    int i;
    for (i = 0; i < total; i++) {
        pthread_mutex_init(&mutexes + i * sizeof(pthread_mutex_t), NULL);
    }
}
