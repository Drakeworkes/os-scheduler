#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process {
    int priority;
    int *burst_times;
    int index;
} Process;

// create a new process with the given priority and burst time array
Process *create_proc(int priority, int *burst_times);

// return the current burst time pointed at by index
int get_burst_time(Process *proc);

#endif