#include "referenceHandler.h"

int referenceInt(void *data, DataType *dataType) {
    if (strcmp(dataType->name, "int")) error("type mismatch");
    return *(int*)data;
}