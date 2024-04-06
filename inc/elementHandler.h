#ifndef ELEMENT_OPERATIONS
#define ELEMENT_OPERATIONS

#include "dynamicArray.h"
#include "utils.h"

void swapWithLastElement(DynamicArray *dArr, int index, DataType *dataType);

inline void prioritize(DynamicArray *dArr, int pos, DataType *dataType);
inline void deprioritize(DynamicArray *dArr, int pos, DataType *dataType);

inline void allowModify(DynamicArray *dArr);
inline void disableModify(DynamicArray *dArr);

#endif