#ifndef OVERLAP_HANDLER_H
#define OVERLAP_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "overlap.h"

#include "utils.h"

OverlapArray *createOverlapArray(int size);

bool ifElementExists(OverlapArray *olArr, int index);

void destroyOverlapArray(OverlapArray *olArr);

#endif