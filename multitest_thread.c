#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "multitest.h"

typedef struct thread_input {
    int value;
    int start_index;
    int end_index;
    int* ARRAY;
} thread_input;

void* thread_search(void* input_arg) {
    thread_input arg_struct = *(thread_input*)input_arg;
    int* ARRAY = arg_struct.ARRAY;
    int value = arg_struct.value;
    int start_index = arg_struct.start_index;
    int end_index = arg_struct.end_index;
    int index = start_index;
    for (index = start_index; index < end_index; index++) {
        if (ARRAY[index] == value) {
            return (void*) index;
        }
    }
    return (void*) -1;
}


int search(int* ARRAY, int SIZE, int VALUE) {
    int number_of_splits = SIZE % SPLIT_SIZE == 0 ? SIZE / SPLIT_SIZE : SIZE / SPLIT_SIZE + 1;
    pthread_t threads[number_of_splits];
    int i = 0;
    for (i = 0; i < number_of_splits; i++) {
        thread_input* arg_struct = malloc(sizeof(thread_input));
        arg_struct->value = VALUE;
        arg_struct->start_index = i * SPLIT_SIZE;
        arg_struct->end_index = SIZE < (i + 1) * SPLIT_SIZE ? SIZE : (i + 1) * SPLIT_SIZE;
        arg_struct->ARRAY = ARRAY;
        pthread_create(&threads[i], NULL, thread_search, (void*)arg_struct);
    }
    i = 0;
    int return_val = -1;
    void* return_pointer = NULL;
    for (i = 0; i < number_of_splits; i++) {
        pthread_join(threads[i], &return_pointer);
        if (return_pointer != -1) {
            return_val = return_pointer;
        }
    }
    return return_val;
}
