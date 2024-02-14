#include "showElements.h"
#include <stdio.h>

void showConfig(DynamicArray *arr) {
    printf("DataType: %d\n", arr->dataType);
    printf("DataSize: %d\n", arr->dataSize);
    printf("Offset: %d\n", arr->offset);
    printf("Capacity: %d\n", arr->capacity);
    printf("Allow Overlapping: %s\n", arr->allowOverlapping ? "true" : "false");
    printf("OverlapArrayCapacity: %d\n", arr->overlapArrayCapacity);
    printf("Allow Modification: %s\n", ararraray->allowModification ? "true" : "false");

    printf("\n");
    // Displaying elementExistence array
    printf("ElementExistence Array:\n");
    for (int i = 0; i < array->capacity; ++i) {
        printf("%d ", array->elementExistence[i]);
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
