#include "multitest.h"

int search(int* array, int size, int value) {
    int i = 0;
    for (i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}

char* getMode() {
    return "sequential";
}
