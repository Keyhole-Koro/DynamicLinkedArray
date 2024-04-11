#ifndef DYNAMIC_ARRAY_HANDLER_H
#define DYNAMIC_ARRAY_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dynamicArray.h"

#include "dataType.h"
#include "utils.h"
#include "overlapHandler.h"

/**
 * 
 * @param arrayName       Name of the dynamic array (for debugging purposes).
 * @param initialCapacity Initial capacity of the array. If elements exceed this capacity, the array will be reallocated with double the initial capacity.
 * @param ifAllowModification If true, adding and swapping operations are enabled; otherwise, they are disabled.
 * @param ifAllowOverlapping If false, checks for common elements when adding a new element; otherwise, overlapping is allowed.
 * @param referentMember   Pointer to a function used for finding and comparing elements. This function must have the signature `(*)(void*, DataType*)`.
 * @param dataType         The data type of the elements in the array. Use `registerDataType(char *name, int size)` (defined in dataTypeHandler.h) to register the data type.
 * 
 * @return A pointer to the initialized dynamic array.
**/
DynamicArray *createDynamicArray(char *arrayName, int initialCapacity, bool ifAllowModification, bool ifAllowOverlapping, int (*referentMember)(void*, DataType*), DataType *dataType);

void addToDynamicArray(DynamicArray*, void*, DataType*);

void copyAndAddToDynamicArray(DynamicArray*, void*, DataType*);

int getArrayOffset(DynamicArray*);

void *retrieveData(DynamicArray*, int, DataType*);

void *fetchMatchingData(DynamicArray*, void*, DataType*);

void reallocateDynamicArray(DynamicArray*);

bool isOutOfRange(DynamicArray*, int);

void copyPasteElements(DynamicArray*, DynamicArray*);

void initializeElementsInDynamicArray(DynamicArray*, int);

DynamicArray *cloneArray(DynamicArray*);

void destroyDynamicArray(DynamicArray*);

#endif
