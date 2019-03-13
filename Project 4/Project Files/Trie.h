#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <algorithm>

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    // don't add any other public members
private:
    // structure for node - each one must have a list of values and a list of children, and a list of the children's labels
    struct Node {
        char label;
        std::vector<ValueType> values;
        std::vector<Node*> children;
    };
    Node* m_root;

      // to be used in the destructor and reset() to free the whole trie
    void freeTrie(Node* p);
    void insertFromNode(Node* p, const std::string& key, int keyPos, const ValueType& value);
    void findFromNode(Node*p, const std::string& key, int keyPos, bool exactMatchOnly,
                      std::vector<ValueType>& targetVector);

};

template<typename ValueType>
Trie<ValueType>::Trie() {
    m_root = new Node;
}

template <typename ValueType>
void Trie<ValueType>::freeTrie(Trie<ValueType>::Node* p) {
    if (! p->children.empty()) {
        for (int i = 0; i < p->children.size(); i++) {
            freeTrie(p->children[i]);
        }
    }
    delete p;
}

template<typename ValueType>
Trie<ValueType>::~Trie() {
    freeTrie(m_root);
}

template<typename ValueType>
void Trie<ValueType>::reset() {
    freeTrie(m_root);
    m_root = new Node;
}

template <typename ValueType>
void Trie<ValueType>::insertFromNode(Trie<ValueType>::Node *p, const std::string &key, int keyPos, const ValueType &value) {
    if (keyPos > key.size())
        return;

    // we've reached the end of the string, so insert the value into the current node
    if (keyPos == key.size()) {
        p->values.push_back(value);
        return;
    }

    // from here on, we can work under the assumption that there are still
    // characters left in key (i.e. keyPos is less than key's size)

    char keyChar = key[keyPos];

    // if the children vector is empty, we need to create new nodes
    if (p->children.empty()) {
        // add a new node to children and the correct char to childrenLabels
        Node* n = new Node;
        n->label = keyChar;
        p->children.push_back(n);
        insertFromNode(n, key, ++keyPos, value);
    }
    // the children vector is not empty, so we need more checks
    else {
        int i;
        for (i = 0; i < p->children.size(); i++) {
            Node* cur = p->children[i];
            // if the children vector contains a child with label keyChar,
            // break out of the loop; 'i' will have the index of said child
            if (cur->label == keyChar)
                break;
        }

        // the easiest way to check if keyChar was found is whether i is the size of the vector.
        if (i != p->children.size())
            insertFromNode(p->children[i], key, ++keyPos, value);
        // char was not found in the children, so insert a new node and go from there
        else {
            Node* n = new Node;
            n->label = keyChar;
            p->children.push_back(n);
            insertFromNode(n, key, ++keyPos, value);
        }
    }
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
    // root node shouldn't have values
    if (key.empty())
        return;

    // we did all the dirty work in insertFromNode with recursion and whatnot, so just call it here
    insertFromNode(m_root, key, 0, value);
}

template <typename ValueType>
void Trie<ValueType>::findFromNode(Trie<ValueType>::Node *p, const std::string &key, int keyPos, bool exactMatchOnly,
                                   std::vector<ValueType>& targetVector) {
    if (keyPos > )
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const {

}

#endif // TRIE_INCLUDED










































