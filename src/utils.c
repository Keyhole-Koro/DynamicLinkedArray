#include "utils.h"

int undefined = -1;

void error(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

int dummy_member(void *data, DataType type) {
    (void)data; // Suppress unused parameter warning
    (void)type; // Suppress unused parameter warning
    return undefined;
}

bool isOutOfRange(DynamicArray *dArr, int index) {
    return index < 0 || index > getArrayOffset(dArr);
}

void copyPasteElements(DynamicArray *copiedArr, DynamicArray *pastedArr) {
	if (copiedArr->dataType != pastedArr->dataType) error("type mismatch: copyPasteElements\n");
	for (int i = 0; i < getArraySize(copiedArr); i++) {
		copyAndAddToDynamicArray(pastedArr, retriveData(copiedArr, i, copiedArr->dataType), pastedArr->dataType);
    }
}

bool isElementDataMatching(int (*referentMember)(void *, DataType),void *data1, void *data2, DataType type) {
    return referentMember(data1, type) == referentMember(data2, type);
}

bool isDataSizeMatching(DataUnion *data, int size) {
    return DATA_SIZE_MATCH(data, size);
}

bool isDataSizeSet(DataUnion *data) {
    return DATA_SIZE_MATCH(data, undefined);
}

bool setDataSize(DataUnion *data, void *payload) {
    return DATA_SIZE_MATCH(data, sizeof(*payload));
}

bool isDataTypeMatching(DataUnion *data, DataType expectedDataType) {
    return data->array.dataType == expectedDataType || data->tree.dataType == expectedDataType;
}

int getArraySize(DynamicArray *dArr) {
	return dArr->offset + 1;
}

int getArrayOffset(DynamicArray *dArr) {
	return dArr->offset;
}

bool *createBoolArray(int size) {
    bool *arr = (bool*)calloc(size, sizeof(bool));
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