/**
 * mysh.c
 *
 * Don Rowe, CMSI 387
 * Assignment 0320
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define CHANGE_DIR_COMMAND "cd "

/**
 * This program is a terminal shell for Linux
 */
int main() {
    
    /* Variable that will store the fork result. */
    pid_t pid;
    
    /* String to hold the command to run. */
    char command[256];
    
    /* Array of strings, representing first the command and then the args */
    char* tokens;
    
    /* String to hold the new directory */
    char new_dir[253];
    
    /* The int that should be used to hold the status from the wait call */
    int result;
    
    /* The code that scanf returns, e.g., EOF */
    int scanf_code;
    
    do {
        
        /* Get the command from the user */
        printf("Enter the command to run: ");
        /* FIXME: This needs to be looped through to get successive tokens.
           presently it only gets the first */
        scanf_code = scanf("%s", command);
            //test:
            //printf("scanf_code: %d\n", scanf_code);
        
        /* If the user types ctrl-D, just quit */
        if (scanf_code == EOF) {
            printf("\n");
            return 0;
        }
        
        /* 
         * If the user types a command beginning with "cd" change to that
         * directory. Do not fork a new process--just start the read loop over.
         *
         * TODO: allow whitespace before the cd command
         * FIXME: This is all wrong--everything gets tokenized by whitespace,
         * not just by line breaks.
         */
        if (strncmp(CHANGE_DIR_COMMAND, command, 3) == 0) {
                //test:
                printf("cd command detected!\n");
            /* set new_dir to the stuff in command after "cd " */
            /* since command is null-terminated, new_dir will be as well */
            int i;
            for (i = 0; i < 256 - 3; i++) {
                new_dir[i] = command[i + 3];
            }
            
            /* Change to new_dir */
            if (chdir(new_dir) == 0) {
                printf("New working directory: %s\n", new_dir);
            } else {
                printf("There was an error in changing the working directory!\n");
            }
            
            pid = 1;
            continue;
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
        /* FIXME: be able to handle an arbitrary number of args:
           use execvp() instead */
        execlp(command, command, NULL);
    }

    return 0;
}
