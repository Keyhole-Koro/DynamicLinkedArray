#ifndef HASH_H
#define HASH_H

#include "dataType.h"
#include "dynamicArrayHandler.h"

int calculateHash(DynamicArray *arr, int (referentElement)(void*, DataType*), DataType*);

#endif