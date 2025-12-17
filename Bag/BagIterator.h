#pragma once
#include "Bag.h"

class Bag;

class BagIterator {
    friend class Bag;

protected:
    const Bag& bag; // Reference to the bag
    int currentBucket;
    Bag::Node* currentNode;
    int freqIndex;

    BagIterator(const Bag& c);

public:
    void first(); // Initialize the iterator to the first element
    void next();// Move to the next element
    bool valid() const;// Check if the iterator is valid (not past the end)
    int getCurrent() const;// Get the current element
    void previous(); // Move to the previous element
};