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

    insertPayloadRecursive(tree->root, newNode);
}

void insertPayloadRecursive(Node *root, Node *newNode) {
    if (root == NULL) {
        root = newNode;
        return;
    }
    HASH_LESS_THAN_OR_EQUAL(root, newNode) ? root_insertPayload(root->left, newNode) : root_insertPayload(root->right, newNode);       
}

Node *retriveNode(DynamicTree *tree, bool (customCmp)(Node*, Node*), void *payload) {
    Node *expectedNode = createNode(tree, payload);

    return retriveNodeRecursive(tree->root, expectedNode);  // Return the found Data node or NULL if not found
}

Node *retriveNodeRecursive(Node *root, Node *expectedNode) {
    if (customCmp(root, expectedNode)) return root;
    return (HASH_LESS_THAN_OR_EQUAL(root, expectedNode)) ? retriveNodeRecursive(root->left, expectedNode) : retriveNodeRecursive(root->right, expectedNode);
    return NULL;
}

void ensureConsistentTreeElements(DynamicTree *tree, Node *newNode, DataType type) {
    if (tree->dataSize != sizeof(*(newNode->payload))) error("The data sizes don't match");
    if (tree->dataType != type) error("The data types don't match");
}

void deleteNode(DynamicTree *tree, int hash) {
    tree->root = deleteNodeRecursive(tree->root, hash);
}

Node *deleteNodeRecursive(Node *root, int hash) {
    if (root == NULL) return root; // Base case: If the tree or subtree is empty, return NULL

    if (hash < root->hash) {
        root->left = deleteNodeRecursive(root->left, hash);
    } else if (hash > root->hash) {
        root->right = deleteNodeRecursive(root->right, hash);
    } else { // If the hash matches, this is the node to be deleted
        // Node with only one child or no child
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node *temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->hash = temp->hash;
        root->payload = temp->payload;

        // Delete the inorder successor
        root->right = deleteNodeRecursive(root->right, temp->hash);
    }
    return root;
}

Node *minValueNode(Node *node) {
    Node *current = node;

    while (current->left != NULL) {
        current = current->left;
    }
    return current;
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