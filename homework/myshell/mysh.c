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
    
    do {
        
        /*Initialize the number of args for this command */
        args_len = 0;
        
        /* Get the command from the user */
        printf("Enter the command to run: ");
        /* FIXME: This needs to be looped through to get successive tokens.
           presently it only gets the first */
           
        /* Get the raw input*/
        //scanf_code = scanf("%s", command);
        fgets(raw_input, MAX_TOKEN_LENGTH, stdin);
        
        /* If the user types ctrl-D, just quit */
//         if (strspn(EOF, raw_input) {
//             printf("\n");
//             return 0;
//         }
        
        /* Get the command */
        command = strtok(raw_input, " ");
            
        /*Loop through and add arguments to the list */
        while (args[args_len] = strtok(NULL, " ")) {
            args_len++;
        }
        
            //test:
            printf("command: %s\n", command);
            printf("args:\n");
            for (i = 0; i < args_len; i++) {
                printf("%s\n", args[i]);
            }
        
//         /* 
//          * If the user types a command beginning with "cd" change to that
//          * directory. Do not fork a new process--just start the read loop over.
//          *
//          * TODO: allow whitespace before the cd command
//          * FIXME: This is all wrong--everything gets tokenized by whitespace,
//          * not just by line breaks.
//          */
//         if (strncmp(CHANGE_DIR_COMMAND, command, 3) == 0) {
//                 //test:
//                 printf("cd command detected!\n");
//             /* set new_dir to the stuff in command after "cd " */
//             /* since command is null-terminated, new_dir will be as well */
//             int i;
//             for (i = 0; i < 256 - 3; i++) {
//                 new_dir[i] = command[i + 3];
//             }
//             
//             /* Change to new_dir */
//             if (chdir(new_dir) == 0) {
//                 printf("New working directory: %s\n", new_dir);
//             } else {
//                 printf("There was an error in changing the working directory!\n");
//             }
//             
//             pid = 1;
//             continue;
//         }
//           
// 
//         /* Perform the actual fork */
//         pid = fork();
//         
//         /* If this is the parent process, wait on the child */
//         if (pid > 0) { 
//             wait(&result);
//         }
//         
     } while (pid > 0);
//     
//     /* If this is the child process, run the command the user passed to it */
//     if (pid == 0) {
//         /* FIXME: be able to handle an arbitrary number of args:
//            use execvp() instead */
//         execlp(command, command, NULL);
//    }

    return 0;
}
