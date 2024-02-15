#include "dynamicTree.h"

void insertPayloadRecursive(Node *root, Node *newNode);
Node *retriveNodeRecursive(Node *root, bool (customCmp)(Node*, Node*), Node *expectedNode);
void ensureConsistentTreeElements(DynamicTree *tree, Node *newNode, DataType type);

DynamicTree *createDynamicTree(int (*referentMember)(void*, DataType), bool allowModification, DataType dataType) {
    DynamicTree *tree = (DynamicTree*)malloc(sizeof(DynamicTree));
    tree->dataType = dataType;
    tree->dataSize = undefined;
    tree->root = NULL;
    
    tree->overlapArray = (referentMember != &dummy_member) ? createOverlapArray(10) : NULL;    
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
    return node;
}

void insertPayload(DynamicTree *tree, Node *newNode, DataType type) {
    ensureConsistentTreeElements(tree, newNode, type);

    if (!isDataSizeSet((DataUnion*)tree)) setDataSize((DataUnion*)tree, newNode->payload);
    if (!isDataSizeMatching((DataUnion*)tree, sizeof(*newNode->payload))) error("Type mismatch at addToDynamicArray()\n");
    //if (ifElementExists(tree, tree->referentMember((void *)tree, type))) return;

    insertPayloadRecursive(tree->root, newNode);
}

void insertPayloadRecursive(Node *root, Node *newNode) {
    if (root == NULL) {
        root = newNode;
        return;
    }
    HASH_LESS_THAN_OR_EQUAL(root, newNode) ? insertPayloadRecursive(root->left, newNode) : insertPayloadRecursive(root->right, newNode);       
}

Node *retriveNode(DynamicTree *tree, bool (customCmp)(Node*, Node*), void *payload) {
    Node *expectedNode = createNode(tree, payload);

    return retriveNodeRecursive(tree->root, customCmp, expectedNode);  // Return the found Data node or NULL if not found
}

Node *retriveNodeRecursive(Node *root, bool (customCmp)(Node*, Node*), Node *expectedNode) {
    if (customCmp(root, expectedNode)) return root;
    return (HASH_LESS_THAN_OR_EQUAL(root, expectedNode)) ? retriveNodeRecursive(root->left, customCmp, expectedNode) : retriveNodeRecursive(root->right, customCmp, expectedNode);
    return NULL;
}

void ensureConsistentTreeElements(DynamicTree *tree, Node *newNode, DataType type) {
    if (isDataSizeMatching((DataUnion*)tree, sizeof(newNode->payload))) error("The data sizes don't match");
    if (isDataTypeMatching((DataUnion*)tree, type)) error("The data types don't match");
}

void destroyDynamicTree(DynamicTree *tree) {
    destroyTreeRecursive(tree->root);
    if (tree->overlapArray != NULL) {
        destroyOverlapArray(tree->overlapArray);
    }
    free(tree);
}

void destroyTreeRecursive(Node *root) {
    if (root != NULL) {
        destroyTreeRecursive(root->left);
        destroyTreeRecursive(root->right);
        free(root->payload);
        free(root);
    }
}