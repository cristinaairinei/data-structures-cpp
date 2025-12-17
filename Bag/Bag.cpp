#include "Bag.h"
#include "BagIterator.h"
#include <exception>

// Constructor
Bag::Bag() {
    capacity = 13;
    head = new Node*[capacity]; // array of pointers to the head of each chain
    for (int i = 0; i < capacity; ++i)
        head[i] = nullptr;
    sizeElems = 0;
    distinctElems = 0;
}
// Complexity: O(capacity), (teta of (nr of buckets))

// Hash function that transforms an element into a bucket index
int Bag::hash(TElem e) const {
    return abs(e) % capacity;
}
//Complexity: O(1)


void Bag::resize() {
    int newCapacity = capacity * 2;
    Node** newHead = new Node*[newCapacity]; // new array of pointers to the head of each chain (buckets)
    for (int i = 0; i < newCapacity; ++i)
        newHead[i] = nullptr;// initialize all buckets to nullptr

    for (int i = 0; i < capacity; ++i) {
        Node* current = head[i];  // iterate through the old buckets
        while (current != nullptr) {
            int newIndex = abs(current->pair.first) % newCapacity;
            Node* newNode = new Node{current->pair, newHead[newIndex]};
            newHead[newIndex] = newNode;
            current = current->next;
        }
    }

    delete[] head;
    head = newHead;
    capacity = newCapacity;
}
//complexity O(capacity), total complexity


void Bag::add(TElem e) {
    if ((double)distinctElems / capacity > 0.75) // load factor > 0.75
        resize();

    int index = hash(e);
    Node* current = head[index]; //we calc in which bucket we have to add the element

    while (current != nullptr) {
        if (current->pair.first == e) {
            current->pair.second++;
            sizeElems++;
            return;
        }
        current = current->next;
    }

    Node* newNode = new Node{{e, 1}, head[index]};
    head[index] = newNode; // add the new node to the head of the bucket
    sizeElems++;
    distinctElems++;
}

//complexity teta(1) for the case when the element is in the first node of the bucket
//complexity teta(n) in the worst case when the element is not in the bag or is in the last node of the bucket
//complexity O(n) in the average case when the element is in the middle of the bucket

// Removes one occurrence of an element
bool Bag::remove(TElem e) {
    int index = hash(e);
    Node* current = head[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->pair.first == e) {
            current->pair.second--;
            sizeElems--;

            if (current->pair.second == 0) { // if frequency is 0, remove the node
                if (prev == nullptr)
                    head[index] = current->next;
                else
                    prev->next = current->next;
                delete current;
                distinctElems--;
            }
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}
//complexity teta(1) for the case when the element is in the first node of the bucket
//complexity teta(n) in the worst case when the element is not in the bag or is in the last node of the bucket
//complexity O(n) in the average case when the element is in the middle of the bucket


bool Bag::search(TElem e) const {
    int index = hash(e);
    Node* current = head[index];

    while (current != nullptr) {
        if (current->pair.first == e)
            return true;
        current = current->next;
    }
    return false;
}
//complexity teta(1) for the case when the element is in the first node of the bucket
//complexity teta(n) in the worst case when the element is not in the bag or is in the last node of the bucket
//complexity O(n) in the average case when the element is in the middle of the bucket


int Bag::nrOccurrences(TElem e) const {
    int index = hash(e);
    Node* current = head[index];

    while (current != nullptr) {
        if (current->pair.first == e)
            return current->pair.second;
        current = current->next;
    }
    return 0;
}
//completity teta(1) for the case when the element is in the first node of the bucket
//complexity teta(n) in the worst case when the element is not in the bag or is in the last node of the bucket
//complexity O(n) in the average case when the element is in the middle of the bucket



int Bag::size() const {
    return sizeElems;
}
//complexity O(1)


bool Bag::isEmpty() const {
    return sizeElems == 0;
}
//complexity: O(1)


BagIterator Bag::iterator() const {
    return BagIterator(*this);
}

// Destructor
Bag::~Bag() {
    for (int i = 0; i < capacity; ++i) { // delete all nodes in each bucket
        Node* current = head[i];
        while (current != nullptr) {
            Node* toDelete = current; // save current node to delete
            current = current->next;
            delete toDelete;
        }
    }
    delete[] head;
}
// Complexity: O(capacity)
