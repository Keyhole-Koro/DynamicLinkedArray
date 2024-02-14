#include "./include/dynamicTree.h"

// Function to create a new DynamicTree
DynamicTree *createDynamicTree(bool ifAllowOverlapping, int (*referentMember)(void*, DataType), bool allowModification, DataType dataType) {
    DynamicTree *tree = (DynamicTree*)malloc(sizeof(DynamicTree));
    tree->dataType = dataType;
    tree->dataSize = undefined;
    tree->root = NULL;
    
    tree->overlapArray = (referentMember != &dummy_member) ? createOverlapArray() : NULL;    
    tree->referentMember = referentMember;

    tree->allowModification = allowModification;
    return tree;
}

void *createNode(DynamicTree *tree, void *payload) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->hash = tree->hashCalculation(payload, tree->dataType);
    node->left = NULL;
    node->right = NULL;
    node->payload = payload;
}

void insertPayload(DynamicTree *tree, Node *newNode, DataType type) {
    ensureConsistentTreeElements(tree, newNode, type);

    if (!isDataSizeSet(tree)) setDataSize(tree, newNode->payload);
    if (!isDataSizeMatching(tree, sizeof(*newNode->payload))) error("Type mismatch at addToDynamicArray()\n");
    if (ifElementExists(tree, tree->referentMember((void *)tree, type))) return;

    void root_insertPayload(Node *root, Node *newNode) {
        if (root == NULL) {
            root = newNode;
            return;
        }
        if (HASH_LESS_THAN_OR_EQUAL(root, newNode) ? root_insertPayload(root->left, newNode)) : root_insertPayload(root->right, newNode);       
    }

    root_insertPayload(tree->root, newData);
}

void *retrivePayload(DynamicTree *tree, bool (customCmp)(Node*, Node*), void *payload) {
    Node *expectedNode = createNode(tree, payload);

    void root_retrivePayload(Node *root, Node *expectedNode) {
        if (customCmp(root, expectedNode)) return root;
        if (HASH_LESS_THAN_OR_EQUAL(root, expectedNode)) ? root_retrivePayload(root->left, expectedNode) : root_retrivePayload(root->right, expectedNode);
    }

    return root_retrivePayload(tree->root, expectedNode);  // Return the found Data node or NULL if not found
}

void ensureConsistentTreeElements(DynamicTree *tree, Node *newNode, DataType type) {
    if (tree->dataSize != sizeof(*(newNode->payload))) error("The data sizes don't match");
    if (tree->dataType != type) error("The data types don't match");
}
// Sample usage
int main() {
    DynamicTree *myTree = createDynamicTree(/* your parameters here */);

    void *newPayload = /* create a Data node */;
    insertPayload(myTree, newPayload);

    void *foundData = retrivePayload(myTree, );

    // Deletion example
    int deleteHash = /* specify the hash value */;
    deleteNode(myTree, deleteHash);

    // Cleanup
    destroyDynamicTree(myTree);

    return 0;
}