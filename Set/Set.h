#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
class SetIterator;

struct Node;

class Set {
    friend class SetIterator; //allows the iterator to access private members of Set

private:
    Node* head;
    int length;

public:
    Set();

    //adds an element to the set
    //returns true if the element was added, false if it was already in the set
    bool add(TElem e);

    //removes an element from the set
    //returns true if the element was removed, false if it was not in the set
    bool remove(TElem e);

    //checks if an element belongs to the set
    bool search(TElem elem) const;

    //returns the number of elements;
    int size() const;

    //check whether the set is empty or not;
    bool isEmpty() const;

    //returns an iterator for the set
    SetIterator iterator() const;

    //destructor
    ~Set();
};
