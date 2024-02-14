#include "./include/overlapHandler.h"

bool ifElementExists(DynamicArray *arr, int index) {
    if (arr->allowOverlapping) return false;
	if (index < 0) error("index is under index");
    if (index > 100) printf("warn: index exceeds 100: index == %d\n", index);// in case the size is huge

    reallocOverlapArray(arr, index);

    if (arr->elementExistence[index] == 1) return true;
    fillInIndexOfOverlapArray(arr, index);
    return false;
}

void reallocOverlapArray(DynamicArray *arr, int index) {
    int previous_capacity_size = arr->overlapArrayCapacity;
    if (index > arr->overlapArrayCapacity) {
        int new_capacity = index * 1.4 * sizeof(unsigned char);

        arr->elementExistence = realloc(arr->elementExistence, new_capacity);

        if (arr->elementExistence == NULL) error("Memory allocation failed\n");
        arr->overlapArrayCapacity = new_capacity;
        //intialize
        for (int i = previous_capacity_size; i < new_capacity; i++) {
            arr->elementExistence[i] = 0;
        }
    }
}

void fillInIndexOfOverlapArray(DynamicArray *arr, int index) {
	arr->elementExistence[index] = false;
}
