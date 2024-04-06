#include "sortElement.h"

int qsortPartition(DynamicArray *arr, int (referentFunc)(void*, DataType*), int low, int high, DataType *type) {
	if (type != arr->dataType) error("type mismatch: qsortPartition\n");
	void *high_prod = retrieveData(arr, high, type);
	int pivot = referentFunc(high_prod, type);
	void *j_prod;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		j_prod = retrieveData(arr, j, type);
		if (referentFunc(j_prod, type) < pivot) {
			i++;
			swapElement(arr, i, j, type);
		}
	}
	swapElement(arr, i + 1, high, type);
	return (i + 1);
}

//sort productions according the number of symbols
void quickSort(DynamicArray *arr, int (referentFunc)(void*, DataType*), int low, int high, DataType *type) {
	if (type != arr->dataType) error("type mismatch: quickSort\n");
	if (low < high) {
		int pi = qsortPartition(arr, referentFunc, low, high, type);

		quickSort(arr, referentFunc, low, pi - 1, type);
		quickSort(arr, referentFunc, pi + 1, high, type);
	}
}