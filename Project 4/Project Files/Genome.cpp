#include "provided.h"
#include <string>
#include <cctype>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
    int m_length;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence) {
    m_name = nm;
    m_sequence = sequence;
    m_length = (int) sequence.size();
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) {
    string s;
    string name;
    string sequence;
    vector<Genome> temp;
    while (getline(genomeSource, s)) {
        // if genomeSource still has lines left, s now holds the current line we're worried about
        // no empty lines allowed
        if (s.empty())
            return false;
        // line is a name line, so take the substring starting at s[1] as the name
        if (s[0] == '>') {
            if (!name.empty()) {
                if(!sequence.empty()) {
                    // add the genome with name and sequence to temp if name and sequence are both not empty
                    temp.emplace_back(name, sequence);
                    name = "";
                    sequence = "";
                }
                // this would be reached if, for example, there were two name lines in a row.
                else
                    return false;
            }
            string tempName = s.substr(1);
            // only make it the name if there are characters after the >
            if (tempName.empty())
                return false;
            else
                name = tempName;
        }
        // at this point, the line should be a base line. check that each character is valid.
        else {
            // there shouldn't be a base line without a name
            if (name.empty())
                return false;
            for (int i = 0; i < s.size(); i++) {
                // return false if a char is not A, G, T, C, or N.
                switch (toupper(s[i])) {
                    case 'A':
                    case 'G':
                    case 'T':
                    case 'C':
                    case 'N':
                        continue;
                    default: return false;
                }
            }
            // if this point has been reached, the string is valid and should be concatenated onto sequence.
            sequence += s;

        }
    }
    // at the end of the file, there should be a genome sequence that still needs to be added.
    if (!name.empty()) {
        if (!sequence.empty()) {
            temp.emplace_back(name, sequence);
            genomes = temp;
            return true;
        }
        return false;
    }
    // if this is reached, there was an error.
    return false;
}

int GenomeImpl::length() const {
    return m_length;
}

string GenomeImpl::name() const {
    return m_name;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const {
    // this is the check to see if this function reaches past the sequence's end
    // or if something else fishy is going on
    if (position + length > m_length || position < 0 || length < 0)
        return false;

    fragment = m_sequence.substr((size_t) position, (size_t) length);
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
