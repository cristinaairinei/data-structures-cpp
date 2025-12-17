#include "BagIterator.h"
#include "Bag.h"
#include <exception>

BagIterator::BagIterator(const Bag& b) : bag(b) { // constructor
    first();
}

void BagIterator::first() {
    currentBucket = 0;
    currentNode = nullptr;
    freqIndex = 0;

    while (currentBucket < bag.capacity && bag.head[currentBucket] == nullptr)  //find the first non-empty bucket
        currentBucket++;

    if (currentBucket < bag.capacity)
        currentNode = bag.head[currentBucket]; // set the current node to the first non-empty bucket
    else
        currentNode = nullptr;
}
//complexity: O(n)
void BagIterator::next() {
    if (!valid())
        throw std::exception();

    freqIndex++;//advance the frequency index
    if (freqIndex < currentNode->pair.second)
        return; // we are still in the same node

    // Move to next node in chain or next non-empty bucket
    freqIndex = 0;
    currentNode = currentNode->next;

    while (currentNode == nullptr && currentBucket + 1 < bag.capacity) {
        currentBucket++;
        currentNode = bag.head[currentBucket];
    }
}
//complexity: O(n)

bool BagIterator::valid() const {
    return currentNode != nullptr;
}
//complexity: O(1)

int BagIterator::getCurrent() const {
    if (!valid())
        throw std::exception();
    return currentNode->pair.first;
}
//complexity: O(1)

void BagIterator::previous() {
    if (!valid()) {
        return;
    }

    if (freqIndex > 0) {  //iteratorul parcurge frecv aceluiasi el
        freqIndex--;
        return;
    }

    Bag::Node* prevNode = nullptr;
    int prevBucket = -1;
    int prevFreqIndex = 0;

    for (int i = 0; i <= currentBucket; ++i) {
        Bag::Node* node = bag.head[i]; // iterate through the buckets
        while (node != nullptr) {
            if (i < currentBucket || node != currentNode) {
                prevNode = node;
                prevBucket = i;
                prevFreqIndex = node->pair.second - 1;
            }
            node = node->next;
        }
    }

    if (prevNode == nullptr) { // no previous element, we are at the first element, the iterator is invalid
        currentNode = nullptr;
        currentBucket = -1;
        freqIndex = -1;
        return;
    }
//we have to set the iterator to the previous element
    currentBucket = prevBucket;
    currentNode = prevNode;
    freqIndex = prevFreqIndex;
}
//complexity: teta (1) in the best case when the iterator is at the first element
//complexity: teta(n) in the worst case when the iterator is at the last element
//complexity: O(n) in the average case when the iterator is in the middle of the bag