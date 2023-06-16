/*

Name of file: chatbots.c
Team: Kobi Bell and Mark Duraid
Class: CS 480
Assignment #1

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>

#define FILENAME "QUOTE.txt"
#define NUM_THREADS 7

sem_t FLAG;
FILE *file;

void* thread_func(void* arg) {
    int tid = *(int*)arg;
    int i;
    for (i = 0; i < 8; i++) {

        // Waiting for semaphore
        if (tid % 2 == 0) {
            sleep(2);
            if (sem_wait(&FLAG) == -1) {
                perror("Error waiting for semaphore");
                exit(EXIT_FAILURE);
            }
            FILE* file = fopen("QUOTE.txt", "a");
            if (file == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }
            if (fprintf(file, "Thread %d: Controlling complexity is the essence of computer programming. --Brian Kernigan\n", tid) < 0) {
                perror("Error writing to file");
                exit(EXIT_FAILURE);
            }
            if (fclose(file) == -1) {
                perror("Error closing file");
                exit(EXIT_FAILURE);
            }
            printf("Thread %d is running\n", tid);
            if (sem_post(&FLAG) == -1) {
                perror("Error releasing semaphore");
                exit(EXIT_FAILURE);
            }
        } else {
            sleep(3);
            if (sem_wait(&FLAG) == -1) {
                perror("Error waiting for semaphore");
                exit(EXIT_FAILURE);
            }
            FILE* file = fopen("QUOTE.txt", "a");
            if (file == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }
            if (fprintf(file, "Thread %d: Computer science is no more about computers than astronomy is about telescopes. --Edsger Dijkstra\n", tid) < 0) {
                perror("Error writing to file");
                exit(EXIT_FAILURE);
            }
            if (fclose(file) == -1) {
                perror("Error closing file");
                exit(EXIT_FAILURE);
            }
            printf("Thread %d is running\n", tid);
            if (sem_post(&FLAG) == -1) {
                perror("Error releasing semaphore");
                exit(EXIT_FAILURE);
            }
        }
    }
    return NULL;
}

int main() {
    // Create file and write PID
    file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", getpid());
    if (fclose(file) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    // Create the semaphore
    if (sem_init(&FLAG, 0, 1) == -1) {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }

    // Create the threads
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error joining thread");
            exit(EXIT_FAILURE);
        }
    // Destroy the semaphore
    if (sem_destroy(&FLAG) == -1) {
        perror("Error destroying semaphore");
        exit(EXIT_FAILURE);
    }

    // Print exit message
    printf("All threads have finished. Exiting program.\n");

    return 0;
}
}