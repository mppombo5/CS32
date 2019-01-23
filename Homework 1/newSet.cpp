//
// Created by Matthew Pombo on 2019-01-22.
//
#include <iostream>
#include <string>
#include "newSet.h"
using namespace std;

Set::Set() {
    m_size = 0;
    m_max = DEFAULT_MAX_ITEMS;
    m_set = new ItemType[m_max];
}

Set::Set(int max) {
    m_size = 0;
    m_max = max;
    m_set = new ItemType[m_max];
}

Set::~Set() {
    delete [] m_set;
}

Set::Set(const Set& source) {
    m_size = source.m_size;
    m_max = source.m_max;
    m_set = new ItemType[m_size];

    for (int k = 0; k < m_size; k++) {
        m_set[k] = source.m_set[k];
    }
}

Set& Set::operator=(const Set& src) {
    if (&src == this)
        return *this;
    delete [] m_set;
    m_size = src.m_size;
    m_max = src.m_max;
    m_set = new ItemType[m_size];
    for (int k = 0; k < m_size; k++) {
        m_set[k] = src.m_set[k];
    }
    return *this;
}

bool Set::empty() const {
    return (m_size == 0);
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    if (m_size >= m_max)
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

    ItemType item;
    // just do the same comparison each loop
    for (int j = 0; j < m_size; j++) {
        item = m_set[j];
        int counter = 0;
        for (int k = 0; k < m_size; k++) {
            if (k == j)
                continue;
            else {
                if (m_set[k] < item)
                    counter++;
            }
        }
        if (counter == i)
            break;
    }

    value = item;
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
    int tempSize, tempMax;

    tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;

    tempMax = m_max;
    m_max = other.m_max;
    other.m_max = tempMax;
}

void Set::dump() const {
    for (int k = 0; k < m_size; k++) {
        cerr << m_set[k] << endl;
    }
}