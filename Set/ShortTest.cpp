#include <iostream>
#include <cassert>
#include <exception>
#include "Set.h"
#include "SetIterator.h"

void testAll() {
    Set s;
    assert(s.isEmpty() == true);
    assert(s.size() == 0);
    assert(s.add(5));
    assert(s.add(1));
    assert(s.add(10));
    assert(s.add(7));
    assert(s.add(1) == false);
    assert(s.add(10) == false);
    assert(s.size() == 4);
    assert(s.search(10) == true);
    assert(s.search(16) == false);
    assert(s.remove(1) == true);
    assert(s.remove(6) == false);
    assert(s.size() == 3);

    SetIterator it = s.iterator();
    int sum = 0;
    while (it.valid()) {
        sum += it.getCurrent();
        it.next();
    }

    assert(sum == 22); // 5 + 10 + 7 = 22

    SetIterator it2 = s.iterator();
    while (it2.valid()) {
        it2.next();
    }

    try {
        it2.getCurrent();
        assert(false);
    } catch (std::exception&) {
        assert(true);
    }
}


