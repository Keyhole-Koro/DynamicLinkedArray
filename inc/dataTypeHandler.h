#ifndef DATA_TYPE_HANDLER_H
#define DATA_TYPE_HANDLER_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dataType.h"
#include "utils.h"

typedef int type;

extern DataType *dataTypes[];

DataType *registerDataType(char*, int);
DataType *retrieveDataType(char *expectedName);

#endif