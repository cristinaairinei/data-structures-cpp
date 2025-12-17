#include "SortedMultiMap.h"
#include "SMMIterator.h"

#include <vector>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    root = nullptr;
    relation = r;
    totalSize = 0;
}
//complexity of the constructor is O(1)

void SortedMultiMap::addValue(Node* node, TValue v) {
    if (node->valSize == node->valCapacity) {
        node->valCapacity *= 2; //we need to resize the values array
        TValue* newValues = new TValue[node->valCapacity];
        for (int i = 0; i < node->valSize; i++) {
            newValues[i] = node->values[i];
        }
        delete[] node->values;
        node->values = newValues; // Update the values pointer to the new array
    }
    node->values[node->valSize++] = v; // Add the new value to the values array at the first empty position in the resized array
}
//complexity teta(1) best case, teta(n) worst case
//total complexity O(n)


SortedMultiMap::Node* SortedMultiMap::insert(Node* node, TKey c, TValue v) {
    if (node == nullptr) {
        totalSize++;
        return new Node(c, v);
    }

    if (node->key == c) {
        addValue(node, v); // If the key already exists, add the value to the existing node
        totalSize++;
    } else if (relation(c, node->key)) {
        node->left = insert(node->left, c, v);
    } else {
        node->right = insert(node->right, c, v);
    }

    return node;
}
//it can be teta(n) in the worst case, but on average it is teta(log n) for balanced trees
//total O(n)

void SortedMultiMap::add(TKey c, TValue v) {
    root = insert(root, c, v);
}
//total O(n), where n is the height of the tree

vector<TValue> SortedMultiMap::search(TKey c) const {
    Node* current = root; // Start from the root of the tree
    while (current != nullptr) {
        if (current->key == c) {
            return vector<TValue>(current->values, current->values + current->valSize); // If the key matches, return the values associated with it
        } else if (relation(c, current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }//we try to find by c
    }
    return {};
}
//complexity of the search function is O(n) total complexity

bool SortedMultiMap::removeValue(Node* node, TValue v) {
    for (int i = 0; i < node->valSize; i++) {  // Search for the value in the values array
        if (node->values[i] == v) {
            for (int j = i; j < node->valSize - 1; j++) {
                node->values[j] = node->values[j + 1]; // Shift values to the left
            }//we delete the node
            node->valSize--;
            return true;
        }
    }
    return false;
}
// teta(1)bc, teta(n)wc,  where n is the number of values in the node, total complexity O(n)


SortedMultiMap::Node* SortedMultiMap::findMin(Node* node) {
    while (node && node->left != nullptr)
        node = node->left; // Traverse to the leftmost node because it contains the minimum key
    return node;
}
//complexity of the findMin function is O(n) where n is the height of the tree, as it traverses to the leftmost node

SortedMultiMap::Node* SortedMultiMap::removeNode(Node* node, TKey c, TValue v, bool& removed) {
    if (node == nullptr)
        return nullptr; //recursive base case

    if (node->key == c) {
        if (removeValue(node, v)) {
            removed = true;
            totalSize--;
            if (node->valSize == 0) {// If the node has no values left, we need to remove the node itself
                if (!node->left && !node->right) {// If the node has no children, delete it(frunza)
                    delete node;
                    return nullptr;
                } else if (!node->left) {
                    Node* temp = node->right; // If the node has only a right child, return that child(e inlocuit cu copilul drept)
                    delete node;
                    return temp;
                } else if (!node->right) { // If the node has only a left child, return that child(e inlocuit cu copilul stang)
                    Node* temp = node->left;
                    delete node;
                    return temp;
                } else { //we need to find the minimum node in the right subtree to replace the current node(or the max in the left subtree)
                    Node* minNode = findMin(node->right);
                    node->key = minNode->key;
                    delete[] node->values
                    node->valSize = minNode->valSize;
                    node->valCapacity = minNode->valCapacity;
                    node->values = new TValue[minNode->valCapacity];
                    for (int i = 0; i < minNode->valSize; i++) {
                        node->values[i] = minNode->values[i];//we copy the values from the minimum node to the current node
                    }
                    node->right = removeNode(node->right, minNode->key, minNode->values[0], removed);  // Remove the minimum node from the right subtree
                }
            }
        }
    } else if (relation(c, node->key)) {
        node->left = removeNode(node->left, c, v, removed);
    } else {
        node->right = removeNode(node->right, c, v, removed);
    } // If the key is not found, continue searching in the left or right subtree
//this is the recursion
    return node;
}
//complexity is teta(1) best case, teta(n), worst case =>total case O(n)

bool SortedMultiMap::remove(TKey c, TValue v) {
    bool removed = false;
    root = removeNode(root, c, v, removed); //we atrib the new root to the root of the tree because the root can change after the removal
    return removed;
}
//complexity of the remove function is O(n)

int SortedMultiMap::size() const {
    return totalSize;
}
//complexity of the size function is O(1)

bool SortedMultiMap::isEmpty() const {
    return totalSize == 0;
}
//complexity of the size and isEmpty functions is O(1)

void SortedMultiMap::destroy(Node* node) {
    if (node) { // If the node is not null, recursively destroy its children
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}
//complexity of the destroy function is O(n)

SortedMultiMap::~SortedMultiMap() {
    destroy(root);
}
//complexity of the destructor is O(n) where n is the number of nodes in the tree

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}
//complexity of the iterator function is O(1)


//NEW FUNCTION
//
int SortedMultiMap::addIfNotPresent(SortedMultiMap& m) {
    int addedCount = 0;
    SMMIterator it = m.iterator();
    it.first();//we start at the first
    while (it.valid()) { // Iterate through each element in the provided SortedMultiMap
        TElem elem = it.getCurrent();
        TKey key = elem.first;
        TValue value = elem.second;

        if (this->search(key).empty()) { //if the vector of values is empty
            this->add(key, value);
            addedCount++;
        }

        it.next();
    }
    return addedCount;
}
//complexity is O(n*m) where n is the size of the current SortedMultiMap and m is the size of the provided SortedMultiMap
//O(n log m)