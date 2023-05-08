//
//  exercise1.c
//  
//
//  Created by Jessica Manchak on 2/28/23.
//

#include "exercise1.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

int main(){
    // Write C code here
    
    pid_t pid, pid1, pid2;

    pid = fork();
        
    if (pid < 0) { //error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
    }else if(pid == 0){
        pid1 = getpid();
        printf("I am the child: %d\n", pid1);
        pid2 = fork();
        if(pid2 == 0){
            pid1 = getpid();
            printf("I am the grandchild: %d\n", pid1);
    
        }
    }else{
        pid1 = getpid();
        printf("I am the parent: %d\n", pid1);
        wait(NULL);
    }
    
    return 0;
}
