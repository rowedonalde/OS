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
#include <stdlib.h>

#define CHANGE_DIR_COMMAND "cd"
#define MAX_TOKEN_LENGTH 256

/**
 * This program is a terminal shell for Linux
 */
int main() {
    
    /* Variable that will store the fork result. */
    pid_t pid;
    
    /* Raw input from the user, before tokenizing */
    char raw_input[MAX_TOKEN_LENGTH];
    
    /* String to hold the command to run. */
    char* command;
    
    /* Array of strings, each an argument */
    char* args[MAX_TOKEN_LENGTH];
    
    /* Number of arguments to the present command */
    int args_len;
    
    /* The int that should be used to hold the status from the wait call */
    int result;
    
    /* The code that scanf returns, e.g., EOF */
    int scanf_code;
    
    /* Loop counter */
    int i;
    
    char eof_str[1];
    eof_str[0] = EOF;
    
    do {
        
        /*Initialize the number of args for this command */
        args_len = 0;
        
        /* Get the command from the user */
        printf("Enter the command to run: ");
           
        /* Get the raw input*/
        fgets(raw_input, MAX_TOKEN_LENGTH, stdin);
        
        /* If the user types ctrl-D, just quit */
//         if (strspn(eof_str, raw_input)) {
//             printf("\n");
//             return 0;
//         }
        
        /* Get the command */
        args[0] = strtok(raw_input, " \n");
            
        /*Loop through and add arguments to the list */
        while (args[args_len + 1] = strtok(NULL, " \n")) {
            args_len++;
        }
        
// test:
//              printf("command: %s\n", command);
//              printf("args:\n");
//              for (i = 0; i < args_len; i++) {
//                  printf("%s\n", args[i]);
//              }
        
        /* 
         * If the user types a command beginning with "cd" change to that
         * directory. Do not fork a new process--just start the read loop over.
         */
//         if (strspn(CHANGE_DIR_COMMAND, command)) {
//                 //test:
//                 printf("cd command detected!\n");
//             
//             /* Change to new dir */
//             if (chdir(args[0]) == 0) {
//                 printf("New working directory: %s\n", args[0]);
//             } else {
//                 printf("There was an error in changing the working directory!\n");
//             }
//             
//             pid = 1;
//             continue;
//         }
          
 
        /* Perform the actual fork */
        pid = fork();
            //test:
            //printf("my pid is %d\n", pid);
        
        /* If this is the parent process, wait on the child */
        if (pid > 0) { 
            wait(&result);
        }
        
     } while (pid > 0);
    
    /* If this is the child process, run the command the user passed to it */
    if (pid == 0) {
        args[args_len + 1] = NULL;
        if (args_len > 0) {
            execvp(args[0], args);
        } else {
            execlp(args[0], args[0], NULL);
        }
    }

    return 0;
}
