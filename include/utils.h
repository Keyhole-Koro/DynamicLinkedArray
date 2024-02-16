#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#include "dynamicArray.h"
#include "dynamicTree.h"

#define HASH_LESS_THAN_OR_EQUAL(root, Node) ((root)->hash <= (Node)->hash)

#define DATA_SIZE_MATCH(data, size) (data)->array.dataSize == (size) || (data)->tree.dataSize == (size)

extern int undefined;

typedef union {
    DynamicArray array;
    DynamicTree tree;
} DataUnion;

void error(char *message);

int dummy_member(void*, DataType*);

bool isOutOfRange(DynamicArray*, int);

void copyPasteElements(DynamicArray*, DynamicArray*);

bool isElementDataMatching(int (*referentMember)(void*, DataType*), void*, void*, DataType*);
bool isDataTypeMatching(DataType*, DataType*);
int getArrayOffset(DynamicArray*);

bool *createBoolArray(int);
void initializeBoolArray(bool*, int);
void destoryBoolArray(bool*);

#endif