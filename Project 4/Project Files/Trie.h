#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

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
    // structure for node - each one must have a list of values and a list of children,
    // and a list of the children's labels
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
                      std::vector<ValueType>& targetVector) const;

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
void Trie<ValueType>::insertFromNode(Trie<ValueType>::Node *p, const std::string &key,
                                     int keyPos, const ValueType &value) {
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
        insertFromNode(n, key, keyPos+1, value);
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
            insertFromNode(p->children[i], key, keyPos+1, value);
        // char was not found in the children, so insert a new node and go from there
        else {
            Node* n = new Node;
            n->label = keyChar;
            p->children.push_back(n);
            insertFromNode(n, key, keyPos+1, value);
        }
    }
}

// this just uses insertFromNode as a helper function, with one additional check
template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
    // root node shouldn't have values
    if (key.empty())
        return;

    // we did all the dirty work in insertFromNode with recursion and whatnot, so just call it here
    insertFromNode(m_root, key, 0, value);
}

// void that adds to a vector by reference, helper for find
template <typename ValueType>
void Trie<ValueType>::findFromNode(Trie<ValueType>::Node *p, const std::string &key, int keyPos, bool exactMatchOnly,
                                   std::vector<ValueType>& targetVector) const {
    if (keyPos > key.size())
        return;

    // if we've reached the end of the key string, insert the node's values into targetVector
    if (keyPos == key.size()) {
        for (int i = 0; i < p->values.size(); i++)
            targetVector.push_back(p->values[i]);
        return;
    }

    // the string hasn't reached the end, so return out if there are no children
    if (p->children.empty())
        return;

    // there are still char's left in key, so we need to keep traversing
    char keyChar = key[keyPos];

    // the first character always needs to match, so this is probably easier to
    if (keyPos == 0) {
        // same method as insertFromNode for getting the right index
        int i;
        for (i = 0; i < p->children.size(); i++) {
            Node* cur = p->children[i];
            if (cur->label == keyChar)
                break;
        }
        // only keep finding if there's a match for the first character
        if (i != p->children.size()) {
            findFromNode(p->children[i], key, keyPos+1, exactMatchOnly, targetVector);
        }
        else
            return;
    }

    // otherwise, we need to deal with exact/non-exact matches
    // remember that the string still hasn't reached the end, per the base case above
    else {
        // first check, if searching for an exact match
        if (exactMatchOnly) {
            int i;
            for (i = 0; i < p->children.size(); i++) {
                Node* cur = p->children[i];
                if (cur->label == keyChar)
                    break;
            }
            if (i != p->children.size()) {
                findFromNode(p->children[i], key, keyPos+1, true, targetVector);
            }
            else
                return;
        }
        // exactMatchOnly is false
        else {
            // find from every node, set exactMatchOnly to false if the label is not keyChar
            for (int i = 0; i < p->children.size(); i++) {
                Node* cur = p->children[i];
                // if the char matches the key, we can keep exactMatchOnly false
                // otherwise, keep going but with exactMatchOnly true - we've used our one mismatch.
                bool match = (cur->label != keyChar);
                findFromNode(cur, key, keyPos+1, match, targetVector);
            }
        }
    }
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const {
    std::vector<ValueType> tempVector;
    if (!key.empty())
        findFromNode(m_root, key, 0, exactMatchOnly, tempVector);

    return tempVector;
}

#endif // TRIE_INCLUDED










































