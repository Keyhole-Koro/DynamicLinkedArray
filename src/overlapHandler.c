#include "overlapHandler.h"

void reallocOverlapArray(OverlapArray *olArr, int index);
void fillInIndexOfOverlapArray(OverlapArray *olArr, int index);

OverlapArray *createOverlapArray(int size) {
    OverlapArray *arr = (OverlapArray *)malloc(sizeof(OverlapArray));
    arr->capacity = size;
    arr->elementExistenceArray = createBoolArray(size);
    return arr;
}

bool ifElementExists(OverlapArray *olArr, int index) {
    if (!olArr) return false;
	if (index < 0) error("index is less than 0");
    if (index > 100) printf("warn: index exceeds 100: index == %d\n", index);// in case the size is huge

    reallocOverlapArray(olArr, index);

    if (olArr->elementExistenceArray[index]) return true;
    fillInIndexOfOverlapArray(olArr, index);
    return false;
}

void reallocOverlapArray(OverlapArray *olArr, int index) {
    int cur_capacity = olArr->capacity;
    if (index > cur_capacity) {
        int new_capacity = index * 1.4 * sizeof(unsigned char);

        olArr->elementExistenceArray = realloc(olArr->elementExistenceArray, new_capacity);

        if (!olArr->elementExistenceArray) error("Memory allocation failed\n");
        
        olArr->capacity = new_capacity;

        for (int i = cur_capacity; i < new_capacity; i++) {
            olArr->elementExistenceArray[i] = false;
        }
    }
}

void fillInIndexOfOverlapArray(OverlapArray *olArr, int index) {
	olArr->elementExistenceArray[index] = true;
}

void destroyOverlapArray(OverlapArray *olArr) {
    if (olArr != NULL) {
        free(olArr->elementExistenceArray);
        free(olArr);
    }
}
