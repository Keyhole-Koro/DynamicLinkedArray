#include "utils.h"

bool isOutOfRange(DynamicArray *arr, int index) {
    if (index < 0 || index > getArrayOffset(arr)) return true;
    return false;
}

void copyPasteElements(DynamicArray *copiedArr, DynamicArray *pastedArr) {
	if (copiedArr->DataType != pastedArr->typeDataType) error("type mismatch: copyPasteElements\n");
	for (int i = 0; i < getArraySize(copiedArr); i++) {
		appendCopy(pastedArr, retriveData(copiedArr, i, copiedArr->DataType), pastedArr->DataType);
    }
}

bool isElementDataMatching(int (*referentMember)(void *, DataType),void *data1, void *data2, DataType type) {
    if (referentMember(data1, type) == referentMember(data2, type)) return true;
    return false;
}

bool isDataSizeMatching(DynamicArray *arr, int size) {
    if (arr->dataSize == size) return true;
    return false;
}

bool isDataSizeSet(DynamicArray *arr) {
    if (arr->dataSize == undefined) return false;
    return true;
}

void setDataSize(DynamicArray *arr, void *data) {
    arr->dataSize = sizeof(*data);
}

bool ifDataTypeMatch(DynamicArray *arr, DataType expectedDataType) {
    if (arr->dataType == expectedDataType) return true;
    return false;
}

int getArraySize(DynamicArray *arr) {
	return arr->offset + 1;
}

bool *createBoolArray(int size) {
    bool *arr = (unsigned char *)calloc(size, sizeof(bool));
    initializeBoolArray(arr, size);
    return arr;
}

void initializeBoolArray(bool *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = false;
    }
}

void destoryBoolArray(bool *arr) {
    free(arr);
}