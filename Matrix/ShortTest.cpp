#include <assert.h>
#include "Matrix.h"


using namespace std;

void testAll() {
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    m.modify(1, 1, 5);
    assert(m.element(1, 1) == 5);
    TElem old = m.modify(1, 1, 6);
    assert(m.element(1, 1) == 6);
    assert(m.element(1, 2) == NULL_TELEM);
    assert(old == 5);

    m.modify(1, 1, 5);
    m.modify(2, 2, 10);

    pair<int, int> pos5 = m.positionOf(5);
    assert(pos5.first == 1 && pos5.second == 1);

    pair<int, int> pos10 = m.positionOf(10);
    assert(pos10.first == 2 && pos10.second == 2);

    pair<int, int> pos100 = m.positionOf(100);
    assert(pos100.first == -1 && pos100.second == -1);
}
