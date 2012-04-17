/**
 * mysh.c
 *
 * Don Rowe, CMSI 387
 * Assignment 0320
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

/**
 * This program is a terminal shell for Linux
 */
int main() {
    
    /* Variable that will store the fork result. */
    pid_t pid;
    
    /* String to hold the command to run. */
    char command[256];
    
    /* The int that should be used to hold the status from the wait call */
    int result;
    
    /* The code that scanf returns, e.g., EOF */
    int scanf_code;
    
    do {
        
        /* Get the command from the user */
        printf("Enter the command to run: ");
        scanf_code = scanf("%s", command);
            //test:
            //printf("scanf_code: %d\n", scanf_code);
        
        /* If the user types ctrl-D, just quit */
        if (scanf_code == EOF) {
            printf("\n");
            return 0;
        }

        /* Perform the actual fork */
        pid = fork();
        
        /* If this is the parent process, wait on the child */
        if (pid > 0) { 
            wait(&result);
        }
        
    } while (pid > 0);
    
    /* If this is the child process, run the command the user passed to it */
    if (pid == 0) {
        execlp(command, command, NULL);
    }

    return 0;
}
