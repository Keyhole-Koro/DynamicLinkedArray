#include "./include/overlapHandler.h"

OverlapArray *createOverlapArray(int size) {
    OverlapArray *arr = (OverlapArray *)malloc(sizeof(OverlapArray));
    arr->capacity = size;
    arr->elementExistenceArray = createBoolArray(size);
}

bool ifElementExists(OverlapArray *olArr, int index) {
    if (!olArr) return false;
	if (index < 0) error("index is under index");
    if (index > 100) printf("warn: index exceeds 100: index == %d\n", index);// in case the size is huge

    reallocOverlapArray(olArr, index);

    if (olArr->elementExistenceArray[index] == 1) return true;
    fillInIndexOfOverlapArray(olArr, index);
    return false;
}

void reallocOverlapArray(OverlapArray *olArr, int index) {
    int cur_capacity = olArr->capacity;
    if (index > cur_capacity) {
        int new_capacity = index * 1.4 * sizeof(unsigned char);

        olArr->elementExistenceArray = realloc(olArr->elementExistenceArray, new_capacity);

        if (olArr->elementExistenceArray == NULL) error("Memory allocation failed\n");
        
        olArr->capacity = new_capacity;

        for (int i = cur_capacity; i < new_capacity; i++) {
            olArr->elementExistenceArray[i] = false;
        }
    }
}

void fillInIndexOfOverlapArray(OverlapArray *olArr, int index) {
	olArr->elementExistenceArray[index] = true;
}
