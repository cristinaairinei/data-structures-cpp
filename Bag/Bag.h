#pragma once
// DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111
#include <utility>

class BagIterator;

class Bag {
    friend class BagIterator;

protected:
    struct Node { //every bucket is a linked list
        std::pair<TElem, int> pair;//elem, frequency
        Node* next; // pointer to the next node in the chain
    };

    Node** head; // array of pointers to the head of each chain(bucket)
    int capacity; //how many buckets we have
    int sizeElems;
    int distinctElems;

    int hash(TElem elem) const; // hash function that maps an element to a bucket
    void resize();

public:
    // Constructor
    Bag();

    // Adds an element to the bag
    void add(TElem e);

    // Removes one occurrence of an element from the bag
    // Returns true if an element was removed, false otherwise
    bool remove(TElem e);

    // Checks if an element appears in the bag
    bool search(TElem e) const;

    // Returns the number of occurrences for an element in the bag
    int nrOccurrences(TElem e) const;

    // Returns the number of elements from the bag (with repetitions)
    int size() const;

    // Returns an iterator for this bag
    BagIterator iterator() const;

    // Checks if the bag is empty
    bool isEmpty() const;

    // Destructor
    ~Bag();
};
