#include "elementHandler.h"

void swapElement(DynamicArray *dArr, int pos1, int pos2, DataType type) {
	if (dArr->allowModification == false) error("not allowed to be modified: swapElement\n");
	if (ifDataTypeMatch(dArr, type)) error("type mismatch: swapElement\n");

	if (isOutOfRange(dArr, pos1) || isOutOfRange(dArr, pos2)) error("Index out of bounds: swapElement\n");

	void **data = dArr->dataArray;

	void *temp_element = data[pos1];
	data[pos1] = data[pos2];
	data[pos2] = temp_element;
}

void swapWithLastElement(DynamicArray *dArr, int index, DataType type) {
	swapElement(dArr, index, getArrayOffset(dArr), type);
}

void removeElement(DynamicArray *dArr, int index, DataType type) {
	if (dArr->allowModification == false) error("not allowed to be modified: removeElement\n");
	if (!ifDataTypeMatch(dArr, type)) error("Type mismatch: swapRemoveElement\n");
	if (getArraySize(dArr) < 2) return;
	swapWithLastElement(dArr, index, type);
	removeLastElement(dArr);
}

void *extractCertainData(DynamicArray *dArr, bool (customReferentMember)(void*, void* ,DataType), void *expected_data, DataType type) {
    for (int i = 0; i < getArraySize(dArr); i++) {
        void *data = retriveData(dArr, i, type);
        if (isElementDataMatching(dArr->referentMember, data, expected_data, type)) return data;
    }
    return NULL;
}

void prioritize(DynamicArray *dArr, int pos, DataType type) {
	if (pos == 0) return;
	swapElement(dArr, pos, pos-1, type);
}

void deprioritize(DynamicArray *dArr, int pos, DataType type) {
	if (pos == getArrayOffset(dArr)) return;
	swapElement(dArr, pos, pos+1, type);
}

void allowModify(DynamicArray *dArr) {
	dArr->allowModification = true;
}

void disableModify(DynamicArray *dArr) {
	dArr->allowModification = false;
}