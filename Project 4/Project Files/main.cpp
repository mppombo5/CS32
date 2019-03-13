//
// Created by Matthew Pombo on 2019-03-11.
//

#include "Trie.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    Trie<int> iTrie;
    iTrie.insert("ACTGGTA", 42);
    iTrie.insert("ACTGGTA", 3);
    iTrie.insert("ACTGGTAC", 93);
    iTrie.insert("ACTGTTA", 53);
    iTrie.insert("ATTGGTA", 44);
    iTrie.insert("GCTGGTA", 78);

    bool exact = true;
    bool notExact = false;

    vector<int> results = iTrie.find("ACTGGTA", exact);
    for (int i = 0; i < results.size(); i++) {
        cout << results[i] << ' ';
    }
}