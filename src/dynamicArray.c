#include "dynamicArray.h"

DynamicArray *createDynamicArray(int initialCapacity, bool allowModification, int (*referentMember)(void *, DataType), DataType type) {
    DynamicArray *dArr = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (dArr == NULL) error("Memory allocation failed\n");
    dArr->dataArray = (void **)malloc(sizeof(void *) * initialCapacity);
    initializeElementsInDynamicArray(dArr, 0);
    if (dArr->dataArray == NULL) error("Memory allocation failed\n");

    dArr->dataType = type;
    dArr->dataSize = undefined;
    dArr->offset = undefined;
    dArr->capacity = initialCapacity;
    dArr->allowModification = allowModification;

    dArr->overlapArray = (referentMember != &dummy_member) ? createOverlapArray(initialCapacity) : NULL;    

    dArr->referentMember = referentMember;

    return dArr;
}

void addToDynamicArray(DynamicArray *dArr, void *data, DataType type) {
    if (dArr->allowModification == false) error("Modification not allowed: addToDynamicArray\n");
    if (!isDataTypeMatching(dArr, type)) error("Type mismatch: addToDynamicArray\n");

    if (!isDataSizeSet(dArr)) setDataSize(dArr, data);
    if (!isDataSizeMatching(dArr, sizeof(*data))) error("Type mismatch at addToDynamicArray()\n");
    if (ifElementExists(dArr, dArr->referentMember((void *)data, type))) return;

    reallocateDynamicArray(dArr);

    dArr->dataArray[++dArr->offset] = data;
}

void copyAndAddToDynamicArray(DynamicArray *dArr, void *data, DataType type) {
    if (dArr->allowModification == false) error("Modification not allowed: copyAndAddToDynamicArray\n");
    if (!isDataTypeMatching(dArr, type)) error("Type mismatch: copyAndAddToDynamicArray\n");

    int sizeData = sizeof(*data);

    if (!isDataSizeSet(dArr)) setDataSize(dArr, data);
    if (!isDataSizeMatching(dArr, sizeData)) error("Type mismatch at copyAndAddToDynamicArray()\n");
    if (ifElementExists(dArr, dArr->referentMember((void *)data, type))) return;

    reallocateDynamicArray(dArr);

    void *copy_data_ptr = malloc(sizeData);
    if (copy_data_ptr == NULL) error("Memory allocation failed\n");
    memcpy(copy_data_ptr, data, sizeData);
    dArr->dataArray[++dArr->offset] = copy_data_ptr;
}

void *retriveData(DynamicArray *dArr, int pos, DataType type) {
	if (!isDataTypeMatching(dArr, type)) error("type mismatch: retriveData\n");

	if (isOutOfRange(dArr, pos)) error("Index out of bounds: retriveData\n");

	return dArr->dataArray[pos];
}

void *fetchMatchingData(DynamicArray *dArr, void *expectedData, DataType type) {        
    //may replace here to extractCertainData()
    for (int i = 0; getArraySize(dArr); i++) {
        void *data = (void *)retriveData(dArr, i, type);
        if (isElementDataMatching(dArr->referentMember, data, expectedData, type)) return retriveData(dArr, fetchPosMatchingData(dArr, expectedData, type), type);;
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
	DataType type = originaldArr->dataType;
	DynamicArray *clonedArray = createDynamicArray(getArraySize(originaldArr), originaldArr->allowModification, originaldArr->referentMember, type);

	for (int i = 0; i < getArraySize(originaldArr); i++) {
        void *data = retriveData(originaldArr, i, type);
		appendCopy(clonedArray, data, type);
	}

	return clonedArray;
}

void destroyDynamicArray(DynamicArray* dArr) {
    for (int i = 0; i < getArraySize(dArr); i++) free(dArr->dataArray[i]);
	free(dArr->dataArray);
	free(dArr);
}
