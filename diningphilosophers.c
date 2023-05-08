//
//  diningphilosophers.c
//  
//
//  Created by Jessica Manchak on 3/21/23.
//

#include "diningphilosophers.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define Left (i+N-1)%N
#define Right (i+1)%N

void philosopher(int i);
void take_chopsticks(int i);
void put_chopsticks(int i);
void test(int i);

sem_t chopstick[N];
sem_t mutex = 1;

int state[N];

void philosopher(int i){
    state[i] = THINKING;
    while(true){
        //think
        take_chopsticks(i);
        //eat
        put_chopsticks(i);
    }
}

void take_chopsticks(int i){
    wait(&mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(&mutex);
    if(state[i] != EATING){
        wait(&chopstick[i]);
    }
}

void put_chopsticks(int i){
    wait(&mutex);
    state[i] = THINKING;
    test(Left);
    test(Right);
    sem_post(&mutex);
}

void test(int i){
    if (state[i] == HUNGRY && state[Left] !=
        EATING && state[Right] != EATING){
        state[i] = EATING;
        sem_post(&chopstick[i]);
    }
}

int main(){
    pthread_t thread[N];
    int philosophers[N] = {0, 1, 2, 3, 4};
    
    sem_init(&mutex, 0, 1);
    
    for(int i = 0; i < N; i++){
        sem_init(&chopstick[i], NULL, philosopher);
    }
    
    for(int j = 0; j < N; j++){
        pthread_join(thread[j], NULL);
    }
    
    return 0;
}
