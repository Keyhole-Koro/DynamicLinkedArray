#include "hash.h"

int calculateHash(DynamicArray *arr, int (referentMember)(void*, DataType*), DataType *type) {
	int hash = 0;

	for (int i = 0; i < getArrayOffset(arr); i++) {
		void *data = retrieveData(arr, i, type);
		hash ^= referentMember(data, type);
	}

	return hash;
}