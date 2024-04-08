#ifndef HASH_H
#define HASH_H

#include "dataTypeHandler.h"
#include "dynamicArray.h"

int calculateHash(DynamicArray *arr, int (referentElement)(void*, DataType*), DataType*);

#endif