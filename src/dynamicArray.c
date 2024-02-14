#include "./include/dynamicArray.h"

int dummy_member(void *data, DataType type) {
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

    if (referentMember != &dummy_member) {
        arr->allowOverlapping = false;
        arr->elementExistence = createBoolArray(initialCapacity);
        arr->overlapArrayCapacity = initialCapacity;
    } else {
        arr->allowOverlapping = true;
    }
    arr->referentMember = referentMember;

    return arr;
}

void addToDynamicArray(DynamicArray *arr, void *data, DataType type) {
    if (arr->allowModification == false) error("Modification not allowed: addToDynamicArray\n");
    if (!ifDataTypeMatch(arr, type)) error("Type mismatch: addToDynamicArray\n");

    if (!isDataSizeSet(arr)) setDataSize(arr, data);
    if (!isDataSizeMatching(arr, sizeof(*data))) error("Type mismatch at addToDynamicArray()\n");
    if (isAlreadyExist(arr, arr->referentMember((void *)data, type))) return;

    reallocateDynamicArray(arr);

    arr->dataArray[++arr->offset] = data;
}

void copyAndAddToDynamicArray(DynamicArray *arr, void *data, DataType type) {
    if (arr->allowModification == false) error("Modification not allowed: copyAndAddToDynamicArray\n");
    if (!ifDataTypeMatch(arr, type)) error("Type mismatch: copyAndAddToDynamicArray\n");

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

void *retriveData(DynamicArray *arr, int pos, DataType type) {
	if (!ifDataTypeMatch(arr, type)) error("type mismatch: retriveData\n");

	if (pos < 0 || pos > getArrayOffset(arr)) error("Index out of bounds: retriveData\n");

	return arr->dataArray[pos];
}

void *fetchMatchingData(DynamicArray *arr, void *expectedData, DataType type) {
    if (getArraySize(arr) == 0) return NULL;
        
    //may replace here to extractCertainData()
    for (int i = 0; getArraySize(arr); i++) {
        void *data = (void *)retriveData(arr, i, type);
        if (isElementDataMatching(arr->referentMember, data, expectedData, type)) return retriveData(arr, fetchPosMatchingData(arr, expectedData, type), type);;
    }
    
    return NULL;
}

void reallocateDynamicArray(DynamicArray *arr) {
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

void destroyDynamicArray(DynamicArray* arr) {
    for (int i = 0; i < getArraySize(arr); i++) free(arr->dataArray[i]);
	free(arr->dataArray);
	free(arr);
}
