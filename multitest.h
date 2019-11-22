#ifndef MULTITEST_H
#define MULTITEST_H

#include <stdlib.h>
#include <stdio.h>
#define dummy(x, y, u, w) search(x, y, u, w)


int search(int* _array, int _size, int _value, int SPLIT_SIZE);
char* getMode();

#endif
