//
// Created by Matthew Pombo on 2019-01-23.
//

#ifndef PROJECT_2_SET_H
#define PROJECT_2_SET_H

using namespace std;
using ItemType = string;

struct Node {
    ItemType value;
    Node* next;
};

class Set
{
public:
    Set();
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);

private:
    Node* head;
};


#endif //PROJECT_2_SET_H
