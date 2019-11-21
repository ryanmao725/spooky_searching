/*
 * @author Shivan Modha and Ryan Mao
 * @description RU CS214 2019
 * @creation 11/21/19
 */
// macros
#define MAX_SPLIT_SIZE 250
#define SIZE 20000
#define SPLIT 1000

// necessary imports
#include <stdlib.h>
#include <stdio.h>
#include "multitest.h"

// function definitions
void print(int* _array, int _size); // Print an array
void scramble(int* _array, int _size); // Scramble an array
int* generate(int _size); // Create a sequential array of size
int srch(int* _array, int _size, int _value, int _splitSize); // Wrapper to the search function, to verify the split size doesn't exceed MAX_SPLIT_SIZE

// test function definitions
void test_verify(int* _array, int _size, int _splitSize);

/**
 * application entry point
 */
int main(int argc, char** argv) {
    int* list = generate(SIZE);
    test_verify(list, SIZE, SPLIT);
    return 0;
}

/**
 * given an array, print it out
 */
void print(int* _array, int _size) {
    // create the looper variable
    int i = 0;
    // loop
    for (i = 0; i < _size; i++) {
        printf("%d, ", _array[i]);
    }
}
/**
 * given an array, scramble the array values by swapping values
 */
void scramble(int* _array, int _size) {
    int i =0;
    int SF = _size / 4 * 3;
    for (i = 0; i < SF; i++) {
        int index_1 = rand() % _size;
        int index_2 = rand() % _size;
        int temp = _array[index_1];
        _array[index_1] = _array[index_2];
        _array[index_2] = temp;
    }
}
/**
 * create an array of specified size
 */
int* generate(int _size) {
    int* ARRAY = malloc(sizeof(int) * _size);
    int i = 0;
    for (i = 0; i < _size; i++) {
        ARRAY[i] = i;
    }
    return ARRAY;
}
/**
 * search wrapper function
 */
int srch(int* _array, int _size, int _value, int _splitSize) {
    if (_splitSize > MAX_SPLIT_SIZE) {
        return search(_array, _size, _value, MAX_SPLIT_SIZE);
    } else {
        return search(_array, _size, _value, _splitSize);
    }
}

void test_verify(int* _array, int _size, int _splitSize) {
    scramble(_array, _size);
    int i = 0;
    for (i = 0; i < _size; i++) {
        int index = srch(_array, _size, _array[i], 250);
        if (i != index) {
            printf("Verification Failed: Expected Index %d, Received Index %d. Searched for %d.\n", i, index, _array[i]);
            break;
        } else {
            printf("Pass: %d\n", i);
        }
    }
}
