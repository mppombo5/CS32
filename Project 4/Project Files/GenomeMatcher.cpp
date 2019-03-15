#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength,
                                bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength,
                            bool exactMatchOnly, double matchPercentThreshold,
                            vector<GenomeMatch>& results) const;
private:
    int m_minSL;
    vector<Genome> m_genomes1;
    unordered_map<string, Genome> m_genomes;
      //struct to hold a genome's name and the relevant position in the Trie
    struct GenomeBucket {
        string name;
        int position;
    };
    Trie<GenomeBucket> m_trie;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSL = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genomes.insert({genome.name(), genome});
    string s;
    for (int i = 0; i <= genome.length()-m_minSL; i++) {
        GenomeBucket b;
        b.name = genome.name();
        b.position = i;
        if (genome.extract(i, m_minSL, s))
            m_trie.insert(s, b);
        else
            break;
    }

    // first attempt with a vector of genomes rather than an unordered_map
    /*m_genomes1.push_back(genome);
    string s1;
    // add each substring of length m_minSL to the trie
    for (int i = 0; i <= genome.length()-m_minSL; i++) {
        GenomeBucket b;
        b.name = genome.name();
        b.position = i;
        if (genome.extract(i, m_minSL, s1))
            m_trie.insert(s1, b);
        else
            break;
    }*/
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSL;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength,
                                               bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if (fragment.size() < minimumLength || minimumLength < m_minSL)
        return false;

    // keeps track of genomes that have matched the fragment
    vector<GenomeBucket> initialHits;
    // final vector to be passed back when done
    vector<DNAMatch>  genomeMatches;

    // only look for the first substring of length minimumLength
    initialHits = m_trie.find(fragment.substr(0, (size_t) minimumLength), exactMatchOnly);

    // immediately return false if there were no matches between any genomes.
    if (initialHits.empty())
        return false;

    // initialHits now contains all instances of genomes having the minLength substring of fragment
    for (int i = 0; i < initialHits.size(); i++) {
        string subFragment;

        // if we can indeed extract the whole fragment from the position of genomeHit[i],
        // set subFragment equal to a fragment whose length is the same as fragment passed into the function.
        if (m_genomes.at(initialHits[i].name).extract(initialHits[i].position, (int) fragment.size(), subFragment)) {
            int subFragmentSize = 0;

            // determine whether we should be allowed our one mismatch.
            // the first letter matches for sure, since it was added to our initialHits.
            bool mismatchAllowed = !exactMatchOnly;
            for (size_t j = 0; j < fragment.size(); j++) {
                if (fragment[j] == subFragment[j])
                    subFragmentSize++;
                else {
                    // keep going if a mismatch is allowed, break out if not.
                    if (!mismatchAllowed)
                        break;
                    subFragmentSize++;
                    mismatchAllowed = false;
                }
            }
        }
    }
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength,
                                           bool exactMatchOnly, double matchPercentThreshold,
                                           vector<GenomeMatch>& results) const
{
    return false;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength,
                                           bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength,
                                       bool exactMatchOnly, double matchPercentThreshold,
                                       vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
