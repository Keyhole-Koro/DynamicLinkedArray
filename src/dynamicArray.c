#include "./include/dynamicArray.h"

int undefined = -1;

int defaultReferentMember(void *data, DataType type) {
    return undefined;
}

DynamicArray *initializeDynamicArray(int initialCapacity, bool allowModification, int (*referentMember)(void *, DataType), DataType type) {
    DynamicArray *arr = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (arr == NULL) error("Memory allocation failed\n");
    arr->dataArray = (void **)malloc(sizeof(void *) * initialCapacity);
    initializeElementsInDynamicArray(arr, 0);
    if (arr->dataArray == NULL) error("Memory allocation failed\n");

    arr->dataType = type;
    arr->dataSize = undefined;
    arr->offset = undefined;
    arr->capacity = initialCapacity;
    arr->allowModification = allowModification;

    if (referentMember != &defaultReferentMember) {
        arr->allowOverlapping = false;
        arr->elementExistence = createBoolArray(initialCapacity);
        arr->overlappingCapacity = initialCapacity;
    } else {
        arr->allowOverlapping = true;
    }
    arr->referentMember = referentMember;

    return arr;
}

void addToDynamicArray(DynamicArray *arr, void *data, DataType type) {
    if (arr->allowModification == false) error("Modification not allowed: addToDynamicArray\n");
    if (type != arr->dataType) error("Type mismatch: addToDynamicArray\n");

    if (!isDataSizeSet(arr)) setDataSize(arr, data);
    if (!isDataSizeMatching(arr, sizeof(*data))) error("Type mismatch at addToDynamicArray()\n");
    if (isAlreadyExist(arr, arr->referentMember((void *)data, type))) return;

    reallocateDynamicArray(arr);

    arr->dataArray[++arr->offset] = data;
}

void copyAndAddToDynamicArray(DynamicArray *arr, void *data, DataType type) {
    if (arr->allowModification == false) error("Modification not allowed: copyAndAddToDynamicArray\n");
    if (type != arr->dataType) error("Type mismatch: copyAndAddToDynamicArray\n");

    int sizeData = sizeof(*data);

    if (!isDataSizeSet(arr)) setDataSize(arr, data);
    if (!isDataSizeMatching(arr, sizeData)) error("Type mismatch at copyAndAddToDynamicArray()\n");
    if (isAlreadyExist(arr, arr->referentMember((void *)data, type))) return;

    reallocateDynamicArray(arr);

    void *copy_data_ptr = malloc(sizeData);
    if (copy_data_ptr == NULL) error("Memory allocation failed\n");
    memcpy(copy_data_ptr, data, sizeData);
    arr->dataArray[++arr->offset] = copy_data_ptr;
}

void normalReallocateDynamicArray(DynamicArray *arr) {
	if (getArraySize(arr) == arr->capacity) {
		int previous_capacity_size = arr->capacity;
		arr->capacity *= 2;
		arr->dataArray = realloc(arr->dataArray, arr->capacity * sizeof(void *));
		initializeElementsInDynamicArray(arr, previous_capacity_size+1);
		if (arr->dataArray == NULL) error("Memory allocation failed\n");
	}
}

void initializeElementsInDynamicArray(DynamicArray *arr, int startIndex) {
    for (int i = startIndex; i < arr->capacity; i++) {
        arr->dataArray[i] = NULL;
    }
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

int getArraySize(DynamicArray *arr) {
	return arr->offset + 1;
}