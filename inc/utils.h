#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdbool.h>

#include "dataType.h"
#include "dynamicArray.h"
#include "dynamicTree.h"

#define nullptr ((void *)0)

#define HASH_LESS_THAN_OR_EQUAL(root, Node) ((root)->hash <= (Node)->hash)

#define DATA_SIZE_MATCH(data, size) (data)->array.dataSize == (size) || (data)->tree.dataSize == (size)

extern int undefined;

void error(char *message);

int dummy_member(void*, DataType*);

bool isElementDataMatching(int (*referentMember)(void*, DataType*), void*, void*, DataType*);
bool isDataTypeMatching(DataType*, DataType*);

bool *createBoolArray(int);
void initializeBoolArray(bool*, int);
void destoryBoolArray(bool*);

#endif