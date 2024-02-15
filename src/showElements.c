#include "showElements.h"
#include <stdio.h>

void showDataType(DataType *dataType) {
    printf("dataType name %s", dataType->name);
    printf("dataType size %li", dataType->size);
}

void showConfigArray(DynamicArray *arr) {
    showDataType(arr->dataType);
    printf("Offset: %i\n", arr->offset);
    printf("Capacity: %i\n", arr->capacity);
    if (!arr->overlapArray) printf("OverlapArrayCapacity: %i\n", arr->overlapArray->capacity);
    printf("Allow Modification: %s\n", arr->allowModification ? "true" : "false");

    printf("\n");

    if (!arr->overlapArray) return;

    // Displaying elementExistence array
    printf("ElementExistence Array:\n");
    for (int i = 0; i < arr->overlapArray->capacity; ++i) {
        printf("%d ", arr->overlapArray->elementExistenceArray[i]);
    }
    printf("\n");
}

// You need to make another funciton for your own data
void showIntElements(DynamicArray *arr) {
    printf("All elements in the array:\n");
    for (int i = 0; i < getArraySize(arr); i++) {
        void *data = retriveData(arr, i, arr->dataType);
        // Assuming each element is an integer, you can adjust accordingly for other types
        printf("%d\n", *(int *)data);
    }
}
