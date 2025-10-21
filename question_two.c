/*
 * CSCI 3310 System Programming
 * Assignment 1 Question 2
 * Team Members: Johnathan Forrester, Jack Harlock, Konner Yi, Brayden Johnson
 * Group Number: Group 1
 */

#include<stdio.h>//printf
#include<string.h>
#include<unistd.h>//unix speciific
#include<sys/types.h>//pid_t
#include<sys/wait.h>//wait
#include<stdlib.h>
#include<errno.h>

int main(int argc, char const *argv[])
{
    //Only activates IF # of args greater than one
    if(argc>1){
        char *endptr;
        errno = 0;

        //Tries to convert given number to long, checks for non-numerics and overflow, returns error if present
        long numArgs = strtol(argv[1], &endptr, 10);
        if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE) {
            printf("can not convert to integer\n");
            return 1;   
        }

        //Creates a child process, then the child prints the parent and child PID
        pid_t pid=fork();
        if(pid==0){
            printf("Child Process: PID=%d, Parent PID=%d\n", getpid(), getppid());
        }

        //Allocates heap memory according to the size of parentArr, then fills parentArr with values starting from 0 to sizeof-1
        //Note that both the child and parent fill allocate different memory and fill different arrays
        int* parentArr=malloc(sizeof(int)*numArgs);
        for(long i=0;i<numArgs;i++){
            parentArr[i]=i;
        }

        //Parent ONLY
        if(pid>0){
            //Wait for child to finish, then print parent array 0 to sizeof-1, then free heap space
            wait(NULL);
            printf("Parent Array: ");
            for(long i=0;i<numArgs;i++){
                printf("%d ",parentArr[i]);

            }
            printf("\n");
            free(parentArr);
            parentArr=NULL;
        }

        //Child ONLY
        if(pid==0){
            //Print parent ID, print child array 0 to sizeof-1, then end child process after freeing heap space
            printf("Parent PID=%d\n", getppid());
            int* childArr=malloc(sizeof(int)*numArgs);
            for(long i=0;i<numArgs;i++){
                childArr[i]=i;
            }
            printf("Child Array: ");
            for(long i=0;i<numArgs;i++){
                printf("%d ",childArr[i]);
            }
            printf("\n");
            free(childArr);
            childArr=NULL;
            exit(0);
        }
        

    }
    return 0;
}
