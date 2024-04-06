#ifndef OVERLAP_HANDLER
#define OVERLAP_HANDLER

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "dataTypeHandler.h"
#include "utils.h"

OverlapArray *createOverlapArray(int size);

bool ifElementExists(OverlapArray *olArr, int index);

void destroyOverlapArray(OverlapArray *olArr);

#endif