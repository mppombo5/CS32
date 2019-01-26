//
// Created by Matthew Pombo on 2019-01-23.
//

#ifndef PROJECT_2_SET_H
#define PROJECT_2_SET_H

using ItemType = std::string;

class Set
{
public:
    ///////////////////////////////////////////////
    // REMEMBER TO REMOVE THIS BEFORE TURNING IN //
    ///////////////////////////////////////////////
    void dump() const;
    void dumpBackwards() const;

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

private:
    struct Node {
        ItemType value;
        Node*    next;
        Node*    prev;
    };
    // dummy node, never has any values but gets rid of special cases
    Node* dummyHead;
    Node* tail;
    int   m_size;


};


#endif //PROJECT_2_SET_H
