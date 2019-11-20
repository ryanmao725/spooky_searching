#include <stdlib.h>
#include <stdio.h>
#include "multitest.h"

//Define a macro for the size of the array.
#define ARRAY_SIZE 1000

void print(int* _array, int _size) {
    int i = 0;
    for (i = 0; i < _size; i++) {
        printf("%d, ", _array[i]);
    }
}

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

int* generate(int _size) {
    int* ARRAY = malloc(sizeof(int) * _size);
    int i = 0;
    for (i = 0; i < _size; i++) {
        ARRAY[i] = i;
    }
    return ARRAY;
}

int main(int argc, char** argv) {
    int* array = generate(ARRAY_SIZE);
    scramble(array, ARRAY_SIZE);
    //print(array, ARRAY_SIZE);
    int index = search(array, ARRAY_SIZE, 90);
    printf("FOUND at Index %d -> %d using mode %s\n", index, array[index], getMode());
    return 0;
}
