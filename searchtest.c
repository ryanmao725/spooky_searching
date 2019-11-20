#include <stdlib.h>
#include <stdio.h>
#include "multitest.h"

//Define a macro for the size of the array.
#define ARRAY_SIZE 1000

void print(int* ARRAY, int SIZE) {
    int i = 0;
    for (i; i < SIZE; i++) {
        printf("%d, ", ARRAY[i]);
    }
}

void scramble(int* ARRAY, int SIZE) {
    int i =0;
    int SF = SIZE / 4 * 3;
    printf("Scramble Factor: %d\n", SF);
    for (i; i < SF; i++) {
        int index_1 = rand() % SIZE;
        int index_2 = rand() % SIZE;
        int temp = ARRAY[index_1];
        ARRAY[index_1] = ARRAY[index_2];
        ARRAY[index_2] = temp;
    }
}

int* generate(int SIZE) {
    int* ARRAY = malloc(sizeof(int*) * SIZE);
    int i = 0;
    for (i; i < SIZE; i++) {
        ARRAY[i] = i;
    }
    return ARRAY;
}

int main(int argc, char** argv) {
    int* ARRAY = generate(ARRAY_SIZE);
    scramble(ARRAY, ARRAY_SIZE);
    print(ARRAY, ARRAY_SIZE);
    int index = search(ARRAY, ARRAY_SIZE, 90);
    printf("FOUND at Index %d -> %d\n", index, ARRAY[index]);
    return 0;
}
