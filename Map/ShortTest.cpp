#include "ShortTest.h"
#include <assert.h>
#include "Map.h"
#include "MapIterator.h"


void testAll() {
    Map m;
    assert(m.isEmpty() == true);
    assert(m.size() == 0); //add elements
    assert(m.add(5,5)==NULL_TVALUE);
    assert(m.add(1,111)==NULL_TVALUE);
    assert(m.add(10,110)==NULL_TVALUE);
    assert(m.add(7,7)==NULL_TVALUE);
    assert(m.add(1,1)==111); //checks if the value is updated and the old value is returned
    assert(m.add(10,10)==110);
    assert(m.add(-3,-3)==NULL_TVALUE);
    assert(m.size() == 5);
    assert(m.search(10) == 10);//checks if the search function works
    assert(m.search(16) == NULL_TVALUE); //bc 16 is not in the map
    assert(m.remove(1) == 1);
    assert(m.remove(6) == NULL_TVALUE);
    assert(m.size() == 4); //checks is the elements are added and removed correctly


    TElem e;
    MapIterator id = m.iterator();
    id.first();
    int s1 = 0, s2 = 0;
    while (id.valid()) {
        e = id.getCurrent();
        s1 += e.first; //sum of keys
        s2 += e.second;//sum of values
        id.next();
    }
    assert(s1 == 19);
    assert(s2 == 19);

}


