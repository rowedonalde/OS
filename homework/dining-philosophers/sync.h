/**
 * Synchronization elements for a bounded buffer solution.
 *
 * Adapted from:
 * github.com/dondi/bazaar/blob/master/bounded-buffer/bb-sync.h
 */
#ifndef __PHIL_SYNC__
#define __PHIL_SYNC__

#include <pthread.h>

//mutexes needs to be allocated in main()
pthread_mutex_t *mutexes;

/**
 * Initializes synchronization primitives.
 */
void initSync(int total);

#endif
