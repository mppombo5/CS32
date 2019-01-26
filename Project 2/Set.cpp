//
// Created by Matthew Pombo on 2019-01-23.
//

#include <iostream>
#include <string>
#include "Set.h"
using namespace std;

//////////////////////////////////////////////////
/// REMEMBER TO REMOVE THESE BEFORE TURNING IN ///
//////////////////////////////////////////////////
void Set::dump() const {
    if (this->empty()) {
        cerr << "This bitch empty" << endl << "Y E E T" << endl;
        return;
    }
    for (Node* p = dummyHead->next; p != nullptr; p = p->next) {
        cerr << p->value << endl;
    }
}
void Set::dumpBackwards() const {
    if (this->empty()) {
        cerr << "This bitch empty" << endl << "Y E E T" << endl;
        return;
    }
    for (Node* p = tail; p != dummyHead; p = p->prev) {
        cerr << p->value << endl;
    }
}


// after this is fair game



Set::Set() {
    dummyHead = new Node;
    dummyHead->next = nullptr;
    dummyHead->prev = nullptr;
    dummyHead->value = "E R R O R ! This better not pop up anywhere.";
    tail = dummyHead;
    m_size = 0;
}

Set::~Set() {
    Node* p;
    for (p = dummyHead->next; p != nullptr; p = p->next) {
        delete p->prev;
    }
    delete tail;
    cerr << "shit's destroyed" << endl;
}

Set::Set(const Set& src) {
    dummyHead = new Node;
    dummyHead->next = nullptr;
    dummyHead->prev = nullptr;
    dummyHead->value = "E R R O R ! This better not pop up anywhere.";
    tail = dummyHead;
    // this is the only part that's different than the default constructor,
    // copy all the values in and it should work out fine... right?
    for (Node* p = src.dummyHead->next; p != nullptr; p = p->next) {
        insert(p->value);
    }
    m_size = src.m_size;
}

Set& Set::operator=(const Set& src) {
    if (&src == this) {
        return *this;
    }
    // just copy over the stuff from the destructor
    Node* p;
    for (p = dummyHead->next; p != nullptr; p = p->next) {
        delete p->prev;
    }
    delete tail;

    // then do the stuff from the copy constructor
    dummyHead = new Node;
    dummyHead->next = nullptr;
    dummyHead->prev = nullptr;
    dummyHead->value = "E R R O R ! This better not pop up anywhere.";
    tail = dummyHead;
    for (Node* i = src.dummyHead->next; i != nullptr; i = i->next) {
        insert(i->value);
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
    for (Node* p = dummyHead->next; p != nullptr; p = p->next) {
        if (p->value == value)
            return false;
    }
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
    Node* p;
    for (p = dummyHead->next; p != nullptr; p = p->next) {
        if (p->value == value) {
            Node* target = p;
            p = p->prev;
            p->next = target->next;
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
    Node* p;
    // simple traversal and comparison
    for (p = dummyHead->next; p != nullptr; p = p->next) {
        if (p->value == value)
            return true;
    }
    return false;
}

bool Set::get(int pos, ItemType& value) const {
    if ( !(0 <= pos && pos < m_size))
        return false;

    ItemType item;
    // a lot of this is just copied and modified from homework 1 to fit into sets
    // the general idea is that you count up how many values are less than value,
    // if it matches pos then you're good to go
    for (Node* p = dummyHead->next; p != nullptr; p = p->next) {
        item = p->value;
        int counter = 0;
        for (Node* k = dummyHead->next; k != nullptr; k = k->next) {
            if (p == k)
                continue;
            if (k->value < item)
                counter++;
        }
        if (counter == pos)
            break;
    }
    value = item;
    return true;
}

void Set::swap(Set& other) {
    // this takes one line to do, because I correctly implemented the copy constructor and assignment operator.

    std::swap(*this, other);

    // my first implementation of this took somewhere around 40-50 lines of code.
    // it's bittersweet.
}