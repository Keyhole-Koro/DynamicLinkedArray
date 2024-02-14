#ifndef OVERLAP_HANDLER
#define OVERLAP_HANDLER

#include "dynamicArray.h"

typedef struct {
    bool *elementExistenceArray; // Array containing 0 or 1 indicating existence of elements
    int capacity; // Capacity of the overlapping array
} OverlapArray;

#endif