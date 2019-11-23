/*
 * @author Shivan Modha and Ryan Mao
 * @description RU CS214 2019
 * @creation 11/21/19
 */
// macros
#define MAX_SPLIT_SIZE 255
#define SIZE 1000
#define SPLIT 100

// necessary imports
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "multitest.h"

typedef struct batch_results {
    long total;
    long average;
    long min;
    long max;
    long stdev;
} BatchResults;

// function definitions
void print(int* _array, int _size); // Print an array
void scramble(int* _array, int _size); // Scramble an array
int* generate(int _size); // Create a sequential array of size
int srch(int* _array, int _size, int _value, int _splitSize); // Wrapper to the search function, to verify the split size doesn't exceed MAX_SPLIT_SIZE
BatchResults execute(int* _array, int _size, int _splitSize, int _iterations); // Execute a singular test unit
// test function definitions
int test_verify(int* _array, int _size, int _splitSize);

/**
 * application entry point
 */
int main(int argc, char** argv) {
    printf("*******************************************************\n");
    printf("Search Testing Application\n");
    printf("\tMode: %s\n", getMode());
    printf("*******************************************************\n");
    printf("\n");
    printf("Test 1: Functionality Verification\n");
    printf("    --(n=%d, ns=%d)-->\n", SIZE, SPLIT);
    int* list = generate(SIZE);
    //srch(list, 100, 5, 10);
    int success = test_verify(list, SIZE, SPLIT);
    if (success != 0) {
        exit(1);
    }
    printf("\n*******************************************************\n\n");
    printf("Test 2: Trend Analysis - Varying Size\n");
    printf("n\tns\ttotal\taverage\tmin\tmax\tstdev\n");
    int i = 10;
    for (i = 10; i < 1001; i += 10) {
        scramble(list, i);
        BatchResults br = execute(list, i, SPLIT, 100);
        if (br.total < 0) {
            i -= 10;
        } else {
            printf("%d\t%d\t%li\t%li\t%li\t%li\t%li\n", i, SPLIT, br.total, br.average, br.min, br.max, br.stdev);
        }
    }
    printf("\n*******************************************************\n\n");
    printf("Test 3: Trend Analysis - Varying Splits\n");
    printf("n\tns\ttotal\taverage\tmin\tmax\tstdev\n");
    i = 10;
    for (i = 10; i < 251; i += 10) {
        scramble(list, i);
        BatchResults br = execute(list, SIZE, i, 100);
        if (br.total < 0) {
            i -= 10;
        } else {
            printf("%d\t%d\t%li\t%li\t%li\t%li\t%li\n", SIZE, i, br.total, br.average, br.min, br.max, br.stdev);
        }
    }
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
        return dummy(_array, _size, _value, MAX_SPLIT_SIZE);
    } else {
        return dummy(_array, _size, _value, _splitSize);
    }
}
/**
 * define a singular test run
 */
BatchResults execute(int* _array, int _size, int _splitSize, int _iterations) {
    struct timeval tv_start, tv_end;
    gettimeofday(&tv_start, NULL);
    int i = 0;
    BatchResults br;
    br.average = 0;
    br.min = 10000000;
    br.max = 0;
    br.stdev = 0;
    int* ptr = malloc(sizeof(int) * _iterations);
    for (i = 0; i < _iterations; i++) {
        int index = rand() % _size;
        struct timeval t_start, t_end;
        gettimeofday(&t_start, NULL);
        srch(_array, _size, _array[index], _splitSize);
        gettimeofday(&t_end, NULL);
        ptr[i] = (t_end.tv_usec - t_start.tv_usec);
        br.average += ptr[i];
        if (ptr[i] < br.min) {
            br.min = ptr[i];
        }
        if (ptr[i] > br.max) {
            br.max = ptr[i];
        }
    }
    br.average /= _iterations;
    gettimeofday(&tv_end, NULL);
    br.total = (tv_end.tv_usec - tv_start.tv_usec);
    for (i = 0; i < _iterations; i++) {
        br.stdev += (ptr[i] - br.average) * (ptr[i] - br.average);
    }
    if (_iterations > 1) {
        br.stdev /= (_iterations - 1);
        br.stdev = (long)sqrt((double)br.stdev);
    } else {
        br.stdev = 0;
    }
    return br;
}

int test_verify(int* _array, int _size, int _splitSize) {
    scramble(_array, _size);
    int i = 0;
    for (i = 0; i < _size; i++) {
        int index = srch(_array, _size, _array[i], _splitSize);
        if (i != index) {
            printf("        Error: Expected %d, but received %d.\n", i, index);
            return -1;
        }
    }
    printf("        Pass! Stress tests can begin!\n");
    return 0;
}
