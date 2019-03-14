//
// Created by Matthew Pombo on 2019-03-11.
//

#include "Trie.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
using namespace std;

int main() {
    /*Trie<int> iTrie;
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
    }*/

    string filename = "/Users/mpombo/Desktop/Q2 Classes/CS 32/Projects/Project 4/data/Halobacterium_jilantaiense.txt";

    ifstream infile(filename);
    if (!infile) {
        cout << "Cannot find infile!" << endl;
        return 1;
    }
    vector<Genome> genomes;
    bool success = Genome::load(infile, genomes);

    if (success) {
        cout << "Loaded " << genomes.size() << " genomes successfully:" << endl;
        for (int i = 0; i < genomes.size(); i++) {
            cout << genomes[i].name() << ", length " << genomes[i].length() << endl;
        }
        return 0;
    }
    else {
        cout << "Error loading genome data." << endl;
        return 1;
    }

}