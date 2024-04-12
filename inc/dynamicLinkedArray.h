#ifndef DYNAMIC_LINKED_ARRAY_H
#define DYNAMIC_LINKED_ARRAY_H

#include <stdbool.h>

#include "dataType.h"
#include "overlap.h"

typedef struct ArrayNode ArrayNode;

typedef struct {
    char *name;
    DataType *dataType;
    ArrayNode *array;
    int offset; // Offset value
    int capacity; // Capacity of the dynamic array
    OverlapArray *overlapArray;
    int (*referentMember)(void*, DataType*); // Function pointer for getting member based on data type
    bool allowModification; // If true, allows modification of the array
    bool allowOverlapping; // true allows overlapping
} DynamicArray;

struct ArrayNode {
    void *Array
    ArrayNode *next;
};

#endif