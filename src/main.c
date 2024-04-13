#include "main.h"

// Define custom comparison function for nodes
bool customCmp(Node *node1, Node *node2) {
    return *(int*)node1->data == *(int*)node2->data;
}

int hashInt(void *data) {
    return *(int*)data;
}

int main() {
    DataType *INT = registerDataType("int", sizeof(int));
    DynamicLinkedArray *arr = createDynamicLinkedArray("test array", true, true, &referenceInt, NULL, INT);

    int element1 = 10;
    addToDynamicLinkedArray(arr, &element1, INT);
    int element2 = 5;
    addToDynamicLinkedArray(arr, &element2, INT);
    int element3 = 14;
    addToDynamicLinkedArray(arr, &element3, INT);

    int *foundData = retrieveLinkedArrayData(arr, 3, INT);
    if (foundData != NULL) {
        printf("Found data: %i\n", *foundData);
    } else {
        printf("data not found\n");
    }

    return 0;
}


/*
int main() {
    DataType *INT = registerDataType("int", sizeof(int));
    DataType *UNSINED_CHAR = registerDataType("unsigned char", sizeof(unsigned char));

    // Initialize a dynamic array
    DynamicArray *myArray = createDynamicArray("test array", 3, true, false, &referenceInt, INT);

    // Add some elements to the array
    int element1 = 10;
    addToDynamicArray(myArray, &element1, INT);

    int element2 = 2;
    addToDynamicArray(myArray, &element2, INT);

    int element3 = 10;
    addToDynamicArray(myArray, &element3, INT);

    int element4 = 10;
    addToDynamicArray(myArray, &element4, INT);

    int element5 = 20;
    addToDynamicArray(myArray, &element5, INT);

    int element6 = 15;
    addToDynamicArray(myArray, &element6, INT);

    int element7 = 10;
    addToDynamicArray(myArray, &element7, INT);

    int element8 = 15;
    addToDynamicArray(myArray, &element8, INT);

    printf("size %i\n", getArrayOffset(myArray));
    // Retrieve and print elements from the array
    showIntElements(myArray);

    showConfigArray(myArray);

    // Fetch matching data
    int searchElement = 10;
    void *foundData = fetchMatchingData(myArray, &searchElement, INT);
    if (foundData != NULL) {
        printf("Found matching data: %d\n", *(int*)foundData);
    } else {
        printf("No matching data found.\n");
    }

    return 0;
}
*/