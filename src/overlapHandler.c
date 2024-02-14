#include "./include/overlapHandler.h"

OverlapArray *createOverlapArray(int size) {
    OverlapArray *arr = (OverlapArray *)malloc(sizeof(OverlapArray));
    arr->capacity = size;
    arr->elementExistenceArray = createBoolArray(size);
}

bool ifElementExists(DynamicArray *arr, int index) {
    if (arr->allowOverlapping) return false;
	if (index < 0) error("index is under index");
    if (index > 100) printf("warn: index exceeds 100: index == %d\n", index);// in case the size is huge

    reallocOverlapArray(arr, index);

    if (arr->elementExistenceArray[index] == 1) return true;
    fillInIndexOfOverlapArray(arr, index);
    return false;
}

void reallocOverlapArray(OverlapArray *arr, int index) {
    int cur_capacity = arr->capacity;
    if (index > cur_capacity) {
        int new_capacity = index * 1.4 * sizeof(unsigned char);

        arr->elementExistenceArray = realloc(arr->elementExistenceArray, new_capacity);

        if (arr->elementExistenceArray == NULL) error("Memory allocation failed\n");
        
        arr->overlapArrayCapacity = new_capacity;

        for (int i = cur_capacity; i < new_capacity; i++) {
            arr->elementExistenceArray[i] = false;
        }
    }
}

void fillInIndexOfOverlapArray(DynamicArray *arr, int index) {
	arr->elementExistenceArray[index] = true;
}
