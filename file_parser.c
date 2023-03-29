#include "file_parser.h"

// Sample File Format
// proc PRIORITY NUM_OF_BURSTS CPU_BURST IO_BURST CPU_BURST . . .
// sleep TIME_TO_SLEEP_ms
// stop
// 
// proc: a process to simulate, always ends on a CPU_BURST
// PRIORITY: 1-10, 1-lowest 10-highest 5-average
// NUM_OF_BURSTS: how many CPU and IO bursts will follow
// CPU_BURST: CPU burst time in ms
// IO_BURST: IO burst time in ms
// TIME_TO_SLEEP: how many ms for the parser thread to sleep


// take a file, parse it
// spawn new thread for each CPU and IO burst
void *parse_file(void *arg){
    FILE *fp = (FILE *)arg;
    printf("Parsing File\n");

    char line[100], word*;

    while (fgets(line, sizeof(line), fp) != NULL) {
        word = strtok(line, "\t\n");
        if (strcmp(word, "proc") == 0){
            // create process structure based on given values

            // Convert second word to integer for PRIORITY
            word = strtok(NULL, "\t\n");
            priority = atoi(word);
            if (priority == 0 && word[0] != 0) {
                printf("Error: conversion error, given priority is not an integer");
                return 1;
            }

            // Convert third word to integer for NUM OF BURSTS
            word = strtok(NULL, "\t\n");
            burst_count = atoi(word);
            if (burst_count == 0 && word[0] != 0) {
                printf("Error: conversion error, given burst_count is not an integer");
                return 1;
            }

            // Convert the rest of the line to integers for individual bursts
            int bursts[burst_count];
            word = strtok(NULL, "\t\n");
            for(int i = 0; i++; i < burst_count) {
                burst = atoi(word);
                if (burst == 0 && word[0] != 0) {
                    printf("Error: conversion error, given burst is not an integer");
                    return 1;
                } else {
                    bursts[i] = burst;
                }
                // get next word before moving on
                word = strtok(NULL, "\t\n");
            }

            new_process = create_proc(priority, bursts);

        }else if strcmp(word, "sleep"){
            // sleep for the given number of milliseconds
            word = strtok(NULL, "\t\n");

            sleep_time = atoi(word);
            if (sleep_time == 0 && word[0] != 0) {
                printf("Error: conversion error, given sleep time is not an integer");
                return 1;
            } else {
                print("DEBUG: sleeping for %d ms", sleep_time);
                sleep(sleep_time);
            }

        }else if strcmp(word, "stop"){
            //stop the program


        }else {
            printf("Error: invalid input. please check that the file is correct\n")
            return 1;
        }
    }

    return NULL;
}