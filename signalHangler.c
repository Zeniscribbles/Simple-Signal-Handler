////////////////////////////////////////////////////////////////////////
///         University of Hawaii - College of Engineering
///                       Amanda Eckardt
///                      ECE 468 Fall 2024
///
///               A user-defined Signal Handler
///             
///                     Ring, ring...Hello?
///
///@see https://faculty.cs.niu.edu/~hutchins/csci480/signals.htm
///
///@file signalHandler.c
///@author Amanda Eckardt <aze@hawaii.edu>
///////////////////////////////////////////////////////////////////////
#include <signal.h>     // For signal processing
#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit()
#include <string.h>     // For memset()
#include <stdatomic.h>  // For atomic variables
#include <unistd.h>     // For sleep()

#define MAX_PUSH 5  // Max Ctrl-C repetitions before SIGINT trigger.

// Using atomic to avoid potential race conditions [protecting global variable].
volatile atomic_int sigintCount = 0;

///@brief signalHandler: Handler for SIGNINT, caused by Ctrl-C at keyboard.
///                      
///@param sig 
void signalHandler(int sig){
    sigintCount++;
}


///@brief Main Program Entry: Signal Processing using signal(). SIGINT is a signal generated when a user presses Control-C.
///                   
///@return exit(EXIT_SUCCESS)
int main(void){
      
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));   // Clear the sigaction structure
    sa.sa_handler = &signalHandler;             // Set signal handler
     
    
    // Set up the signal handler for SIGINT using sigaction
    if (sigaction(SIGINT, &sa, NULL) == -1){
       perror("sigaction");
       return EXIT_FAILURE;
     }    

    // Infinite loop to keep the program running until Ctrl+C is.
    while(1){   
        
        // Check if the user pressed Ctrl+C 5 times
        if(sigintCount == MAX_PUSH){
            printf("\nRecieved Interrupt Signal SIGINT!\n");
            
            for(int i = 0; i < 5; i++){
                printf("^CAloha world\n");
                sleep(1); // Prevent a tight loop from consuming CPU resources
            }
            
            break;        // Break the loop after printing "Aloha World" 5 times
        }
        
    }
    
    return (EXIT_SUCCESS);  // Return success after loop exits
}


