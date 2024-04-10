#ifndef SORT_ELEMENT_H
#define SORT_ELEMENT_H

#include "dynamicArray.h"
#include "dataType.h"
#include "elementHandler.h"
#include "utils.h"

int qsortPartition(DynamicArray *arr, int (referentFunc)(void*, DataType*), int low, int high, DataType *type);

void quickSort(DynamicArray *arr, int (referentFunc)(void*, DataType*), int low, int high, DataType *type);

#endif