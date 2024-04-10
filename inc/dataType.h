#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <stdio.h>

/** @brief This had been in dataTypeHandle.h
    but to avoid a cross include
    struct DataType is separated from dataTypeHandler.h **/
typedef struct {
    char *name;
    size_t size;
} DataType;

#endif