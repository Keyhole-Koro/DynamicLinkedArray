#include "elementHandler.h"

void swapElement(DynamicArray *dArr, int pos1, int pos2, DataType *dataType) {
	if (dArr->allowModification == false) error("not allowed to be modified: swapElement\n");
	if (isDataTypeMatching(dArr->dataType, dataType)) error("type mismatch: swapElement\n");

	if (isOutOfRange(dArr, pos1) || isOutOfRange(dArr, pos2)) error("Index out of bounds: swapElement\n");

	void **data = dArr->dataArray;

	void *temp_element = data[pos1];
	data[pos1] = data[pos2];
	data[pos2] = temp_element;
}

void swapWithLastElement(DynamicArray *dArr, int index, DataType *dataType) {
	swapElement(dArr, index, getArrayOffset(dArr), dataType);
}

void removeLastElement(DynamicArray *arr) {
	if (arr->allowModification == false) error("not allowed to be modified: removeLastElement\n");
	free(arr->dataArray[getArrayOffset(arr)]);
	arr->offset--;
}

void removeElement(DynamicArray *dArr, int index, DataType *dataType) {
	if (dArr->allowModification == false) error("not allowed to be modified: removeElement\n");
	if (!isDataTypeMatching(dArr->dataType, dataType)) error("Type mismatch: swapRemoveElement\n");
	if (getArrayOffset(dArr) < 2) return;
	swapWithLastElement(dArr, index, dataType);
	removeLastElement(dArr);
}

void *extractCertainData(DynamicArray *dArr, bool (customReferentMember)(void*, void* ,DataType*), void *expected_data, DataType *dataType) {
    for (int i = 0; i < getArrayOffset(dArr); i++) {
        void *data = retrieveData(dArr, i, dataType);
        if (customReferentMember(data, expected_data, dataType)) return data;
    }
    return NULL;
}

void prioritize(DynamicArray *dArr, int pos, DataType *dataType) {
	if (pos == 0) return;
	swapElement(dArr, pos, pos-1, dataType);
}

void deprioritize(DynamicArray *dArr, int pos, DataType *dataType) {
	if (pos == getArrayOffset(dArr)) return;
	swapElement(dArr, pos, pos+1, dataType);
}

void allowModify(DynamicArray *dArr) {
	dArr->allowModification = true;
}

void disableModify(DynamicArray *dArr) {
	dArr->allowModification = false;
}