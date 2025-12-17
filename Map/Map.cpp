#include "Map.h"
#include "MapIterator.h"

// constructor
Map::Map() {
    capacity = 10;
    nodes = new DLLNode[capacity]; // array of nodes
    for (int i = 0; i < capacity - 1; i++) {
        nodes[i].next = i + 1; // link the nodes to each other
    }
    nodes[capacity - 1].next = -1; // last node points to -1
    firstEmpty = 0; // first empty node is the first one bc the array is empty
    head = -1;
    tail = -1;
    nrElements = 0;

}
//complexity O(capacity)

// destructor
Map::~Map() {
    delete[] nodes; // free the array of nodes
}
//complexity O(capacity)


void Map::resize() {
    DLLNode* newNodes = new DLLNode[capacity * 2];
    for (int i = 0; i < capacity; i++) {
        newNodes[i] = nodes[i]; // copy the old nodes
    }
    for (int i = capacity; i < 2 * capacity - 1; i++) {
        newNodes[i].next = i + 1;
    }
    newNodes[2 * capacity - 1].next = -1;
    firstEmpty = capacity; //the firts empty node is the first one in the new array
    capacity = 2 * capacity;
    delete[] nodes; //free the old array
    nodes = newNodes; //point to the new array
}
//complexity Θ(1) best case, Θ(n) worst case and O(n) total case


TValue Map::add(TKey c, TValue v) {
    int current = head;
    while (current != -1) {
        if (nodes[current].info.first == c) {
            TValue oldValue = nodes[current].info.second; //we store the old value to be returned
            nodes[current].info.second = v; //update the value
            return oldValue;
        }
        current = nodes[current].next;
    }

    if (firstEmpty == -1) { //if the array is full and we didn t find the key, we need to resize
        resize();
    }

    int newPos = firstEmpty; //we allocate the first empty node
    firstEmpty = nodes[firstEmpty].next; //we update the first empty node

    nodes[newPos].info = std::make_pair(c, v);
    nodes[newPos].prev = tail;
    nodes[newPos].next = -1;

    if (tail != -1) { //if the list is not empty, we link the last node to the new one
        nodes[tail].next = newPos;
    }
    tail = newPos; //new node is the last one now

    if (head == -1) { //if the list is empty, we set the head to the new node
        head = newPos;
    }

    nrElements++;
    return NULL_TVALUE;
}
//complexity Θ(1) best case if the key is found immediately or if we are inserting into an empty list,
// Θ(n) worst case if the array is full, resize
// and 0(n) total case, average case

TValue Map::search(TKey c) const {
    int current = head;
    while (current != -1) {
        if (nodes[current].info.first == c) {
            return nodes[current].info.second;
        }
        current = nodes[current].next;
    }
    return NULL_TVALUE;
}
//complexity Θ(n) in the worst case, Θ(1) in the best case and O(n) in the total case


TValue Map::remove(TKey c) {
    int current = head;
    while (current != -1) {
        if (nodes[current].info.first == c) {
            TValue oldValue = nodes[current].info.second; //we store the old value to be returned

            if (nodes[current].prev != -1) {
                nodes[nodes[current].prev].next = nodes[current].next; //we link the previous node to the next one skipping the current one
            }
            else {
                head = nodes[current].next; //if it is the first node, we update the head to point to the next one skipping the current one
            }

            if (nodes[current].next != -1) {
                nodes[nodes[current].next].prev = nodes[current].prev; //we link the next node to the previous one skipping the current one
            }
            else { //if it is the last node, we update the tail to point to the previous one skipping the current one
                tail = nodes[current].prev;
            }

            nodes[current].next = firstEmpty;
            firstEmpty = current;

            nrElements--;
            return oldValue;
        }
        current = nodes[current].next;
    }
    return NULL_TVALUE;
}
//complexity Θ(1) best case, Θ(n) worst case and O(n) total case


int Map::size() const {
    return nrElements;
}
//O(1)

bool Map::isEmpty() const {

    return nrElements == 0;
}
//O(1)

MapIterator Map::iterator() const {
    return MapIterator(*this); //this pointer is used to pass the current object to the iterator
}
//O(1)