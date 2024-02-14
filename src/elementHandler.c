#include "./include/elementHandler.h"

void removeElement(DynamicArray *arr, int index, DataType type) {
	if (arr->allowModification == false) error("not allowed to be modified: removeElement\n");
	if (!ifDataTypeMatch(arr, type)) error("Type mismatch: swapRemoveElement\n");
	if (getArraySize(arr) < 2) return;
	swapWithLastElement(arr, index, type);
	removeLastElement(arr);
}
