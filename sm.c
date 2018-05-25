//
//  main.c
//
//  Created by GL on 5/23/18.
//  Copyright © 2018 GL. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


typedef enum { false = 0, true = !false } bool;


/*******************************************************************************
 GLOBAL VARIABLES
 *******************************************************************************/
// For getline() to get player input through stdin
// Holds how large the allocated buffer is
size_t inputSize = 0;
// Points to a buffer allocated by getline() that holds our entered string
char* inputLine = NULL;
char inputLinePID[100]; // For inputline with PID appended at end

// Char pointer for finding the \n in inputLine strings and replacing with \0
char* nullTerm;
// For validating user input
// bool validInput = false;



/*******************************************************************************
 FUNCTION DECLARATIONS
 *******************************************************************************/
void getCommand();


/*******************************************************************************
 FUNCTION DEFINITIONS
 *******************************************************************************/

void getCommand(){
    //    - Get your prompt ": " outputting so you hit that simple requirement
    // Prompt is a colon :
    printf(": ");
    fflush(stdout);

    //    - Get the loop to terminate when the user inputs "exit".
    // In Assignment 2 we had to handle user input and input processing,
    // so you can steal your implementations and you should be up and running quickly.

    getline(&inputLine, &inputSize, stdin);
    // Find and replace the \n with \0 so that we can correctly use strcmp
    // to compare user input with any of the string values from the room
    // files (or "time" for time request).
    nullTerm = strchr(inputLine, '\n');
    *nullTerm = '\0';
    char myCommand[50]; // For copying the stdin input string without '\n'
                        // Put user input string into nextRoom, and we will compare nextRoom
    strcpy(myCommand, inputLine);

    //    - Make sure you're handling blank input (easy peasy)

}






// CHECK FOR BUILT IN COMMANDS: EXIT, CD, STATUS

//    - Make sure you're handling blank input (easy peasy)

// CHECK EXIT
//    - Get the loop to terminate when the user inputs "exit".
// In Assignment 2 we had to handle user input and input processing,
// so you can steal your implementations and you should be up and run





int main(int argc, const char * argv[]) {
    bool chooseExit = false;





    int status = 0; // For exit value when call status

    /*
     - In main, set up a loop and start getting user input.
     While user has not entered "exit" built-in command, keep running small
     shell prompts
     */
    while(chooseExit == false){
        int i;

        // GET INPUT

        // PROMPT USER (with :)
        //        getCommand();


        // For getline() to get player input through stdin
        // Holds how large the allocated buffer is
        size_t inputSize = 0;
        // Points to a buffer allocated by getline() that holds our entered string
        char* inputLine = NULL;
        char inputLinePID[100]; // For inputline with PID appended at end

        // Char pointer for finding the \n in inputLine strings and replacing with \0
        char* nullTerm;
        // For validating user input
        // bool validInput = false;

        printf(": ");
        fflush(stdout);

        //    - Get the loop to terminate when the user inputs "exit".
        // In Assignment 2 we had to handle user input and input processing,
        // so you can steal your implementations and you should be up and running quickly.

        getline(&inputLine, &inputSize, stdin);
        // Find and replace the \n with \0 so that we can correctly use strcmp
        // to compare user input with any of the string values from the room
        // files (or "time" for time request).
        nullTerm = strchr(inputLine, '\n');
        *nullTerm = '\0';
        char myCommand[50]; // For copying the stdin input string without '\n'
                            // Put user input string into nextRoom, and we will compare nextRoom
        strcpy(myCommand, inputLine);



        /*Your program must expand any instance of "$$" in a command into the
         process ID of the shell itself. Your shell does not otherwise perform
         variable expansion. This feature makes it easier to create a grading
         script that keeps your work separate.
         */

//        // EXPAND PROCESS ID FOR GRADING SCRIPT TO APPLY
//        // change inputLine$$ into inputLine%d
//        for (i = 0; i < strlen(inputLine); i++){
//            if(inputLine[i] == '$' && inputLine[i+1] == '$'){
//                inputLine[i] = '%';
//                inputLine[i+1] = 'd';
//            }
//        }
//
//        // Format print inputLinePID by filling it with "inputLine%d, getpid()"
//        sprintf(inputLinePID, inputLine, getpid());


        // Compare s1 and s2.  Find first occurrence of substring s2 inside s1.
        // i.e., first first occurrence of $$ in inputLine
        while(strstr(inputLine, "$$")){
            sprintf(strstr(inputLine, "$$"), "%d", getpid());
        }

//        printf("inputLine is: %s", inputLine);
        
        // CHECK FOR BUILT IN COMMANDS: EXIT, CD, STATUS
        // CHECK EXIT
        if (strcmp(inputLine, "exit") == 0){
            printf("exiting...\n");
            chooseExit = true;
            exit(0);
        }


        // CHECK CD
        // If user input cd or cd ..
        // First check if entered cd at all
        else if(strncmp(inputLine, "cd", strlen("cd")) == 0){
            char myPath[50];

            // if cd .. or cd myFolder
            if(strncmp(inputLine, "cd ", strlen("cd ")) == 0){
                sscanf(inputLine, "%*s %s", myPath);
                printf("You entered cd %s\n", myPath);

                chdir(myPath);
            }

            // If just cd
            else{
                printf("You entered cd alone, going HOME\n");
                chdir(getenv("HOME"));
            }
        }


        // CHECK STATUS
        else if (strcmp(inputLine, "status") == 0){
            printf("status-ing...\n");
            printf("exit value %d\n", status);
        }

        // CHECK COMMENT
         else if(strncmp(inputLine, "#", strlen("#")) == 0){
             printf("Ignore comment line\n");
             continue;
         }

        // CHECK NULL
        else if (strcmp(inputLine, "") == 0){
            printf("if inputLine is doubel quotes \n");
            continue;
        }



        // OTHERWISE, CHECK FOR NON-BUILT IN COMMANDS
        // L3 p. 34
        // L3 pg. 26 - checking the exit status of child
        else{


            /*
            pid_t spawnPid = -5;
            int childExitStatus = -5;
            spawnPid = fork();
            switch (spawnPid) {
                case -1: { perror("Hull Breach!\n"); exit(1); break; }
                case 0: {
                    printf("CHILD(%d): Sleeping for 1 second\n", getpid());
                    sleep(1);
                    printf("CHILD(%d): Converting into \'ls -a\'\n", getpid());
//                    execlp("ls", "ls", "-a", NULL);
//                    perror("CHILD: exec failure!\n");
                    exit(2); break;
                }
                default: {
                    printf("PARENT(%d): Sleeping for 2 seconds\n", getpid());
                    sleep(2);
                    printf("PARENT(%d): Wait()ing for child(%d) to terminate\n", getpid(), spawnPid);
                    pid_t actualPid = waitpid(spawnPid, &childExitStatus, 0);
                    printf("PARENT(%d): Child(%d) terminated, Exiting!\n", getpid(), actualPid);
                    exit(0); break;
                }
            }
            */


            /*
            pid_t spawnPid = -5;
            int childExitMethod = -5;
            spawnPid = fork();
            if (spawnPid == -1) //
            {
                perror("Hull Breach!\n");
                exit(1);
            }else if (spawnPid == 0) // Terminate the child process immediately
            {
                printf("CHILD: PID: %d, exiting!\n", spawnPid);
                exit(0);
            }
            printf("PARENT: PID: %d, waiting...\n", spawnPid);
            waitpid(spawnPid, &childExitMethod, 0);
            printf("PARENT: Child process terminated, exiting!\n");
            exit(0);
            */

            /*
            pid_t spawnPid = -5;
            int childExitStatus = -5;
//            int ten = 10;

            spawnPid = fork();
            switch(spawnPid){
                // FORK FAILS
                case -1:  { perror ("Hull Breach!\n"); exit(1); break; }
                // CHILD
                case 0: {
                    printf("CHILD(%d): Sleeping for 1 second\n", getpid());
                    sleep(1);
                    printf("CHILD(%d): Converting into \'ls -a\'\n", getpid());
                    execlp("ls", "ls", "-a", NULL);
                    perror("CHILD: exec failure!\n");
                    exit(2); break;
                }
                // PARENT
                case 1: {
                    printf("PARENT(%d): Sleeping for 2 seconds\n", getpid());
                    sleep(2);
                    printf("PARENT(%d): Wait()ing for child(%d) to terminate\n", getpid(), spawnPid);
                    pid_t actualPid = waitpid(spawnPid, &childExitStatus, 0);
                    printf("PARENT(%d): Child(%d) terminated, Exiting!\n", getpid(), actualPid);
                    exit(0); break;

                }

            }
            printf("This will be executed by both of us!\n");
            */

        } // CLOSE LAST ELSE SECTION (NON-BUILT-IN COMMANDS)

    }; //CLOSE PROMPT WHILE LOOP


    
    return 0;
}
