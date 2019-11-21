#include <unistd.h>
#include "multitest.h"

int search(int* array, int size, int value, int SPLIT_SIZE) {
    int numSplits = size % SPLIT_SIZE == 0 ? size / SPLIT_SIZE : (size / SPLIT_SIZE) + 1;
    pid_t* pid = malloc(sizeof(pid_t) * numSplits);
    int i = 0;
    for (i = 0; i < numSplits; i++) {
        if ((pid[i] = fork()) == 0) {
            int index = 0;
            for (index = 0; index < SPLIT_SIZE; index++) {
                if (array[SPLIT_SIZE * i + index] == value) {
                    exit(index + 1);
                }
            }
            exit(0);
        }
    }
    int stat;
    int ret = -1;
    for (i = 0; i < numSplits; i++) {
        pid_t cpid = waitpid(pid[i], &stat, 0);
        if (WIFEXITED(stat)) {
            int statusCode = WEXITSTATUS(stat);
            if (statusCode > 0) {
                ret = statusCode + (SPLIT_SIZE * i) - 1;
            }
        }
    }
    return ret;
}

char* getMode() {
    return "process";
}
