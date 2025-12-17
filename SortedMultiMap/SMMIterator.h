#pragma once

#include "SortedMultiMap.h"

class SMMIterator {
    friend class SortedMultiMap;

protected:
    const SortedMultiMap& map;
    SortedMultiMap::Node** stack;// stack to hold nodes during iteration for in-order trav
    int* valueIndices; //keeps the index of the values of each node
    int stackSize;
    int stackCapacity;

    void pushLeft(SortedMultiMap::Node* node); // pushes all left children of the node onto the stack(in-order trav)
    void resizeStack();

public:

    SMMIterator(const SortedMultiMap& m);

    // Initializes the iterator to the first element in the SortedMultiMap
    void first();

    // Moves the iterator to the next element in the SortedMultiMap
    void next();

    // Checks if the iterator is valid
    bool valid() const;

    // Returns the current element pointed to by the iterator
    TElem getCurrent() const;

    // Destructor
    ~SMMIterator();
};
