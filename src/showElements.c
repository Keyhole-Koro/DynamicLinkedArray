#include "showElements.h"

// You need to make another funciton for your own data
void showIntElements(DynamicArray *arr) {
    printf("All elements in the array:\n");
    for (int i = 0; i < getArraySize(arr); i++) {
        void *data = retrieveData(arr, i, arr->dataType);
        // Assuming each element is an integer, you can adjust accordingly for other types
        printf("%d\n", *(int *)data);
    }
}
