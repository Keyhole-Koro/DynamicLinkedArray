#include "./include/dynamicTree.h"

// Function to create a new DynamicTree
DynamicTree *createDynamicTree(int dataSize, bool ifAllowOverlapping, int (*referentMember)(void*, DataType), bool allowModification, DataType dataType) {
    DynamicTree* tree = (DynamicTree*)malloc(sizeof(DynamicTree));
    tree->dataType = dataType;
    tree->dataSize = dataSize;
    tree->root = NULL;
    
    arr->overlapArray = (referentMember != &dummy_member) ? createOverlapArray(initialCapacity) : NULL;    
    arr->referentMember = referentMember;

    tree->allowModification = allowModification;
    return tree;
}

void *createNode(int hash, void *payload) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->hash = hash;
    node->left = NULL;
    node->right = NULL;
    node->payload = payload;
}

void insertPayload(DynamicTree *tree, Node *newNode, DataType type) {
    ensureConsistentTreeElements(tree, newNode, type);

    void root_insertPayload(Node *root, Node *newNode) {
        if (root == NULL) {
            root = newNode;
            return;
        }
        if (HASH_LESS_THAN_OR_EQUAL(root, newNode) ? root_insertPayload(root->left, newNode)) : root_insertPayload(root->right, newNode);       
    }

    root_insertPayload(tree->root, newData);
}

// Function to lookup a Data in the DynamicTree
void *retrivePayload(DynamicTree *tree, bool (customCmp)(Node*, Node*), void *payload) {
    Node *expectedNode = createNode(hash, payload);
    void root_retrivePayload(Node *root, Node *expectedNode) {
        if (customCmp(root, expectedNode)) return root;
        if (HASH_LESS_THAN_OR_EQUAL(root, expectedNode)) ? root_retrivePayload(root->left, expectedNode) : root_retrivePayload(root->right, expectedNode);
    }
    return root_retrivePayload(tree->root, expectedNode);  // Return the found Data node or NULL if not found
}

// Function to delete a Data from the DynamicTree
void deletePayload(DynamicTree* tree, int hash) {
    // Implementation for deletion logic
    // You need to handle how to delete a Data node from the tree
}

// Function to destroy the DynamicTree and free memory
void destroyDynamicTree(DynamicTree* tree) {
    // Implementation for destroying the DynamicTree
    // Free memory and perform any cleanup
    free(tree);
}

void ensureConsistentTreeElements(DynamicTree *tree, Node *newNode, DataType type) {
    if (tree->dataSize != sizeof(*(newNode->payload))) error("The data sizes don't match");
    if (tree->DataType != type) error("The data types don't match");
}
// Sample usage
int main() {
    DynamicTree* myTree = createDynamicTree(/* your parameters here */);

    // Insertion example
    void* newPayload = /* create a Data node */;
    insertPayload(myTree, newPayload);

    // Lookup example
    int lookupHash = /* specify the hash value */;
    void* foundData = retrivePayload(myTree, lookupHash);

    // Deletion example
    int deleteHash = /* specify the hash value */;
    deleteNode(myTree, deleteHash);

    // Cleanup
    destroyDynamicTree(myTree);

    return 0;
}