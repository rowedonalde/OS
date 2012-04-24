/**
 * mysh.c
 *
 * Don Rowe, CMSI 387
 * Assignment 0320
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define CHANGE_DIR_COMMAND "cd"
#define MAX_TOKEN_LENGTH 256
#define __NR_helloworld 347
#define SECRET "secret-system-call"

/**
 * This program is a terminal shell for Linux
 */
int main() {
    
    /* Variable that will store the fork result. */
    pid_t pid;
    
    /* Raw input from the user, before tokenizing */
    char raw_input[MAX_TOKEN_LENGTH];
    
    /* The new directory, when cd is called */
    char* current_dir;
    
    /* Array of strings, each an argument */
    char* args[MAX_TOKEN_LENGTH];
    
    /* Number of arguments to the present command,
       NOT the length of array args */
    int args_count;
    
    /* The int that should be used to hold the status from the wait call */
    int result;
    
    /* The code that scanf returns, e.g., EOF */
    int scanf_code;
    
    /* Loop counter */
    int i;
    
    /* Boolean int to indicate whether the child process should run
       concurrently */
    int concurrent;
    
    do {
        
        /*Initialize the number of args and concurrent flag for this command */
        args_count = 0;
        concurrent = 0;
        
        /* Get the command from the user */
        printf("%s> ", getcwd(current_dir, MAX_TOKEN_LENGTH));
           
        /* Get the raw input*/
        fgets(raw_input, MAX_TOKEN_LENGTH, stdin);
        
        /* If the user types ctrl-D, just quit */
        if (feof(stdin)) {   
            printf("Goodbye!\n");
            return 0;
        }
        
        /* Get the command. If the user inputs a null string or whitespace,
           just jump back to the beginning */
        args[0] = strtok(raw_input, " \n");
        if (args[0] == NULL) {
            continue;
        }
            
        /*Loop through and add arguments to the list */
        while (args[args_count + 1] = strtok(NULL, " \n")) {
            args_count++;
        }
        
        /* 
         * If the user types a command beginning with "cd" change to that
         * directory. Do not fork a new process--just start the read loop over.
         */
        if (strspn(CHANGE_DIR_COMMAND, args[0])
            && strlen(CHANGE_DIR_COMMAND) == strlen(args[0])) {
            
            /* Change to new dir */
            if (chdir(args[1]) == 0) {
                printf("New working directory: %s\n", getcwd(current_dir, MAX_TOKEN_LENGTH));
            } else {
                printf("There was an error in changing the working directory!\n");
            }
            
            pid = 1;
            continue;
        }
        
        /* Set the concurrent flag to 1 if necessary */
        if (args_count > 0 && args[args_count][0] == '&') {
            concurrent = 1;
            /* remove the "&" from args */
            args[args_count] = NULL;
            printf("Character is %s\n", args[args_count]);
        }
 
        /* Perform the actual fork */
        pid = fork();
        
        /* If this is the parent process, wait on the child */
        if (pid > 0) {
            /* If the final "arg" is "&", let the program run concurrently */
            if (!concurrent) {
                wait(&result);
            }
        }
        
    } while (pid > 0);
    
    /* If this is the child process, run the command the user passed to it */
    if (pid == 0) {
        /* Handle Easter Egg */
        if (strspn(SECRET, args[0]) && (strlen(SECRET) == strlen(args[0]))) {
            printf("Secret system call activated! Go check /var/log/kern.log!\n");
            syscall(__NR_helloworld);
            return 0;
        }
    
        /* NULL string pointer terminates the array of args for execvp() */
        args[args_count + 1] = NULL;
        if (args_count > 0) {
            execvp(args[0], args);
        } else {
            execlp(args[0], args[0], NULL);
        }
    }

    return 0;
}

// JD: Wow, talk about better late than never.  This code is clean,
//     functional, and pristine.  I have nothing further to say.
//     Well done!
