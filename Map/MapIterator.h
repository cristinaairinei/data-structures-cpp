#pragma once
#include "Map.h"
class MapIterator
{
    friend class Map;
private:
    const Map& map; // reference to the map on which we iterate
    int current; // current pos

    MapIterator(const Map& m);
public:
    void first();
    void next();
    TElem getCurrent();
    bool valid() const;
    void jumpBackward(int k); // jumps backward k positions in the list
};
