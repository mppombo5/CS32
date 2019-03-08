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
    // add as many private members as you like
    struct Node {
        std::vector
    };
};

template<typename ValueType>
Trie<ValueType>::Trie() {

}

template<typename ValueType>
Trie<ValueType>::~Trie() {

}

template<typename ValueType>
void Trie<ValueType>::reset() {

}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string &key, const ValueType &value) {

}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string &key, bool exactMatchOnly) const {

}

#endif // TRIE_INCLUDED
