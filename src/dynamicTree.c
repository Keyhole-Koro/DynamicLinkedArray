#include "dynamicTree.h"

DynamicTree *createDynamicTree(char *name, bool allowOverlapping, bool allowModification, int (*referentMember)(void*, DataType*), int (hashCalculation)(void*), DataType *dataType) {
    DynamicTree *tree = (DynamicTree*)malloc(sizeof(DynamicTree));
    if (tree == NULL) error("allocation failed to create tree");
    tree->name = name;
    tree->dataType = dataType;
    tree->root = NULL;

    tree->hashCalculation = hashCalculation;

    tree->overlapArray = (referentMember != &dummy_member) ? createOverlapArray(10) : NULL;    
    tree->referentMember = referentMember;

    tree->allowOverlapping = allowOverlapping;
    tree->allowModification = allowModification;
    return tree;
}

Node *createNode(DynamicTree *tree, void *data, DataType *dataType) {
    if (tree->dataType != dataType) error("type mismatch");
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) error("allocation failed to create node");
    node->hash = tree->hashCalculation(data);
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}

void insertDataRecursive(DynamicTree *tree, Node **root, Node *newNode) {
    DataType *dataType = tree->dataType;
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    if (!tree->allowOverlapping && (*root)->hash == newNode->hash && tree->referentMember((*root)->data, dataType) == tree->referentMember(newNode->data, dataType)) return;

    if (HASH_LESS_THAN_OR_EQUAL(*root, newNode)) {
        insertDataRecursive(tree, &((*root)->left), newNode);
    } else {
        insertDataRecursive(tree, &((*root)->right), newNode);
    }
}


void insertData(DynamicTree *tree, void *data, DataType *dataType) {
    if (!isDataTypeMatching(tree->dataType, dataType)) error("Type mismatch at addToDynamicArray()\n");
    Node *newNode = createNode(tree, data, dataType);
    insertDataRecursive(tree, &(tree->root), newNode);
}

Node *retrieveNodeRecursive(Node *root, bool (customCmp)(Node*, Node*), Node *expectedNode) {
    if (!root) return NULL;
    if (customCmp(root, expectedNode)) return root;
    if (!root->left || !root->right) return NULL;
    
    return (HASH_LESS_THAN_OR_EQUAL(root, expectedNode)) ? retrieveNodeRecursive(root->left, customCmp, expectedNode) : retrieveNodeRecursive(root->right, customCmp, expectedNode);
}

Node *retrieveNode(DynamicTree *tree, bool (customCmp)(Node*, Node*), void *data) {
    Node *expectedNode = createNode(tree, data, tree->dataType);

    return retrieveNodeRecursive(tree->root, customCmp, expectedNode); // Return the found Data node or NULL if not found
}

void displayINTTreeInOrder(Node *root) {
    if (root != NULL) {
        displayINTTreeInOrder(root->left);
        printf("%d ", *(int*)(root->data)); // Assuming data is an integer. Modify accordingly for other types.
        displayINTTreeInOrder(root->right);
    }
}

void displayINTTree(DynamicTree *tree) {
    displayINTTreeInOrder(tree->root);
    printf("\n");
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
        free(root->data);
        free(root);
    }
}