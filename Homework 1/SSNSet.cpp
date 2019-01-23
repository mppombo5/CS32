//
// Created by Matthew Pombo on 2019-01-22.
//
#include <iostream>
#include "SSNSet.h"

SSNSet::SSNSet() = default;

bool SSNSet::add(unsigned long ssn) {
    return m_set.insert(ssn);
}

int SSNSet::size() const {
    return m_set.size();
}

void SSNSet::print() const {
    for (int k = 0; k < m_set.size(); k++) {
        ItemType s;
        m_set.get(k, s);
        cout << s << endl;
    }
}