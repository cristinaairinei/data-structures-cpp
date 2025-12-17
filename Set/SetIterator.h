#pragma once
#include "Set.h"

//DO NOT CHANGE THIS PART
struct Node;

class SetIterator {
    friend class Set; //iterates through the set
private:

    const Set& set; //reference to the set
    Node* current; //current node in the iteration

public:
    SetIterator(const Set& s); //receives a reference to the set which is s

    void first();

    void next();

    TElem getCurrent();

    bool valid() const;

    void previous();  // Moves the iterator to the previous element

};
