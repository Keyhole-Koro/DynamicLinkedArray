#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#include "dynamicArray.h"

int undefined = -1;

int dummy_member(void *data, DataType type);

bool isOutOfRange(DynamicArray *arr, int index);

void copyPasteElements(DynamicArray *copiedArr, DynamicArray *pastedArr);

bool isElementDataMatching(int (*referentMember)(void *, DataType),void *data1, void *data2, DataType type);
bool isDataSizeMatching(DynamicArray *arr, int size);
bool isDataSizeSet(DynamicArray *arr);
void setDataSize(DynamicArray *arr, void *data);
bool ifDataTypeMatch(DynamicArray *arr, DataType expectedDataType);
int getArraySize(DynamicArray *arr);

bool *createBoolArray(int size);
void initializeBoolArray(bool *arr, int size);
void destoryBoolArray(bool *arr);

#endif