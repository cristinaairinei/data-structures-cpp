#include "Set.h"
#include "SetIterator.h"

// DO NOT CHANGE THIS PART
struct Node { //linked list node
    TElem data;
    Node* next; // Pointer to the next node in the linked list
};

Set::Set() {
    head = nullptr;
    length = 0;  //O(1)
}

bool Set::add(TElem elem) {
    if (search(elem))
        return false; //if the el is already here

    Node* newNode = new Node{elem, head}; // Create a new node and set its next pointer to the current head
    head = newNode; // Update the head bc we put it at the beggining
    length++;
    return true; //BC:teta(1), WC:teta(N), total O(n)
}

bool Set::remove(TElem elem) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr && current->data != elem) {
        prev = current;
        current = current->next;
    } // Traverse the list to find the element

    if (current == nullptr)
        return false; // Element not found

    if (prev == nullptr)
        head = head->next; //we move the head to the next node
    else
        prev->next = current->next; // Bypass the current node

    delete current;
    length--;
    return true; //BC:teta(1), WC:teta(N), total O(n)
}

bool Set::search(TElem elem) const {
    Node* current = head; // Start from the head of the list
    while (current != nullptr) {
        if (current->data == elem)
            return true;
        current = current->next;
    }
    return false;
}//BC:teta(1), WC:teta(N), total O(n)

int Set::size() const {
    return length; // O(1)
}

bool Set::isEmpty() const {
    return length == 0; // O(1)
}

Set::~Set() { // Destructor
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next; //that is how we delete the list
    }
}// O(n), total complexity

SetIterator Set::iterator() const {
    return SetIterator(*this);// O(1)
}
