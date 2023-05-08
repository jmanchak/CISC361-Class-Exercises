//
//  sumlist_single.c
//  
//
//  Created by Jessica Manchak on 3/2/23.
//

#include "sumlist_single.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_NO_OF_ELEMENTS 100000000

static long long int sum;
static int arr[MAX_NO_OF_ELEMENTS];

int main()
{
    //let the array consists of first MAX_NO_OF_ELEMENTS integers,
    //1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++){
        arr[i] = i + 1;
    }

    
    //Setup timing
    clock_t start, end;
    double cpu_time_taken;
    start = clock();
    
    //Summing code here
    for (int j = 0; j < MAX_NO_OF_ELEMENTS; j++){
        sum = sum + arr[j];
    }
    
    //Time calculations here
    end = clock();
    cpu_time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("Total sum: %lld\n", sum);
    printf("Time taken to sum all the numbers are %lf\n", cpu_time_taken);
    
    return 0;
}
