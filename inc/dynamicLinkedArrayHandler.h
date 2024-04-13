#ifndef DYNAMIC_LINKE_ARRAY_HANDLER_H
#define DYNAMIC_LINKE_ARRAY_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dynamicLinkedArray.h"

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

DynamicLinkedArray *createDynamicLinkedArray(char *arrayName, int initialCapacity, bool ifAllowModification,bool ifAllowOverlapping, int (*referentMember)(void*, DataType*), DataType *dataType);
bool validateDynamicLinkedArrayAddition(DynamicLinkedArray *dArr, void *data, DataType *dataType);
void addToDynamicLinkedArray(DynamicLinkedArray *dArr, void *data, DataType *dataType);
void *retrieveLinkedArrayData(DynamicLinkedArray *dArr, int pos, DataType *dataType);
void *fetchNode(ArrayNode *node, int num);
void *fetchLatestArray(DynamicLinkedArray *dArr);
void *fetchLatestArray_(ArrayNode *node);
void newArray(DynamicLinkedArray *dArr);
void *makeArray(DynamicLinkedArray *dArr);
void *makeArrayNode(ArrayNode *previousNode, void *array);
void initializeElements(void *arr, int size);
void setArrayLength(DynamicLinkedArray *dArr, DataType *dataType);
int arraySize(DynamicLinkedArray *dArr);

int quotient(int operand, int operator);
int remainder_int(int operand, int operator);

#endif