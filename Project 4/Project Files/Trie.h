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
        std::vector<ValueType> values;
        std::vector<Node*> children;
        std::vector<char> childrenLabels; // directly linked to children: the subscripts will refer to the same one
    };
    Node* m_root;

    // to be used in the destructor and reset() to free the whole trie
    void freeTrie(Node* p);
    void insertFromNode(Node* p, const std::string& key, int keyPos, const ValueType& value);
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
    // this *should* never happen, but who knows? I certainly don't.
    if (keyPos > key.size())
        return;

    char keyChar = key[keyPos];

    // if the children vector is empty, we need to create new nodes
    if (p->children.empty()) {
        // if every char in the string has been considered, add the label and the value into this node
        if (keyPos == key.size()) {
            p->values.push_back(value);
            return;
        }
        // if there are still more char's from the string to be added,
        // add a new node to children and the correct char to childrenLabels
        else {
            Node* n = new Node;
            p->children.push_back(new Node);
            p->childrenLabels.push_back(keyChar);
            insertFromNode(n, key, ++keyPos, value);
        }
    }
    // the children vector is not empty, so we need more checks
    else {
        std::vector<char>::iterator it = p->childrenLabels.find(p->childrenLabels.begin(), p->childrenLabels.end(), keyChar);
        // the char was found in childrenLabels, so insert from the corresponding node
        if (it != p->childrenLabels.end()) {
            // this gives the position of childrenLabels with with the char, but only for vectors
            int charPos = (int) (it - p->childrenLabels.begin());
            insertFromNode(p->children[charPos], key, ++keyPos, value);
        }
        // char was not found in childrenLabels, so insert a new node and go from there
        else {
            Node* n = new Node;
            p->children.push_back(n);
            p->childrenLabels.push_back(keyChar);
            insertFromNode(n, key, ++keyPos, value);
        }
    }
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
    if (value.empty())
        return;

    // we did all the dirty work in insertFromNode with recursion and whatnot, so just call it here
    insertFromNode(m_root, key, 0, value);
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const {

}

#endif // TRIE_INCLUDED










































