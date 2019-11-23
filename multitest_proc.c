// Include the default header files necessary
#include <unistd.h>
#include "multitest.h"

/**
 * Search implementation using multiprocessing (forks)
 */
int search(int* array, int size, int value, int SPLIT_SIZE) {
    // Calculate the initial number of workers that we need
    int numSplits = size % SPLIT_SIZE == 0 ? size / SPLIT_SIZE : (size / SPLIT_SIZE) + 1;
    // Create a list of the child process id's
    pid_t* pid = malloc(sizeof(pid_t) * numSplits);
    int i = 0;
    for (i = 0; i < numSplits; i++) {
        // Fork! Create a process!
        if ((pid[i] = fork()) == 0) {
            // If in the child, perform a sequential search for the given range
            int index = 0;
            for (index = 0; index < SPLIT_SIZE; index++) {
                // If we are still within the array size, and we have found the value, exit the process thread
                if (SPLIT_SIZE * i + index < size && array[SPLIT_SIZE * i + index] == value) {
                    // The status value of the exit will be 1 + the relative index. This way, the 0'th index will return a 1, reserving the 0 return value for not finding the value
                    exit(index + 1);
                }
            }
            // If we didn't find anything, the process will exit with a 0
            exit(0);
        } else {
            // Continue along with the loop of spawning more processes
            continue;
        }
    }
    // Once we have spawned the different processes, let's wait for them to return one by one
    int stat;
    int ret = -1;
    for (i = 0; i < numSplits; i++) {
        // Wait for the specific process to finish
        pid_t cpid = waitpid(pid[i], &stat, 0);
        // Fetch the status code of the exited process
        if (WIFEXITED(stat)) {
            int statusCode = WEXITSTATUS(stat);
            // If it is not 0, we know that we have found the value at a relative index
            if (statusCode > 0) {
                ret = statusCode + (SPLIT_SIZE * i) - 1;
            }
        }
    }
    // Return our value
    return ret;
}

/**
 * Tell others what type of searching implementation we used
 */
char* getMode() {
    // Let the main driver application know that we are a process implementation
    return "process";
}
