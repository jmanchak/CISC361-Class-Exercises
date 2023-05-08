//
//  finalproject.c
//  
//
//  Created by Jessica Manchak on 4/30/23.
//

#include "finalproject.h"

//Structs for the process & device
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int memory_required
    int time_left;
    int priority;
    int device_required;
};

struct Device{
    int device_id;
    bool is_busy;
    int process_using;
};

//Define global variables
std::vector<Process> hold_queue;
std::queue<Process> ready_queue;
std::queue<Process> wait_queue;
Device devices[MAX_DEVICES];
Process process_table[MAX_PROCESSES];
int time_slice = 4;
int current_time = 0;
int available_memory = 256;
int num_processes = 0;

//Define function for sorting Hold Queue based on SJF algorithm
bool sjf_compare(Process p1, Process p2){
    return p1.burst_time < p2.burst_time;
}

//Define function for sorting Hold Queue based on FIFO algorithm
bool fifo_compare(Process p1, Process p2){
    return p1.arrival_time < p2.arrival_time;
}

//Define function for adding a process to the Hold Queue
void add_to_hold_queue(Process p, std::string algorithm){
    if(available_memory < p.memory_required){
        hold_queue.push_back(p);
        if(algorithm == "sjf"){
            std::sort(hold_queue.begin(), hold_queue.end(), sjf_compare);
        }else if(algorithm == "fifo"){
            std::sort(hold_queue.begin(), hold_queue.end(), fifo_compare);
        }
    }else{
        available_memory -= p.memory_required;
        p.time_left = p.burst_time;
        ready_queue.oush(p)
    }
}
