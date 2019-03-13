//
// Created by Matthew Pombo on 2019-03-11.
//

#include "Trie.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    Trie<int> i;
    i.insert("ACTGGTA", 42);
    i.insert("ACTGGTA", 3);
    i.insert("ACTGTTA", 89);

    Trie<string> s;
    s.insert("GATTACA", "hello");
    s.insert("GATTACA", "there");
    s.insert("GATAACA", "general");
}