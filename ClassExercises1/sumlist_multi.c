//
//  sumlist_multi.c
//  
//
//  Created by Jessica Manchak on 3/9/23.
//

#include "sumlist_multi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_NO_OF_THREADS 2
#define MAX_NO_OF_ELEMENTS 100000000

typedef struct arg_data {
    int thread_number;
} arg_data;

//shared data on which threads will work concurrently
//array which will be summed
static int arr[MAX_NO_OF_ELEMENTS];
//sum variable that will store the total sum
static long long int sum;

void* worker_sum(void* arg){
    arg_data* current_thread_data = (arg_data*)arg;
    printf("Current thread no is : %d\n", current_thread_data->thread_number);
    //Determine the bounds
    static int arraySize = sizeof(arr) / sizeof(arr[0]);
    static int startpart = 0;
    static int endpart = MAX_NO_OF_ELEMENTS;
    
    
    printf("Here we will sum %d to %d\n", arr[startpart], arr[endpart - 1]);
    
    int current_thread_sum;
    //Generate the sum
    if(current_thread_data->thread_number == 0){
        for(int i = 0; i < arraySize/2; i++){
            current_thread_sum = current_thread_sum + arr[i];
        }
    }
    else{
        for(int i = arraySize/2; i < arraySize; i++){
            current_thread_sum = current_thread_sum + arr[i];
        }
    }
    
    sum += current_thread_sum;
    return NULL;
}

int main(){
    //let the array consists of first MAX_NO_OF_ELEMENTS integers,
    //1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++){
        arr[i] = i + 1;
    }
    
    //pthread objects
    pthread_t id[MAX_NO_OF_THREADS];
    
    //argument data to send in worker functions
    arg_data arg_arr[MAX_NO_OF_THREADS];
    
    //total number of threads we will create
    int no_of_threads = MAX_NO_OF_THREADS;
    printf("Creating %d number of threads...\n", no_of_threads);
    
    //Setup timing
    clock_t start, end;
    double cpu_time_taken;
    
    start = clock();
    
    int thread_no = 1;
    
    
    //creating the child threads
    for(int j = 0; j < no_of_threads; j++){
        pthread_create(&id[j], arg_arr, worker_sum, (void*)NULL);
    }
     
    
    //joining the threads one by one
    for (int k = 0; k < no_of_threads; k++){
        pthread_join(id[k], NULL);
    }
    
    int total_sum = 0;
    for (int i = 0; i < MAX_NO_OF_THREADS; i++){
        total_sum += sum;
    }
    
    end = clock();
    cpu_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("All child threads has finished their works...\n");
    printf("Total sum: %lld\n", total_sum);
    printf("Time taken to sum all the numbers are %lf\n", cpu_time_taken);
    
    return 0;
}
