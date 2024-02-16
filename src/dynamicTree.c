#include "dynamicTree.h"

DynamicTree *createDynamicTree(char *name, bool allowOverlapping, bool allowModification, int (*referentMember)(void*, DataType*), int (hashCalculation)(void*, DataType*), DataType *dataType) {
    DynamicTree *tree = (DynamicTree*)malloc(sizeof(DynamicTree));
    if (tree == NULL) error("allocation failed to create tree");
    tree->name = name;
    tree->dataType = dataType;
    tree->root = NULL;
    tree->numNode = 0;

    tree->hashCalculation = hashCalculation;

    tree->overlapArray = (referentMember != &dummy_member) ? createOverlapArray(10) : NULL;    
    tree->referentMember = referentMember;

    tree->allowOverlapping = allowOverlapping;
    tree->allowModification = allowModification;
    return tree;
}

void *createNode(DynamicTree *tree, void *payload, DataType *dataType) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) error("allocation failed to create node");
    node->hash = tree->hashCalculation(payload, dataType);
    node->left = NULL;
    node->right = NULL;
    node->payload = payload;
    return node;
}

void insertPayload(DynamicTree *tree, void *payload, DataType *dataType) {
    if (!isDataTypeMatching(tree->dataType, dataType)) error("Type mismatch at addToDynamicArray()\n");
    Node *newNode = createNode(tree, payload, dataType);
    insertPayloadRecursive(tree, newNode);

    tree->numNode++;
}

void insertPayloadRecursive(DynamicTree *tree, Node *newNode) {
    Node *root = tree->root;
    DataType *dataType = tree->dataType;
    if (!tree->allowOverlapping && root->hash == newNode->hash && tree->referentMember(root->payload, dataType) == tree->referentMember(newNode->payload, dataType)) return; // compares hash, referent member are the same
    if (!root) {
        root = newNode;
        return;
    }
    HASH_LESS_THAN_OR_EQUAL(root, newNode) ? insertPayloadRecursive(tree, newNode) : insertPayloadRecursive(tree, newNode);       
}

Node *retrieveNode(DynamicTree *tree, bool (customCmp)(Node*, Node*), void *payload) {
    Node *expectedNode = createNode(tree, payload, tree->dataType);

    return retrieveNodeRecursive(tree->root, customCmp, expectedNode); // Return the found Data node or NULL if not found
}

Node *retrieveNodeRecursive(Node *root, bool (customCmp)(Node*, Node*), Node *expectedNode) {
    printf("1\n");
    if (!root) return NULL;
    printf("2\n");
    if (customCmp(root, expectedNode)) return root;
    printf("3\n");
    if (!root->left || !root->right) return NULL;
    printf("4\n");
    return (HASH_LESS_THAN_OR_EQUAL(root, expectedNode)) ? retrieveNodeRecursive(root->left, customCmp, expectedNode) : retrieveNodeRecursive(root->right, customCmp, expectedNode);
}

void destroyDynamicTree(DynamicTree *tree) {
    if (tree->overlapArray != NULL) {
        destroyOverlapArray(tree->overlapArray);
    }
    destroyTreeRecursive(tree->root);
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