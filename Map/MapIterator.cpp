#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

MapIterator::MapIterator(const Map& d) : map(d) { // constructor
    current = map.head;
}
//O(1), total complexity

void MapIterator::first() {
    current = map.head;
} //O(1)

void MapIterator::next() {
    if (!valid()) {
        throw exception();
    }
    current = map.nodes[current].next;
}
//O(1)

TElem MapIterator::getCurrent() {
    if (!valid()) {
        throw exception();
    }
    return map.nodes[current].info; //as key-value pair
}
//O(1)

bool MapIterator::valid() const {
    return current != -1;
}
//O(1)

void MapIterator::jumpBackward(int k) {
    if (!valid()) {
        throw std::exception();  // Iterator is invalid
    }

    if (k <= 0) {
        throw std::exception();
    }

    for (int i = 0; i < k; ++i) {
        if (current == -1 || map.nodes[current].prev == -1) {
            current = -1; //bc there are not enough elements to jump backward
            return;
        }
        current = map.nodes[current].prev;
    }
}

//if k==1 Teta(1) if k is large teta(k), total complexity O(k)