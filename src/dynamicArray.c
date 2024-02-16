#include "dynamicArray.h"

DynamicArray *createDynamicArray(char *arrayName, int initialCapacity, bool ifAllowModification, bool ifAllowOverlapping, int (*referentMember)(void*, DataType*), DataType *dataType) {
    DynamicArray *dArr = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (dArr == NULL) error("Memory allocation failed\n");
    dArr->dataArray = (void **)malloc(sizeof(void *) * initialCapacity);
    initializeElementsInDynamicArray(dArr, 0);
    if (dArr->dataArray == NULL) error("Memory allocation failed\n");
    
    dArr->name = arrayName;
    dArr->dataType = dataType;
    dArr->offset = 0;
    dArr->capacity = initialCapacity;
    dArr->allowModification = ifAllowModification;
    dArr->allowOverlapping = ifAllowOverlapping;

    dArr->overlapArray = (referentMember != &dummy_member) ? createOverlapArray(initialCapacity) : NULL;    

    dArr->referentMember = referentMember;

    return dArr;
}

bool validateDynamicArrayAddition(DynamicArray *dArr, void *data, DataType *dataType) {
    if (dArr->allowModification == false) error("Modification not allowed: (copyAnd)addToDynamicArray\n");
    if (!isDataTypeMatching(dArr->dataType, dataType)) error("Type mismatches: (copyAnd)addToDynamicArray\n");

    if (!dArr->allowOverlapping && ifElementExists(dArr->overlapArray, dArr->referentMember(data, dataType))) return false;
    return true;
}

void addToDynamicArray(DynamicArray *dArr, void *data, DataType *dataType) {
    if (!validateDynamicArrayAddition(dArr, data, dataType)) return;

    reallocateDynamicArray(dArr);
    dArr->dataArray[dArr->offset++] = data;
}

void copyAndAddToDynamicArray(DynamicArray *dArr, void *data, DataType *dataType) {
    if (!validateDynamicArrayAddition(dArr, data, dataType)) return;
    
    int sizeData = dataType->size;

    reallocateDynamicArray(dArr);

    void *copy_data_ptr = malloc(sizeData);
    if (copy_data_ptr == NULL) error("Memory allocation failed\n");
    memcpy(copy_data_ptr, data, sizeData);
    dArr->dataArray[dArr->offset++] = copy_data_ptr;
}

void *retrieveData(DynamicArray *dArr, int pos, DataType *dataType) {
	if (!isDataTypeMatching(dArr->dataType, dataType)) error("type mismatch: retrieveData\n");

	if (isOutOfRange(dArr, pos)) error("Index out of bounds: retrieveData\n");

	return dArr->dataArray[pos];
}

void *fetchMatchingData(DynamicArray *dArr, void *expectedData, DataType *dataType) {        
    for (int i = 0; getArrayOffset(dArr); i++) {
        void *data = (void *)retrieveData(dArr, i, dataType);
        if (isElementDataMatching(dArr->referentMember, data, expectedData, dataType)) return data;
    }
    
    return NULL;
}

void reallocateDynamicArray(DynamicArray *dArr) {
	if (getArrayOffset(dArr) == dArr->capacity) {
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
	DynamicArray *clonedArray = createDynamicArray(originaldArr->name, originaldArr->allowOverlapping, originaldArr->allowModification, originaldArr->allowOverlapping, originaldArr->referentMember, dataType);

	for (int i = 0; i < getArrayOffset(originaldArr); i++) {
        void *data = retrieveData(originaldArr, i, dataType);
		copyAndAddToDynamicArray(clonedArray, data, dataType);
	}

	return clonedArray;
}

void destroyDynamicArray(DynamicArray* dArr) {
    for (int i = 0; i < getArrayOffset(dArr); i++) free(dArr->dataArray[i]);
	free(dArr->dataArray);
	free(dArr);
}
