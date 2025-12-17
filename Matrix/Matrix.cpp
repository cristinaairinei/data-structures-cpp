#include "Matrix.h"
#include <stdexcept>
#include <iostream>

using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {
    this->numberOfLines = nrLines; //this-> is for the class variables
    this->nrCols = nrCols;
    this->size = 0;
    this->capacity = 10;  // Initial array capacity O(1) for the variables
    this->elements = new Triple[this->capacity];  // Dynamically allocating memory for the elements array O(n)
}

Matrix::~Matrix() {  //destructor
    delete[] this->elements; // Deallocating the memory for the elements array so TEta(1)
}

int Matrix::nrLines() const {
    return this->numberOfLines;
}

int Matrix::nrColumns() const {
    return this->nrCols; // teta O(1)
}

TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= this->numberOfLines || j < 0 || j >= this->nrCols) {
        throw out_of_range("Invalid index"); //out of the bounds
    }

    for (int k = 0; k < this->size; ++k) {
        if (this->elements[k].line == i && this->elements[k].col == j) {
            return this->elements[k].value; //teta of 1/ or teta of n
        }
    }

    return NULL_TELEM; //if not found
}

TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= this->numberOfLines || j < 0 || j >= this->nrCols) {
        throw out_of_range("Invalid index");
    }

    for (int k = 0; k < this->size; ++k) {
        if (this->elements[k].line == i && this->elements[k].col == j) { // O(n)
            TElem old = this->elements[k].value; //pastram valoarea
            if (e == NULL_TELEM) {
                for (int l = k; l < this->size - 1; ++l) {
                    this->elements[l] = this->elements[l + 1];  //we remove the triplet and shift O(n)
                }
                --this->size;
            } else {
                this->elements[k].value = e; //update the value
            }
            return old;
        }
    }

    if (e != NULL_TELEM) {
        if (this->size == this->capacity) {
            //We resize if the array is full
            this->resize(); //O(n) is the resize
        }

        this->elements[this->size].line = i;
        this->elements[this->size].col = j;
        this->elements[this->size].value = e;
        ++this->size; // is O(1)

        for (int k = this->size - 1; k > 0 &&
            (this->elements[k].line < this->elements[k - 1].line ||
            (this->elements[k].line == this->elements[k - 1].line && this->elements[k].col < this->elements[k - 1].col)); --k) {
            swap(this->elements[k], this->elements[k - 1]); //insertion sort O(n)
        }
    }

    return NULL_TELEM;
}

void Matrix::resize() { //O(n) bc we copy the elements
    this->capacity *= 2;
    Triple* newElements = new Triple[this->capacity]; // Dynamically allocating a new array with double the capacity
    for (int i = 0; i < this->size; ++i) {
        newElements[i] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = newElements;
}

pair<int, int> Matrix::positionOf(TElem e) const {
    for (int k = 0; k < this->size; ++k) {
        if (this->elements[k].value == e) {
            return {this->elements[k].line, this->elements[k].col}; //O(1) when is on the first pos or O(n) when is at the end

        }
    }
    return {-1, -1}; // Element not found
}
