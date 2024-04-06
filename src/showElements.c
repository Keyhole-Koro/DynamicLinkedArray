#include "showElements.h"
#include <stdio.h>

void showDataType(DataType *dataType) {
    printf("dataType name: %s\n", dataType->name);
    printf("dataType size: %li\n", dataType->size);
}

void showConfigArray(DynamicArray *arr) {
    printf("-----Array-----\n");
    printf("Name: %s\n", arr->name);
    showDataType(arr->dataType);
    printf("Offset: %i\n", arr->offset);
    printf("Capacity: %i\n", arr->capacity);
    if (!arr->overlapArray) printf("OverlapArrayCapacity: %i\n", arr->overlapArray->capacity);
    printf("Allow Modification: %s\n", arr->allowModification ? "true" : "false");

    printf("\n");

    if (!arr->overlapArray) return;

    printf("ElementExistence Array:\n");
    for (int i = 0; i < arr->overlapArray->capacity; ++i) {
        printf("%2d ", i); // Print index with a width of 2 characters
    }
    printf("\n");

    for (int i = 0; i < arr->overlapArray->capacity; ++i) {
        printf("%2d ", arr->overlapArray->elementExistenceArray[i]);
    }

    printf("\n----------\n");
}

// You need to make another funciton for your own data
void showIntElements(DynamicArray *arr) {
    printf("All elements in the array:\n");
    for (int i = 0; i < getArrayOffset(arr); i++) {
        void *data = retrieveData(arr, i, arr->dataType);
        printf("%d\n", *(int *)data);
    }
}
