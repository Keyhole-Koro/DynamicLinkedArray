#ifndef DYNAMIC_TREE
#define DYNAMIC_TREE

#include <stddef.h>
#include <stdbool.h>

#include "dataTypeHandler.h"
#include "overlapHandler.h"
#include "utils.h"

#include "dynamicTree.h"

DynamicTree *createDynamicTree(char*ame, bool, bool, int (*referentMember)(void*, DataType*), int (hashCalculation)(void*, DataType*), DataType*);
void *createNode(DynamicTree*, void*, DataType*);
void insertPayload(DynamicTree*, void*, DataType*);
void insertPayloadRecursive(DynamicTree*, Node*);
Node *retrieveNode(DynamicTree*, bool (customCmp)(Node*, Node*), void*);
Node *retrieveNodeRecursive(Node*, bool (customCmp)(Node*, Node*), Node*);
void destroyDynamicTree(DynamicTree*);
void destroyTreeRecursive(Node*);

#endif