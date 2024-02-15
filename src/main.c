#include "main.h"

int main() {
    DataType *INT = registerDataType("int", sizeof(int));
    DataType *UNSINED_CHAR = registerDataType("unsigned char", sizeof(unsigned char));

    // Initialize a dynamic array
    DynamicArray *myArray = createDynamicArray(10, true, &dummy_member, INT);

    // Add some elements to the array
    int element1 = 10;
    addToDynamicArray(myArray, &element1, INT);

    int element2 = 2;
    addToDynamicArray(myArray, &element2, INT);

    int element3 = 34;
    addToDynamicArray(myArray, &element3, INT);

    DynamicArray *clonedArray = cloneArray(myArray);

    // Retrieve and print elements from the array
    showIntElements(clonedArray);

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
