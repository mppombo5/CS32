//
// Created by Matthew Pombo on 2019-03-11.
//

#include "Trie.h"
#include "provided.h"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
using namespace std;

int main1() {
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

    string filename = "../data/TestData.txt";
    string filename2 = "../data/Ferroglobus_placidus.txt";

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
    }
    else {
        cout << "Error loading genome data in first file." << endl;
        return 1;
    }

    Genome g1 = genomes[0];
    string f1, f2, f3, f4;
    bool result1 = g1.extract(0, 5, f1);
    bool result2 = g1.extract(74, 6, f2);
    bool result3 = g1.extract(74, 7, f3);
    bool result4 = g1.extract(0, 1, f4);
    assert(result1 && f1 == "GCTCG");
    assert(result2 && f2 == "CTGGGA");
    assert(!result3);
    assert(result4 && f4 == "G");

    ifstream infile2(filename2);
    if (!infile2) {
        cout << "Cannot find the second file!" << endl;
        return 1;
    }
    success = Genome::load(infile2, genomes);

    if (success) {
        cout << "Loaded " << genomes.size() << " genomes successfully:" << endl;
        for (int i = 0; i < genomes.size(); i++) {
            cout << genomes[i].name() << ", length " << genomes[i].length() << endl;
        }
    }
    else {
        cout << "Error loading genome data in second file." << endl;
        return 1;
    }
    cout << "All tests passed!" << endl;

    for (int i = 0, j = 1; i < 10; i++, j++) {
        cout << i << ' ' << j << endl;
    }
}