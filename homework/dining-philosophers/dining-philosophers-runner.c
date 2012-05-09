/*
 * dining_philosophers_runner.c
 *
 * This program runs a Dining Philosophers simulation. It
 * takes two arguments from the command line: an int n:n>1
 * number of philosophers and an int t:t>0 second wait bound.
 *
 * This file defines a thread interface for the philosopher
 * loop. The main() function first initializes the chopstick
 * mutex array. Then, it initializes the threads that run
 * each philosopher loop. This process will run indefinitely
 * until it is killed.
 */
