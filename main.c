#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "cpu_thread.h"
#include "io_thread.h"
#include "file_parser.h"

#define DEBUG 0

int main(int argc, char const *argv[]) {
    
    ////////////////////////////////////////////////
    // Get input from CLI arguments
    ////////////////////////////////////////////////
    
    // set up variables for CLI input
    int algo = 0;
    int quantum = 0;
    FILE *file_ptr;

    // step through given arguments
    for(int i = 1; i < argc; i++){
        // algorithm option
        if( strcmp(argv[i], "-alg") == 0 ){
            // check next argument for algorithm to use
            if( strcmp(argv[i+1], "FCFS") == 0 ){
                if(DEBUG) { printf("Activating FIRST COME FIRST SERVE\n"); }
                algo = 1;
            }
            else if( strcmp(argv[i+1], "SJF") == 0 ){
                if(DEBUG) { printf("Activating SHORTEST JOB FIRST\n"); }
                algo = 2;
            }
            else if( strcmp(argv[i+1], "PR") == 0 ){
                if(DEBUG) { printf("Activating PRIORITY SCHEDULING\n"); }
                algo = 3;
            }
            else if( strcmp(argv[i+1], "RR") == 0 ){
                if(DEBUG) { printf("Activating ROUND ROBIN\n"); }
                algo = 4;
            }
            else {
                if(DEBUG) { printf("Error: Invalid algorithm\n"); }
                exit(1);
            }
            i++;
        }

        // quantum option
        if( strcmp(argv[i], "-quantum") == 0 && algo == 4 ){
            // check next argument for quantum size
            if(DEBUG) { printf("Setting Quantum\n"); }
            quantum = atoi(argv[++i]);
        }

        // input option
        if( strcmp(argv[i], "-input") == 0 ){
            // check next argument for file_name
            if(DEBUG) { printf("ATTEMPTING TO OPEN FILE %s\n", argv[i+1]); }
            file_ptr = fopen(argv[i+1], "r");
            i++;

            // check if file was opened
            if(file_ptr == NULL){
                perror("Error: Cannot open file\n");
                exit(1);
            }
        }
    }

    // check if we got an algorithm and input at least
    if( !algo ){
        printf("Error: Missing algorithm\n");
        printf("Usage: ./scheduler -alg [FCFS,SJF,PR,RR] [-quantum [integer(ms)] -input [filename]\n");
        exit(1);
    }
    else if( !file_ptr ){
        printf("Error: Missing input file\n");
        printf("Usage: ./scheduler -alg [FCFS,SJF,PR,RR] [-quantum [integer(ms)] -input [filename]\n");
        exit(1);
    }
    else if( algo == 4 && !quantum ){
        printf("Error: Missing quantum time\n");
        printf("Usage: ./scheduler -alg [FCFS,SJF,PR,RR] [-quantum [integer(ms)] -input [filename]\n");
        exit(1);
    }

    ///////////////////////////////////////////////////
    // End input
    ///////////////////////////////////////////////////




    return 0;
}