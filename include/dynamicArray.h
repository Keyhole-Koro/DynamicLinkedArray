#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dataTypeHandler.h"
#include "overlapHandler.h"
#include "utils.h"

DynamicArray *createDynamicArray(int, bool, int (*referentMember)(void*, DataType), DataType);

void addToDynamicArray(DynamicArray*, void*, DataType);

void copyAndAddToDynamicArray(DynamicArray*, void*, DataType);

void *retriveData(DynamicArray*, int, DataType);

void *fetchMatchingData(DynamicArray*, void*, DataType);

void reallocateDynamicArray(DynamicArray*);

void initializeElementsInDynamicArray(DynamicArray*, int);

DynamicArray *cloneArray(DynamicArray*);

void destroyDynamicArray(DynamicArray*);

#endif
