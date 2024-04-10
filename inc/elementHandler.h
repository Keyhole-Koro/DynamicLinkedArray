#ifndef ELEMENT_OPERATIONS
#define ELEMENT_OPERATIONS

#include "dynamicArrayHandler.h"
#include "utils.h"

void swapElement(DynamicArray *dArr, int pos1, int pos2, DataType *dataType);
void swapWithLastElement(DynamicArray *dArr, int index, DataType *dataType);

inline void prioritize(DynamicArray *dArr, int pos, DataType *dataType);
inline void deprioritize(DynamicArray *dArr, int pos, DataType *dataType);

inline void allowModify(DynamicArray *dArr);
inline void disableModify(DynamicArray *dArr);

#endif