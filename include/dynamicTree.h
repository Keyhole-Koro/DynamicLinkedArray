#ifndef DYNAMIC_TREE
#define DYNAMIC_TREE

#include "stdbool.h"

#include "dataTypeHandler.h"
#include "overlapHandler.h"
#include "utils.h"

#define HASH_LESS_THAN_OR_EQUAL(root, Node) ((root)->hash <= (Node)->hash)

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