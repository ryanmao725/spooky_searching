// Include relevant libraries and packages
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "multitest.h"

// Global variables used to maintain state
static int* ARRAY = NULL;
static int SIZE = -1;
static int VALUE = -1;
static int SPLIT_SIZE = -1;

// Threading input structure to make it easier to send values
typedef struct thread_input {
    int value;
    int start_index;
    int end_index;
    int* ARRAY;
    int index;
} thread_input;

/**
 * Inner sequential search implemented for the thread itself
 */
void* thread_search(void* input) {
    // Retrieve the split number
    int split_number = *(int*)input;
    // Get the starting index of the linear search
    int start_index = split_number * SPLIT_SIZE;
    // Get the end index of the linear search
    int end_index = SIZE < (split_number + 1) * SPLIT_SIZE ? SIZE : (split_number + 1) * SPLIT_SIZE;
    // Linear Search!
    int index = start_index;
    for (index; index < end_index; index++) {
        if (ARRAY[index] == VALUE) {
            *((int*)input) = index;
            pthread_exit((void*)-1);
        }
    }
    // Create the output values, and exit
    *((int*)input) = -1;
    pthread_exit(NULL);
}

/**
 * Search implementation using threads
 */
int search(int* _ARRAY, int _SIZE, int _VALUE, int _SPLIT_SIZE) {
    // Set all variables globally.
    ARRAY = _ARRAY;
    SIZE = _SIZE;
    VALUE = _VALUE;
    SPLIT_SIZE = _SPLIT_SIZE;
    // Calculate the number of workers necessary to execute
    int number_of_splits = SIZE % SPLIT_SIZE == 0 ? SIZE / SPLIT_SIZE : SIZE / SPLIT_SIZE + 1;
    // Create the threads
    pthread_t threads[number_of_splits];
    int thread_inputs[number_of_splits];
    int i = 0;
    for (i = 0; i < number_of_splits; i++) {
        // Establish the thread inputs, and then spawn the thread
        thread_inputs[i] = i;
        pthread_create(&threads[i], NULL, thread_search, (void*)&thread_inputs[i]);
    }
    // Wait for all of the threads to finish, and then parse through the output
    i = 0;
    int return_val = -1;
    void* return_pointer = NULL;
    for (i = 0; i < number_of_splits; i++) {
        pthread_join(threads[i], &return_pointer);
        // If we are not null, we know that we have a returned value
        if (return_pointer != NULL) {
            return_val = thread_inputs[i];
        }
    }
    return return_val;
}
/**
 * Tell others what type of search we implemented
 */
char* getMode() {
    return "thread";
}
