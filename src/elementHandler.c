#include "./include/elementHandler.h"

void swapElement(DynamicArray *arr, int pos1, int pos2, DataType type) {
	if (arr->allowModification == false) error("not allowed to be modified: swapElement\n");
	if (ifDataTypeMatch(arr, type)) error("type mismatch: swapElement\n");

	if (isOutOfRange(arr, pos) || isOutOfRange(arr, pos)) error("Index out of bounds: swapElement\n");

	void **data = arr->dataArray;

	void *temp_element = data[pos1];
	data[pos1] = data[pos2];
	data[pos2] = temp_element;
}

void swapWithLastElement(DynamicArray *arr, int index, DataType type) {
	swapElement(arr, index, getArrayOffset(arr), type);
}

void removeElement(DynamicArray *arr, int index, DataType type) {
	if (arr->allowModification == false) error("not allowed to be modified: removeElement\n");
	if (!ifDataTypeMatch(arr, type)) error("Type mismatch: swapRemoveElement\n");
	if (getArraySize(arr) < 2) return;
	swapWithLastElement(arr, index, type);
	removeLastElement(arr);
}

void *extractCertainData(DynamicArray *arr, bool (customReferentMember)(void*, void* ,DataType), void *expected_data, DataType type) {
    for (int i = 0; i < getArraySize(arr); i++) {
        Data *data = retriveData(arr, i, type);
        if (isElementDataMatching(data, expected_data, type)) return data;
    }
    return NULL;
}

void prioritize(DynamicArray *arr, int pos, DataType type) {
	if (pos == 0) return;
	swapElement(arr, pos, pos-1, type);
}

void deprioritize(DynamicArray *arr, int pos, DataType type) {
	if (pos == getArrayOffset(arr)) return;
	swapElement(arr, pos, pos+1, type);
}

void allowModify(DynamicArray *arr) {
	arr->allowModification = true;
}

void disableModify(DynamicArray *arr) {
	arr->allowModification = false;
}