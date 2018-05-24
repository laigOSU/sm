//
//  main.c
//  smallsh.c
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


int main(int argc, const char * argv[]) {
    bool chooseExit = false;

    // insert code here...
    printf("Hello, World!\n");



    /*
     - In main, set up a loop and start getting user input.
     While user has not entered "exit" built-in command, keep running small
     shell prompts

     */
    while(chooseExit == false){

        // GET INPUT



        // For getline() to get player input through stdin
        // Holds how large the allocated buffer is
        size_t inputSize = 0;
        // Points to a buffer allocated by getline() that holds our entered string
        char* inputLine = NULL;
        // Char pointer for finding the \n in inputLine strings and replacing with \0
        char* nullTerm;
        // For validating user input
        // bool validInput = false;

        // Prompt is a colon :
        printf(": ");
        fflush(stdout);

        getline(&inputLine, &inputSize, stdin);
        // Find and replace the \n with \0 so that we can correctly use strcmp
        // to compare user input with any of the string values from the room
        // files (or "time" for time request).
        nullTerm = strchr(inputLine, '\n');
        *nullTerm = '\0';
        char myCommand[50]; // For copying the stdin input string without '\n'
                            // Put user input string into nextRoom, and we will compare nextRoom
        strcpy(myCommand, inputLine);

        // CHECK FOR BUILT IN COMMANDS: EXIT, CD, STATUS

        // CHECK EXIT
        if (strcmp(inputLine, "exit") == 0){
            printf("exiting...\n");
            exit(0);
        }

        // CHECK CD

        // CHECK STATUS



        // OTHERWISE, CHECK FOR NON-BUILT IN COMMANDS

    };

    //    - Get the loop to terminate when the user inputs "exit".  In Assignment 2 we had to handle user input and input processing, so you can steal your implementations and you should be up and running quickly.
    //
    //
    //    - Get your prompt ": " outputting so you hit that simple requirement
    //
    //
    //    - Make sure you're handling blank input (easy peasy)
    //
    //
    //    - Move from strstr() to strtok() for finer grained control - strstr() will find "exit" anywhere in a line, but you want to be able to process each token.  So what happens if someone inputs "exit", vs. "exit status", vs. "exit exit"?  When someone uses too many arguments I reject the command and say "Too many arguments to function."
    //
    //
    //        - Once you have it handling "exit" and its variations flawlessly, start building out "cd", which should be pretty easy at that point.
    //
    //        - Once you have "cd", start building "status".
    
    return 0;
}
