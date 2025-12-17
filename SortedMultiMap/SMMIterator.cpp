#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& m) : map(m) {
    stackCapacity = 100;
    stackSize = 0;
    stack = new SortedMultiMap::Node*[stackCapacity]; // stack to hold nodes during in-order traversal
    valueIndices = new int[stackCapacity];
    first();
}
//complexity of the constructor is O(1)

void SMMIterator::resizeStack() {
    stackCapacity *= 2;
    auto** newStack = new SortedMultiMap::Node*[stackCapacity];
    int* newIndices = new int[stackCapacity];
    for (int i = 0; i < stackSize; i++) {
        newStack[i] = stack[i];
        newIndices[i] = valueIndices[i];
    }
    delete[] stack;
    delete[] valueIndices;
    stack = newStack;
    valueIndices = newIndices;
}
//complexity of resizeStack is O(n)

void SMMIterator::pushLeft(SortedMultiMap::Node* node) { // pushes all left children of the node onto the stack for in-order traversal
    while (node != nullptr) {
        if (stackSize == stackCapacity) {
            resizeStack();
        }
        stack[stackSize] = node; // push the current node onto the stack
        valueIndices[stackSize] = 0;
        stackSize++;
        node = node->left;// move to the left child
    }
}
// complexity of pushLeft is O(n) where n is the height of the tree, as it traverses to the leftmost node

void SMMIterator::first() {
    stackSize = 0;
    pushLeft(map.root);// start from the root of the tree and push all left children onto the stack
}
// complexity of first is O(n) where n is the height of the tree

void SMMIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    valueIndices[stackSize - 1]++; // increment the index of the current value in the current node
    SortedMultiMap::Node* currentNode = stack[stackSize - 1];

    if (valueIndices[stackSize - 1] >= currentNode->valSize) { // if we have traversed all values in the current node
        stackSize--;
        pushLeft(currentNode->right);// push all left children of the right child onto the stack
    }
}
//complexity of next is O(n), total complexity where n is the height of the tree,
//as it may traverse to the right child and then push all left children onto the stack

bool SMMIterator::valid() const {
    return stackSize > 0;
}
// complexity of valid is O(1)

TElem SMMIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception();
    }
    SortedMultiMap::Node* currentNode = stack[stackSize - 1];  // get the current node from the top of the stack
    return std::make_pair(currentNode->key, currentNode->values[valueIndices[stackSize - 1]]);
}
// complexity of getCurrent is O(1), as it simply accesses the top element of the stack and returns the key-value pair

SMMIterator::~SMMIterator() {
    delete[] stack;
    delete[] valueIndices;
}

