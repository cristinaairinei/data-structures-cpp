#pragma once
//DO NOT INCLUDE SMMITERATOR

#include <utility>
#include <vector>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
typedef bool(*Relation)(TKey, TKey);

class SMMIterator;

class SortedMultiMap {
    friend class SMMIterator;

protected:
    struct Node {
        TKey key;
        TValue* values;
        int valSize;
        int valCapacity;
        Node* left; // left child
        Node* right;// right child

        Node(TKey k, TValue v) { // constructor
            key = k;
            valCapacity = 2;
            valSize = 1;
            values = new TValue[valCapacity]; // initialize values array
            values[0] = v; // add the first value
            left = right = nullptr;
        }

        ~Node() {
            delete[] values;
        }
    };

    Node* root;
    Relation relation; //to maintain the order of keys
    int totalSize;



    // adds a value to the node's values array, resizing if necessary
    void addValue(Node* node, TValue v);
    // removes a value from the node's values array
    bool removeValue(Node* node, TValue v);
    // inserts a new node into the tree
    Node* insert(Node* node, TKey c, TValue v);//RECURSIVE
    // removes a node with the specified key and value
    Node* removeNode(Node* node, TKey c, TValue v, bool& removed);//RECURSIVE
    // searches for the minimum node in the subtree
    Node* findMin(Node* node);
    // destroys the entire tree
    void destroy(Node* node);//RECURSIVE

public:

    SortedMultiMap(Relation r);

    // adds a key-value pair to the map
    void add(TKey c, TValue v);

    // searches for all values associated with a key
    std::vector<TValue> search(TKey c) const;

    // removes a key-value pair from the map
    bool remove(TKey c, TValue v);

    // returns the size of the map
    int size() const;

    // checks if the map is empty
    bool isEmpty() const;

    // destroys the map
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();

    // adds all key-value pairs from another SortedMultiMap if the keys are not already present
    int addIfNotPresent(SortedMultiMap& m);
};
