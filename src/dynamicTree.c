#include "dynamicTree.h"

void insertPayloadRecursive(Node*, Node*);
Node *retriveNodeRecursive(Node*, bool (customCmp)(Node*, Node*), Node*);
void ensureConsistentTreeElements(DynamicTree*, DataType*);

DynamicTree *createDynamicTree(int (*referentMember)(void*, DataType*), bool allowModification, DataType *dataType) {
    DynamicTree *tree = (DynamicTree*)malloc(sizeof(DynamicTree));
    tree->dataType = dataType;
    tree->root = NULL;
    tree->numNode = 0;

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

void insertPayload(DynamicTree *tree, Node *newNode, DataType *dataType) {
    ensureConsistentTreeElements(tree, dataType);

    if (!isDataTypeMatching(tree->dataType, dataType)) error("Type mismatch at addToDynamicArray()\n");
    //if (ifElementExists(tree, tree->referentMember((void *)tree, type))) return;

    insertPayloadRecursive(tree->root, newNode);

    tree->numNode++;
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

void ensureConsistentTreeElements(DynamicTree *tree, DataType *dataType) {
    if (isDataTypeMatching(tree->dataType, dataType)) error("data type doesn't match");
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