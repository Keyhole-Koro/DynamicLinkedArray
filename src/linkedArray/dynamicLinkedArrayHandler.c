#include "dynamicLinkedArrayHandler.h"

DynamicLinkedArray *createDynamicLinkedArray(char *arrayName, int initialCapacity,
        bool ifAllowModification, bool ifAllowOverlapping,
        int (*referentMember)(void*, DataType*), DataType *dataType) {
            
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

    setArrayLength(dArr, dataType);

    void *arr = makeArray(dArr);
    dArr->arrayNode = makeArrayNode(nullptr, arr);

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

void *retrieveLinkedArrayData(DynamicLinkedArray *dArr, int pos, DataType *dataType) {
    int desNodePos = quotient(pos, arraySize(dArr));
    ArrayNode *desNode = fetchNode(dArr->arrayNode, desNodePos);

    printf("dArr:%d %d %d\n", arraySize(dArr), dArr->dataType->size * dArr->arrayLength);
    printf("a%d\n",remainder_int(arraySize(dArr), pos));
    printf("b%d\n",(dataType->size));

    return desNode->array + remainder_int(arraySize(dArr), pos) * (dataType->size);
}

void *fetchNode(ArrayNode *node, int num) {
    if (num <= 0) return node;
    return fetchNode(node->next, num - 1);
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
    initializeElements(arr, arraySize(dArr));
    return arr;
}

void *makeArrayNode(ArrayNode *previousNode, void *array) {
    ArrayNode *node = (ArrayNode *)malloc(sizeof(ArrayNode));
    if (node == NULL) error("Memory allocation failed\n");
    node->array = array;
    node->next = NULL;
    if (previousNode) previousNode->next = node;
    return node;
}

void initializeElements(void *arr, int size) {
    memset(arr, 0, size);
}

void setArrayLength(DynamicLinkedArray *dArr, DataType *dataType) {
    int size = dataType->size;
    if (size <= 9) dArr->arrayLength = 81;
    else if (size <= 16) dArr->arrayLength = 64;
    else if (size <= 25) dArr->arrayLength = 49;
    else if (size <= 36) dArr->arrayLength = 36;
    else if (size <= 49) dArr->arrayLength = 25;
    else if (size <= 64) dArr->arrayLength = 16;
    else  dArr->arrayLength = 9;
}

inline int arraySize(DynamicLinkedArray *dArr) {
    return dArr->dataType->size * dArr->arrayLength;
}

inline int getLinkedArrayOffset(DynamicLinkedArray *dArr) {
    return dArr->offset;
}

inline bool isOutOfRangeLinkedArray(DynamicLinkedArray *dArr, int index) {
    return index < 0 || index > getLinkedArrayOffset(dArr);
}

int quotient_(int operand, int operator, int result) {
    if (operand - operator) return result;
    return quotient_(operand, operator, result + 1);
}

inline int quotient(int operand, int operator) {
    return quotient_(operand, operator, 0);
}

int remainder_int(int operand, int operator) {
    if (operand - operator <= 0) return operand;
    return remainder_int(operand, operator);
}