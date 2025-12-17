#pragma once

#include <exception>
#include <utility>
typedef int TElem;
#define NULL_TELEM 0


struct Triple {
    int line;
    int col;
    TElem value;
};

class Matrix {
private:
    int numberOfLines;
    int nrCols;
    int capacity;
    int size;
    Triple* elements;  // Dynamically allocated array for storing the triplets

    void resize();

public:

    Matrix(int nrLines, int nrCols); // Constructor

    ~Matrix(); // Destructor

    int nrLines() const;

    int nrColumns() const;

    TElem element(int i, int j) const;

    TElem modify(int i, int j, TElem e);

   std:: pair<int, int> positionOf(TElem e) const;
};
