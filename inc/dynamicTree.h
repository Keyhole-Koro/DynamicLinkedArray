#ifndef DYNAMIC_TREE_H
#define DYNAMIC_TREE_H

#include <stdbool.h>

#include "dataType.h"
#include "overlap.h"

typedef struct {
    int hash;
    void *left;
    void *right;
    void *data;
} Node;

typedef struct {
    char *name;
    DataType *dataType;
    Node *root;
    int (*hashCalculation)(void*); // the primary parameter has data
    OverlapArray *overlapArray;
    int (*referentMember)(void*, DataType*); // Function pointer for getting member based on data type
    bool allowOverlapping;
    bool allowModification; // If true, allows modification of the array
} DynamicTree;

#endif