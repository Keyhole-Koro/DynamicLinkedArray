#include "utils.h"

int dummy_member(void *data, DataType type) {
    return undefined;
}

bool isOutOfRange(DynamicArray *dArr, int index) {
    if (index < 0 || index > getArrayOffset(dArr)) return true;
    return false;
}

void copyPasteElements(DynamicArray *copiedArr, DynamicArray *pastedArr) {
	if (copiedArr->dataType != pastedArr->dataType) error("type mismatch: copyPasteElements\n");
	for (int i = 0; i < getArraySize(copiedArr); i++) {
		appendCopy(pastedArr, retriveData(copiedArr, i, copiedArr->dataType), pastedArr->dataType);
    }
}

bool isElementDataMatching(int (*referentMember)(void *, DataType),void *data1, void *data2, DataType type) {
    if (referentMember(data1, type) == referentMember(data2, type)) return true;
    return false;
}

bool isDataSizeMatching(DynamicArray *dArr, int size) {
    if (dArr->dataSize == size) return true;
    return false;
}

bool isDataSizeSet(DynamicArray *dArr) {
    if (dArr->dataSize == undefined) return false;
    return true;
}

void setDataSize(DynamicArray *dArr, void *data) {
    dArr->dataSize = sizeof(*data);
}

bool ifDataTypeMatch(DynamicArray *dArr, DataType expectedDataType) {
    if (dArr->dataType == expectedDataType) return true;
    return false;
}

int getArraySize(DynamicArray *dArr) {
	return dArr->offset + 1;
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

void destoryBoolArray(bool *dArr) {
    free(dArr);
}