#include "main.h"

#include <stdio.h>
#include "dynamicTree.h"

// Define custom comparison function for nodes
bool customCmp(Node *node1, Node *node2) {
    printf("%d %d\n", *(int*)node1->payload, *(int*)node2->payload);
    return *(int*)node1->payload == *(int*)node2->payload;
}

int hashInt(void *payload) {
    return *(int*)payload;
}

int main() {
    DataType *INT = registerDataType("int", sizeof(int));
    // Create a dynamic tree
    DynamicTree *tree = createDynamicTree("test tree", true, true, referenceInt, hashInt, INT);
    // Insert some nodes into the tree
    int element1 = 10;
    insertPayload(tree, &element1, INT);
    int element2 = 5;
    insertPayload(tree, &element2, INT);
    int element3 = 14;
    insertPayload(tree, &element3, INT);
    // Retrieve a node from the tree
    Node *foundNode = retrieveNode(tree, customCmp, &element3);
    if (foundNode != NULL) {
        printf("Found node: %i\n", *(int*)foundNode->payload);
    } else {
        printf("Node not found\n");
    }

    // Debugging: Print the tree structure
    printf("Tree structure:\n");

    // Destroy the dynamic tree
    destroyDynamicTree(tree);

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