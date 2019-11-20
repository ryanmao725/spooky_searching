#include "multitest.h"

int searcher(int* array, int startIndex, int endIndex, int value) {
    //printf("Start: %d, end: %d\n", startIndex, endIndex);
    int i = 0;
    for (i = startIndex; i < endIndex; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}

int driver(int* array, int size, int start, int value) {
    if (start < size) {
        int fStatus = fork();
        int childPID;
        if (fStatus == 0) {
            int val = searcher(array, start, start + SPLIT_SIZE, value);
            if (val == -1) {
                exit(0);
            } else {
                printf("found: %d\n", val);
                exit(val - start + 1);
            }
        } else {
            int idx = driver(array, size, start + SPLIT_SIZE, value);
            printf("received: %d\n", idx);
            wait(&childPID);
            if (WIFEXITED(childPID)) {
                int cStatusCode = WEXITSTATUS(childPID);
                printf("Status Code: %d\n", cStatusCode);
                //printf("Completed %d, %d, %d\n", start, startIndex, cStatusCode);
                if (cStatusCode == 0) {
                    if (idx > 0) {
                        printf("returning: %d\n", idx);
                        return idx;
                    } else {
                        printf("returning: %d\n", -1);
                        return -1;
                    }
                } else {
                    printf("returning: %d | status: %d | start: %d\n", cStatusCode - 1 + start, cStatusCode, start);
                    return cStatusCode - 1 + start;
                }
            }
        }
    } else {
        return -1;
    }
}

int search(int* _array, int _size, int _value) {
    printf("\n");
    return driver(_array, _size, 0, _value);
}
