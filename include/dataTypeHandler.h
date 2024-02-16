#ifndef DATA_TYPE_HANDLER_H
#define DATA_TYPE_HANDLER_H

#define ARRAY_SIZE 5  

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int type;

typedef struct {
    char *name;
    size_t size;
} DataType;

typedef struct {
    bool *elementExistenceArray; // Array containing 0 or 1 indicating existence of elements
    int capacity; // Capacity of the overlapping array
} OverlapArray;

typedef struct {
    char *name;
    DataType *dataType;
    void **dataArray; // Placeholder for array of data elements
    int offset; // Offset value
    int capacity; // Capacity of the dynamic array
    OverlapArray *overlapArray;
    int (*referentMember)(void*, DataType*); // Function pointer for getting member based on data type
    bool allowModification; // If true, allows modification of the array
    bool allowOverlapping; // true allows overlapping
} DynamicArray;

typedef struct {
    int hash;
    void *left;
    void *right;
    void *payload;
} Node;

typedef struct {
    char *name;
    DataType *dataType;
    Node *root;
    int numNode;
    int (*hashCalculation)(void*, DataType*); // the primary parameter has payload
    OverlapArray *overlapArray;
    int (*referentMember)(void*, DataType*); // Function pointer for getting member based on data type
    bool allowOverlapping;
    bool allowModification; // If true, allows modification of the array
} DynamicTree;

extern DataType *dataTypes[];

DataType *registerDataType(char*, int);

#endif