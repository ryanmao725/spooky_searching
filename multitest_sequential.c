// Necessary imports to make this application run
#include "multitest.h"

/**
 * Search implementation using a standard sequential linear search
 */
int search(int* array, int size, int value, int SPLIT_SIZE) {
    // Linear Search....
    int i = 0;
    for (i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}
/**
 * Tell anyone who cares what type of search implementation we are using
 */
char* getMode() {
    return "sequential";
}
