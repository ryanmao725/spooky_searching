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

// structure to hold all of the batch results data
typedef struct batch_results {
    long total; // total batch execution time (including time between calls)
    long average; // average execution time
    long min; // minimum execution time
    long max; // maximum execution time
    long stdev; // standard deviation time (error checking)
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
    // Print out the initial starting points
    printf("*******************************************************\n");
    printf("Search Testing Application\n");
    printf("\tMode: %s\n", getMode());
    printf("*******************************************************\n");
    printf("\n");
    printf("Test 1: Functionality Verification\n");
    printf("    --(n=%d, ns=%d)-->\n", SIZE, SPLIT);
    // Generate the list that we will be searching through for our tests
    int* list = generate(SIZE);
    // Run the initial verification tests
    int success = test_verify(list, SIZE, SPLIT);
    // Verify that the verification tests are successful. If they aren't, don't even bother running stress tests because the search implementation we know doesn't work
    if (success != 0) {
        exit(1);
    }
    // Begin the second test suite, where we will vary the size of our search. Note that here we aren't generating new lists, but just lying to the function (telling it that our array size is less than it actually is)
    printf("\n*******************************************************\n\n");
    printf("Test 2: Trend Analysis - Varying Size\n");
    printf("n\tns\ttotal\taverage\tmin\tmax\tstdev\n");
    int i = 10;
    for (i = 10; i < 1001; i += 10) {
        // Loop through for every 10 array size. Generate a new random array by rescrambling what we already have
        scramble(list, i);
        // Run the test with the variable inputs
        BatchResults br = execute(list, i, SPLIT, 100);
        // For some reason, the total value is less than 0?? (its negative??). Just rerun the test...
        if (br.total < 0) {
            i -= 10;
        } else {
            // Print to the console window in TSV format so we can parse through our massive amounts of data with python
            printf("%d\t%d\t%li\t%li\t%li\t%li\t%li\n", i, SPLIT, br.total, br.average, br.min, br.max, br.stdev);
        }
    }
    // Begin the third test suite, where we will vary the split size of our search.
    printf("\n*******************************************************\n\n");
    printf("Test 3: Trend Analysis - Varying Splits\n");
    printf("n\tns\ttotal\taverage\tmin\tmax\tstdev\n");
    i = 10;
    for (i = 10; i < 251; i += 10) {
        // Loop through for every 10 split size. Generate a new random array by rescrambling what we already have
        scramble(list, i);
        // Run the test with the variable inputs
        BatchResults br = execute(list, SIZE, i, 100);
        if (br.total < 0) {
            i -= 10;
        } else {
            // Print to the console window in TSV format so we can parse through our massive amounts of data with python
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
    // Generate our time holder variables
    struct timeval tv_start, tv_end;
    gettimeofday(&tv_start, NULL);
    // Initialize our variables
    int i = 0;
    BatchResults br;
    br.average = 0;
    br.min = 10000000;
    br.max = 0;
    br.stdev = 0;
    // Hold the time values
    int* ptr = malloc(sizeof(int) * _iterations);
    for (i = 0; i < _iterations; i++) {
        // For the number of iterations, loop through and execute a random search
        int index = rand() % _size;
        struct timeval t_start, t_end;
        // Generate the start time
        gettimeofday(&t_start, NULL);
        // Execute the physical search (we don't actually care about the output at this time)
        srch(_array, _size, _array[index], _splitSize);
        // Generate the end time
        gettimeofday(&t_end, NULL);
        // Calcualte the time delta
        ptr[i] = (t_end.tv_usec - t_start.tv_usec);
        // Update our stat variables
        if (ptr[i] < 0) {
            ptr[i] = ptr[i] + 1000000;
        }
        br.average += ptr[i];
        if (ptr[i] < br.min) {
            br.min = ptr[i];
        }
        if (ptr[i] > br.max) {
            br.max = ptr[i];
        }
    }
    // Update the stat variables
    br.average /= _iterations;
    // Update the overal run time
    gettimeofday(&tv_end, NULL);
    br.total = (tv_end.tv_usec - tv_start.tv_usec);
    // Calculate the standard deviation
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
/**
 * Verify that the implemented search function actually works
 */
int test_verify(int* _array, int _size, int _splitSize) {
    // Generate a random list by scrambling the file
    scramble(_array, _size);
    // For every value in the array, search for that value and verify it appear in the expected lcoation. If not, signal that there is an error, and print it out to the screen
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
