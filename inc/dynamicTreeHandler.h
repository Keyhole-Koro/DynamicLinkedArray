#ifndef DYNAMIC_HANDLER_TREE
#define DYNAMIC_HANDLER_TREE

#include <stddef.h>
#include <stdbool.h>

#include "dynamicTree.h"

#include "dataType.h"
#include "utils.h"
#include "overlapHandler.h"

DynamicTree *createDynamicTree(char*ame, bool, bool, int (*referentMember)(void*, DataType*), int (hashCalculation)(void*), DataType*);
Node *createNode(DynamicTree*, void*, DataType*);
void insertData(DynamicTree*, void*, DataType*);
Node *retrieveNode(DynamicTree*, bool (customCmp)(Node*, Node*), void*);
void displayINTTree(DynamicTree*);
void destroyDynamicTree(DynamicTree*);
void destroyTreeRecursive(Node*);

#endif