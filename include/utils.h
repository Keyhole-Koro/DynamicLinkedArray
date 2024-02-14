#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#include "dynamicArray.h"
#include "dynamicTree.h"

#define DATA_SIZE_MATCH(data, size) (data)->array.dataSize == (size) || (data)->tree.dataSize == (size)

int undefined = -1;

typedef union {
    DynamicArray array;
    DynamicTree tree;
} DataUnion;

int dummy_member(void*, DataType);

bool isOutOfRange(DynamicArray*, int);

void copyPasteElements(DynamicArray*, DynamicArray*);

bool isElementDataMatching(int (*referentMember)(void*, DataType), void*, void*, DataType);
bool isDataSizeMatching(DynamicArray*, int);
bool isDataSizeSet(DynamicArray*);
void setDataSize(DynamicArray*, void*);
bool ifDataTypeMatch(DynamicArray*, DataType);
int getArraySize(DynamicArray*);

bool *createBoolArray(int);
void initializeBoolArray(bool*, int);
void destoryBoolArray(bool*);

#endif