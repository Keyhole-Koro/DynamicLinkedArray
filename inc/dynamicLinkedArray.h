#ifndef DYNAMIC_LINKED_ARRAY_H
#define DYNAMIC_LINKED_ARRAY_H

#include <stdio.h>
#include <stdbool.h>

#include "dataType.h"
#include "overlap.h"

typedef struct ArrayNode ArrayNode;

typedef struct {
    char *name;
    DataType *dataType;
    ArrayNode *arrayNode;
    int offset; // Offset value
    int capacity; // Capacity of the dynamic array
    int arrayLength; // Number of elements per an array
    OverlapArray *overlapArray;
    int (*referentMember)(void*, DataType*); // Function pointer for getting member based on data type
    bool allowModification; // If true, allows modification of the array
    bool allowOverlapping; // true allows overlapping
} DynamicLinkedArray;

struct ArrayNode {
    void *array
    ArrayNode *next;
};

inline void arraySize(DynamicLinkedArray *dArr) {
    return dArr->dataType->size * dArr->arrayLength;
}

inline bool isOutOfRange(DynamicLinkedArray *dArr, int index) {
    return index < 0 || index > getArrayOffset(dArr);
}


#endif