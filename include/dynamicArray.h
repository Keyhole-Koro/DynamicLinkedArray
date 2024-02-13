#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dataTypeHandler.h"

typedef struct {
    DataType dataType;
    int dataSize;
    void **dataArray; // Placeholder for array of data elements
    bool allowOverlapping; // If true, allows overlapping
    bool *elementExistence; // Array containing 0 or 1 indicating existence of elements
    int overlappingCapacity; // Capacity of the overlapping array
    int (*referentMember)(void*, DataType); // Function pointer for getting member based on data type
    bool allowModification; // If true, allows modification of the array
    int offset; // Offset value
    int capacity; // Capacity of the dynamic array
} DynamicArray;

void initializeBoolArray(bool *arr, int size);

#endif
