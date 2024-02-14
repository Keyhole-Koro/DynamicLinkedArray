#include "showElements.h"
#include <stdio.h>

void showConfigArray(DynamicArray *arr) {
    printf("DataType: %d\n", arr->dataType);
    printf("DataSize: %d\n", arr->dataSize);
    printf("Offset: %d\n", arr->offset);
    printf("Capacity: %d\n", arr->capacity);
    if (!arr->overlapArray) ("OverlapArrayCapacity: %d\n", arr->overlapArray->capacity);
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
        void *data = retrieveData(arr, i, arr->dataType);
        // Assuming each element is an integer, you can adjust accordingly for other types
        printf("%d\n", *(int *)data);
    }
}
