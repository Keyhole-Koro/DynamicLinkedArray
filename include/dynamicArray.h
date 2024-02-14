#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "overlapHandler.h"
#include "dataTypeHandler.h"
#include "utils.h"

typedef struct {
    DataType dataType;
    int dataSize; // used to ensure that a struct of a subject is the same as an elements' that its array contains
    void **dataArray; // Placeholder for array of data elements
    int offset; // Offset value
    int capacity; // Capacity of the dynamic array
    OverlapArray *overlapArray;
    int (*referentMember)(void*, DataType); // Function pointer for getting member based on data type
    bool allowModification; // If true, allows modification of the array
} DynamicArray;

DynamicArray *createDynamicArray(int initialCapacity, bool allowModification, int (*referentMember)(void *, DataType), DataType type);

void addToDynamicArray(DynamicArray *dArr, void *data, DataType type);

void copyAndAddToDynamicArray(DynamicArray *dArr, void *data, DataType type);

void *retriveData(DynamicArray *dArr, int pos, DataType type);

void *fetchMatchingData(DynamicArray *dArr, void *expectedData, DataType type);

void reallocateDynamicArray(DynamicArray *dArr);

void initializeElementsInDynamicArray(DynamicArray *dArr, int startIndex);

DynamicArray *cloneArray(DynamicArray *originaldArr);

void destroyDynamicArray(DynamicArray* dArr);

#endif
