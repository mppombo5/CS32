//
// Created by Matthew Pombo on 2019-01-22.
//
#include <iostream>
#include <cassert>
#include "newSet.h"
using namespace std;

int main() {
    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = { "hello", "there", "general", "kenobi", "you", "are" };

    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v[k]));

    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));

    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5])  &&  b.insert(v[5]));

    cout << "All tests passed!" << endl;

    return 0;
}