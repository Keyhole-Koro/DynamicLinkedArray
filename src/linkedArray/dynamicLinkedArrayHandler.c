#include "dynamicLinkedArrayHandler.c"

DynamicLinkedArray *createDynamicLinkedArray(char *arrayName, int initialCapacity, bool ifAllowModification, bool ifAllowOverlapping, int (*referentMember)(void*, DataType*), DataType *dataType) {
    DynamicLinkedArray *dArr = (DynamicLinkedArray *)malloc(sizeof(DynamicLinkedArray));
    if (dArr == NULL) error("Memory allocation failed\n");
    
    dArr->name = arrayName;
    dArr->dataType = dataType;
    dArr->offset = 0;
    dArr->capacity = initialCapacity;
    dArr->allowModification = ifAllowModification;
    dArr->allowOverlapping = ifAllowOverlapping;

    dArr->overlapArray = (referentMember != &dummy_member) ? createOverlapArray(initialCapacity) : NULL;    

    dArr->referentMember = referentMember;

    void *arr = makeArray(dArr);
    dArr->arrayNode = makeArrayNode(NULL, arr);

    return dArr;
}

bool validateDynamicLinkedArrayAddition(DynamicLinkedArray *dArr, void *data, DataType *dataType) {
    if (dArr->allowModification == false) error("Modification not allowed: (copyAnd)addToDynamicArray\n");
    if (!isDataTypeMatching(dArr->dataType, dataType)) error("Type mismatches: (copyAnd)addToDynamicArray\n");

    if (!dArr->allowOverlapping && ifElementExists(dArr->overlapArray, dArr->referentMember(data, dataType))) return false;
    return true;
}

void addToDynamicLinkedArray(DynamicLinkedArray *dArr, void *data, DataType *dataType) {
    if (!validateDynamicLinkedArrayAddition(dArr, data, dataType)) return;

    void *arr = fetchLatestArray(dArr);

    memcpy(arr +  dataType->size*(dArr->offset++), data, dataType->size);
}

void *fetchLatestArray(DynamicLinkedArray *dArr) {
    return fetchLatestArray_(dArr->arrayNode);
}

void *fetchLatestArray_(ArrayNode *node) {
    if (node->next == NULL) return node->array;
    return fetchLatestArray_(node->next);
}

void newArray(DynamicLinkedArray *dArr) {
    void *arr = makeArray(dArr);
    makeArrayNode(NULL, arr);
}

void *makeArray(DynamicLinkedArray *dArr) {
    void *arr = malloc(arraySize(dArr));
    if (arr == NULL) error("Memory allocation failed\n");
    initializeElements(arr);
    return arr;
}

void makeArrayNode(ArrayNode *previousNode, void *array) {
    ArrayNode *node = (ArrayNode *)malloc(sizeof(ArrayNode));
    if (node == NULL) error("Memory allocation failed\n");
    node->array = array;
    node->next = NULL;
    if (previousNode) previousNode->next = node;
}

void initializeElements(void *arr) {
    for (int i = 0; i < arraySize(dArr); i++) {
        arr[i] = NULL;
    }
}

void insertArrayLength(DynamicLinkedArray *dArr, DataType *dataType) {
    int size = dataType->size;
    if (size <= 9) dArr->arrayLength = 81;
    else if (size <= 16) dArr->arrayLength = 64;
    else if (size <= 25) dArr->arrayLength = 49;
    else if (size <= 36) dArr->arrayLength = 36;
    else if (size <= 49) dArr->arrayLength = 25;
    else if (size <= 64) dArr->arrayLength = 16;
    else  dArr->arrayLength = 9;
}

