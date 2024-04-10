#ifndef OVERLAP_H
#define OVERLAP_H

/**
    @param elementExistenceArray An array contains true or false indicates existences of elements
    @param capacity A capacity of the overlapping array
**/
typedef struct {
    bool *elementExistenceArray;
    int capacity;
} OverlapArray;

#endif