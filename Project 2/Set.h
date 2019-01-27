//
// Created by Matthew Pombo on 2019-01-23.
//

#ifndef PROJECT_2_SET_H
#define PROJECT_2_SET_H

using ItemType = std::string;

class Set
{
public:
    Set();
    ~Set();
    Set(const Set& src);
    Set& operator=(const Set& src);
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    void dump() const;

private:
    struct Node {
        ItemType value;
        Node*    next;
        Node*    prev;
    };

    // the head is a dummy node, never has any values but gets rid of special cases
    Node* dummyHead;
    Node* tail;
    int   m_size;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);


#endif //PROJECT_2_SET_H
