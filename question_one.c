/*
 * CSCI 3310 System Programming
 * Assignment 1 Question 1
 * Team Members: Johnathan Forrester, Jack Harlock, Konner Yi, Brayden Johnson
 * Group Number: Group 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <command1> <command2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child 
        printf("Child process (PID: %d) executing command: %s\n", getpid(), argv[1]);

        char *args[] = {argv[1], NULL};
        execvp(args[0], args);

        // only called in case of error
        perror("execvp failed in child");
        exit(EXIT_FAILURE);
    } 
    else {
        // Parent 
        wait(NULL);

        printf("Parent process (PID: %d) executing command: %s\n", getpid(), argv[2]);

        char *args[] = {argv[2], NULL};
        execvp(args[0], args);

        perror("execvp failed in parent");
        exit(EXIT_FAILURE);
    }

    return 0;
}