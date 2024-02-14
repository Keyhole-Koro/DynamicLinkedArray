#include "main.h"

int main() {
    // Initialize a dynamic array
    DynamicArray *myArray = createDynamicArray(10, true, &dummy_member, INT);

    // Add some elements to the array
    int element1 = 10;
    addToDynamicArray(myArray, &element1, INT);

    char element2 = 2;
    addToDynamicArray(myArray, &element2, INT);

    float element3 = 34;
    addToDynamicArray(myArray, &element3, INT);

    // Retrieve and print elements from the array
    showIntElements(myArray);

    // Fetch matching data
    int searchElement = 10;
    void *foundData = fetchMatchingData(myArray, &searchElement, INT);
    if (foundData != NULL) {
        printf("Found matching data: %d\n", *(int*)foundData);
    } else {
        printf("No matching data found.\n");
    }

    // Clone the array
    DynamicArray *clonedArray = cloneArray(myArray);

    // Destroy the arrays
    destroyDynamicArray(myArray);
    destroyDynamicArray(clonedArray);

    return 0;
}
