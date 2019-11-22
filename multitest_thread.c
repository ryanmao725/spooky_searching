#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "multitest.h"

static int* ARRAY = NULL;
static int SIZE = -1;
static int VALUE = -1;
static int SPLIT_SIZE = -1;

typedef struct thread_input {
    int value;
    int start_index;
    int end_index;
    int* ARRAY;
    int index;
} thread_input;

void* thread_search(void* input) {
    int split_number = *(int*)input;
    int start_index = split_number * SPLIT_SIZE;
    int end_index = SIZE < (split_number + 1) * SPLIT_SIZE ? SIZE : (split_number + 1) * SPLIT_SIZE;
    int index = start_index;
    for (index; index < end_index; index++) {
        if (ARRAY[index] == VALUE) {
            *((int*)input) = index;
            pthread_exit((void*)-1);
        }
    }
    *((int*)input) = -1;
    pthread_exit(NULL);
}


int search(int* _ARRAY, int _SIZE, int _VALUE, int _SPLIT_SIZE) {
    //Set all variables globally.
    ARRAY = _ARRAY;
    SIZE = _SIZE;
    VALUE = _VALUE;
    SPLIT_SIZE = _SPLIT_SIZE;
    int number_of_splits = SIZE % SPLIT_SIZE == 0 ? SIZE / SPLIT_SIZE : SIZE / SPLIT_SIZE + 1;
    pthread_t threads[number_of_splits];
    int thread_inputs[number_of_splits];
    int i = 0;
    for (i = 0; i < number_of_splits; i++) {
        thread_inputs[i] = i;
        pthread_create(&threads[i], NULL, thread_search, (void*)&thread_inputs[i]);
    }
    i = 0;
    int return_val = -1;
    void* return_pointer = NULL;
    for (i = 0; i < number_of_splits; i++) {
        pthread_join(threads[i], &return_pointer);
        if (return_pointer != NULL) {
            return_val = thread_inputs[i];
        }
    }
    return return_val;
}
char* getMode() {
    return "thread";
}
