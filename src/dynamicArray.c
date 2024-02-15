#include "dynamicArray.h"

DynamicArray *createDynamicArray(int initialCapacity, bool allowModification, int (*referentMember)(void*, DataType*), DataType *dataType) {
    DynamicArray *dArr = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (dArr == NULL) error("Memory allocation failed\n");
    dArr->dataArray = (void **)malloc(sizeof(void *) * initialCapacity);
    initializeElementsInDynamicArray(dArr, 0);
    if (dArr->dataArray == NULL) error("Memory allocation failed\n");

    dArr->dataType = dataType;
    dArr->offset = undefined;
    dArr->capacity = initialCapacity;
    dArr->allowModification = allowModification;

    dArr->overlapArray = (referentMember != &dummy_member) ? createOverlapArray(initialCapacity) : NULL;    

    dArr->referentMember = referentMember;

    return dArr;
}

void addToDynamicArray(DynamicArray *dArr, void *data, DataType *dataType) {
    if (dArr->allowModification == false) error("Modification not allowed: addToDynamicArray\n");
    if (!isDataTypeMatching(dArr->dataType, dataType)) error("Type mismatches: addToDynamicArray\n");

    if (ifElementExists(dArr->overlapArray, dArr->referentMember(data, dataType))) return;

    reallocateDynamicArray(dArr);

    dArr->dataArray[++dArr->offset] = data;
}

void copyAndAddToDynamicArray(DynamicArray *dArr, void *data, DataType *dataType) {
    if (dArr->allowModification == false) error("Modification not allowed: copyAndAddToDynamicArray\n");
    if (!isDataTypeMatching(dArr->dataType, dataType)) error("Type mismatches: copyAndAddToDynamicArray\n");

    int sizeData = dataType->size;

    if (ifElementExists(dArr->overlapArray, dArr->referentMember(data, dataType))) return;

    reallocateDynamicArray(dArr);

    void *copy_data_ptr = malloc(sizeData);
    if (copy_data_ptr == NULL) error("Memory allocation failed\n");
    memcpy(copy_data_ptr, data, sizeData);
    dArr->dataArray[++dArr->offset] = copy_data_ptr;
}

void *retriveData(DynamicArray *dArr, int pos, DataType *dataType) {
	if (!isDataTypeMatching(dArr->dataType, dataType)) error("type mismatch: retriveData\n");

	if (isOutOfRange(dArr, pos)) error("Index out of bounds: retriveData\n");

	return dArr->dataArray[pos];
}

void *fetchMatchingData(DynamicArray *dArr, void *expectedData, DataType *dataType) {        
    for (int i = 0; getArraySize(dArr); i++) {
        void *data = (void *)retriveData(dArr, i, dataType);
        if (isElementDataMatching(dArr->referentMember, data, expectedData, dataType)) return data;
    }
    
    return NULL;
}

void reallocateDynamicArray(DynamicArray *dArr) {
	if (getArraySize(dArr) == dArr->capacity) {
		int previous_capacity_size = dArr->capacity;
		dArr->capacity *= 2;
		dArr->dataArray = realloc(dArr->dataArray, dArr->capacity * sizeof(void *));
		initializeElementsInDynamicArray(dArr, previous_capacity_size+1);
		if (dArr->dataArray == NULL) error("Memory allocation failed\n");
	}
}

void initializeElementsInDynamicArray(DynamicArray *dArr, int startIndex) {
    for (int i = startIndex; i < dArr->capacity; i++) {
        dArr->dataArray[i] = NULL;
    }
}

DynamicArray *cloneArray(DynamicArray *originaldArr) {
	DataType *dataType = originaldArr->dataType;
	DynamicArray *clonedArray = createDynamicArray(getArraySize(originaldArr), originaldArr->allowModification, originaldArr->referentMember, dataType);

	for (int i = 0; i < getArraySize(originaldArr); i++) {
        void *data = retriveData(originaldArr, i, dataType);
		copyAndAddToDynamicArray(clonedArray, data, dataType);
	}

	return clonedArray;
}

void destroyDynamicArray(DynamicArray* dArr) {
    for (int i = 0; i < getArraySize(dArr); i++) free(dArr->dataArray[i]);
	free(dArr->dataArray);
	free(dArr);
}
