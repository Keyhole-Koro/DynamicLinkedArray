#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dataTypeHandler.h"
#include "utils.h"

typedef struct {
    DataType dataType;
    int dataSize; // used to ensure that a struct of a subject is the same as an elements' that its array contains
    void **dataArray; // Placeholder for array of data elements
    int offset; // Offset value
    int capacity; // Capacity of the dynamic array
    bool allowOverlapping; // If true, allows overlapping
    bool *elementExistence; // Array containing 0 or 1 indicating existence of elements
    int overlapArrayCapacity; // Capacity of the overlapping array
    int (*referentMember)(void*, DataType); // Function pointer for getting member based on data type
    bool allowModification; // If true, allows modification of the array
} DynamicArray;

void initializeBoolArray(bool *arr, int size);

#endif
