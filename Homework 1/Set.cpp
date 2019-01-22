//
// Created by Matthew Pombo on 2019-01-16.
//

#include <string>

#include "Set.h"
using namespace std;

Set::Set() {
    m_size = 0;
}

bool Set::empty() const {
    return (m_size == 0);
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    if (m_size >= 250)
        return false;

    for (int k = 0; k < m_size; k++) {
        if (m_set[k] == value)
            return false;
    }

    m_set[m_size] = value;
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value) {
    bool removed = false;
    for (int k = 0; k < m_size; k++) {
        if (m_set[k] == value) {
            removed = true;
            for (; k < m_size - 1; k++) {
                m_set[k] = m_set[k+1];
            }
            m_size--;
        }
        if (removed)
            break;
    }
    return removed;
}

bool Set::contains(const ItemType& value) const {
    for (int k = 0; k < m_size; k++) {
        if (m_set[k] == value)
            return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const {
    if ( !(0 <= i && i < m_size) )
        return false;

    ItemType word;
    // just do the same comparison each loop
    for (int j = 0; j < m_size; j++) {
        word = m_set[j];
        int counter = 0;
        for (int k = 0; k < m_size; k++) {
            if (k == j)
                continue;
            else {
                if (m_set[k] < word)
                    counter++;
            }
        }
        if (counter == i)
            break;
    }

    value = word;
    return true;
}

void Set::swap(Set& other) {
    int greater = m_size;
    if (other.size() > m_size)
        greater = other.size();
    for (int i = 0; i < greater; i++) {
        ItemType temp = m_set[i];
        m_set[i] = other.m_set[i];
        other.m_set[i] = temp;
    }
    int temp;
    temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;
}

void Set::dump() const {
    for (int k = 0; k < m_size; k++) {
        cerr << m_set[k] << endl;
    }
}