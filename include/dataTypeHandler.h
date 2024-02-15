#ifndef DATA_TYPE_HANDLER_H
#define DATA_TYPE_HANDLER_H

#define ARRAY_SIZE 5  

#include <stdbool.h>

typedef int type;

typedef enum {
    INT = 0,
    EXPR,
} DataType;

typedef struct {
    bool *elementExistenceArray; // Array containing 0 or 1 indicating existence of elements
    int capacity; // Capacity of the overlapping array
} OverlapArray;

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

typedef struct {
    int hash;
    void *left;
    void *right;
    void *payload;
} Node;

typedef struct {
    DataType dataType;
    int dataSize; // used to ensure that a struct of a subject is the same as data's
    Node *root;
    int (*hashCalculation)(void*, DataType); // the primary parameter has payload
    OverlapArray *overlapArray;
    int (*referentMember)(void*, DataType); // Function pointer for getting member based on data type
    bool allowModification; // If true, allows modification of the array
} DynamicTree;

#endif