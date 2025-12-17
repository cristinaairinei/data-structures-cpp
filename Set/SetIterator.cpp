#include "SetIterator.h"
#include <exception>

// DO NOT CHANGE THIS PART
struct Node {
    TElem data;
    Node* next;
};


SetIterator::SetIterator(const Set& s) : set(s) {
    current = s.head; // Initialize the iterator to point to the head of the set
}// O(1)

void SetIterator::first() {
    current = set.head;
}// O(1)

void SetIterator::next() {
    if (!valid())
        throw std::exception();
    current = current->next;
}// O(1)

TElem SetIterator::getCurrent() {
    if (!valid())
        throw std::exception();
    return current->data;
}// O(1)

bool SetIterator::valid() const {
    return current != nullptr;
}// O(1), total complexity

void SetIterator::previous() {
    if (!valid()) {
        throw std::exception();
    }

    if (current == set.head) {
        current = nullptr;
        return; //we don t have a previous node
    }


    Node* node = set.head;
    while (node != nullptr && node->next != current) {
        node = node->next; // Traverse the list to find the previous node
    }

    current = node; // Update current to point to the previous node
}
//0(n) total complexity