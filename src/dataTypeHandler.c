#include "dataTypeHandler.h"
#define MAX_DATA_TYPES 30

int numTypes = 0;

DataType *dataTypes[MAX_DATA_TYPES];

DataType *registerDataType(char *name, int size) {
    DataType *newDataType = malloc(sizeof(DataType));
    if (newDataType == NULL) error("allocation failed to register data type");
    newDataType->name = name;
    newDataType->size = size;
    if (numTypes >= MAX_DATA_TYPES) error("the maximum number of elements exceeds the number defaultly set\n if you wanna change the maximum, modigy MAX_DATATYPES in dataTypeHandler.c");

    dataTypes[numTypes++] = newDataType;
    
    return newDataType;
}

DataType *retriveDataType(char *expectedName) {
    for (int i = 0; i < numTypes; i++) {
        if (dataTypes[i]->name == expectedName) return dataTypes[i];
    }
    error("data type is not set");
    return NULL;
}