//
// Created by Matthew Pombo on 2019-01-23.
//

// TODO: check for aliasing in unite and subtract

#include <iostream>
#include <string>
#include "Set.h"
using namespace std;

Set::Set() {
    // create head node, set next and previous to nullptr
    dummyHead = new Node;
    dummyHead->next = nullptr;
    dummyHead->prev = nullptr;
    // dummyHead->value = "E R R O R ! This better not pop up anywhere.";
    tail = dummyHead;
    m_size = 0;
}

Set::~Set() {
    // start deleting from head's next, delete the previous and eventually you'll just be left with tail
    for (Node* p = dummyHead->next; p != nullptr; p = p->next)
        delete p->prev;
    delete tail;
}

Set::Set(const Set& src) {
    // the first part is exactly the same as the normal constructor
    dummyHead = new Node;
    dummyHead->next = nullptr;
    dummyHead->prev = nullptr;
    //dummyHead->value = "E R R O R ! This better not pop up anywhere.";
    tail = dummyHead;
    m_size = 0;
    // this is the only part that's different than the default constructor,
    // copy all the values in and it should work out fine... right?
    for (Node* p = src.dummyHead->next; p != nullptr; p = p->next) {
        insert(p->value);
    }
}

Set& Set::operator=(const Set& src) {
    if (&src == this)
        return *this;

    // copy and paste the destructor, start from scratch
    for (Node* p = dummyHead->next; p != nullptr; p = p->next)
        delete p->prev;
    delete tail;

    // then do the stuff from the copy constructor
    dummyHead = new Node;
    dummyHead->next = nullptr;
    dummyHead->prev = nullptr;
    //dummyHead->value = "E R R O R ! This better not pop up anywhere.";
    tail = dummyHead;
    for (Node* p = src.dummyHead->next; p != nullptr; p = p->next) {
        insert(p->value);
    }
    m_size = src.m_size;
    return *this;
}

bool Set::empty() const {
    return (dummyHead->next == nullptr);
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    // first check if the value is already in the list
    if (contains(value))
        return false;
    Node* p = new Node;
    p->value = value;
    Node* k = tail;
    k->next = p;
    p->next = nullptr;
    p->prev = k;
    tail = p;
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value) {
    if (empty())
        return false;

    for (Node* p = dummyHead->next; p != nullptr; p = p->next) {
        // traverse the list and see if any of the values match
        if (p->value == value) {
            Node* target = p;
            p = p->prev;
            p->next = target->next;
            // this checks if target is the last value in the list
            if (target->next != nullptr)
                target->next->prev = p;
            else
                tail = p;
            delete target;
            m_size--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const {
    // simple traversal and comparison
    for (Node* p = dummyHead->next; p != nullptr; p = p->next) {
        if (p->value == value)
            return true;
    }
    return false;
}

bool Set::get(int pos, ItemType& value) const {
    if ( !(0 <= pos && pos < m_size))
        return false;

    // a lot of this is just copied and modified from homework 1 to fit into sets
    // the general idea is that you count up how many values are less than value,
    // if it matches pos then you're good to go
    for (Node* p = dummyHead->next; p != nullptr; p = p->next) {
        int counter = 0;
        for (Node* k = dummyHead->next; k != nullptr; k = k->next) {
            if (p != k && k->value < p->value)
                counter++;
        }
        if (counter == pos) {
            value = p->value;
            return true;
        }
    }
    return false;
}

void Set::swap(Set& other) {
    std::swap(*this, other);
    // my first implementation of this took somewhere around 40-50 lines of code.
    // it's bittersweet.
}

void Set::dump() const {
    if (empty()) {
        cerr << "This bitch empty; Y E E T" << endl;
        return;
    }
    for (Node* p = dummyHead->next; p != nullptr; p = p->next) {
        cerr << p->value << endl;
    }
}

void unite(const Set& s1, const Set& s2, Set& result) {
    // first thing to do is make result an empty set
    Set temp;
    // then go through and just add  each thing  from s1 and s2, insert will prevent duplicates
    for (int i = 0; i < s1.size(); i++) {
        ItemType item;
        s1.get(i, item);
        temp.insert(item);
    }
    for (int i = 0; i < s2.size(); i++) {
        ItemType item;
        s2.get(i, item);
        temp.insert(item);
    }
    result = temp;
}

void subtract(const Set& s1, const Set& s2, Set& result) {
    // again, first make sure result is empty
    Set temp;
    for (int i = 0; i < s1.size(); i++) {
        ItemType item;
        s1.get(i, item);
        if (!s2.contains(item))
            temp.insert(item);
    }
    result = temp;
}