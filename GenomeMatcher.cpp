#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>
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
		bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;

private:
	struct GenomePos
	{
	public:
		GenomePos(int indx, int pos) :index(indx), position(pos) {};
		int index;  // index of genome in m_genomes
		int position; // position in DNA sequence
	};

	int countMatches(const string &str1, const string &str2, bool exactMatchOnly) const;
	vector<Genome> m_genomes;
	int m_minSearchLength;
	Trie<GenomePos> m_trie;
	unordered_map <string, int> genomeNameIndex; // save maps between genome name and index number in m_genomes
};

int GenomeMatcherImpl::countMatches(const string &str1, const string &str2, bool exactMatchOnly) const {
	// count number of matches character between str1 and str2, str1 and str2 must have same length

	if (str1.length() != str2.length() || str1.length() == 0 || str2.length() == 0) return 0;
	if (str1[0] != str2[0]) return 0;  // if first letter not match

	int numMatches = 0;
	int numMisMatches = 0;
	for (int k = 0; k < str1.length(); k++) {

		if (str1[k] == str2[k])
			numMatches++;
		else
			numMisMatches++;

		if (exactMatchOnly)
		{
			if (numMisMatches > 0) break;  // no mis-match allowed
		}
		else
		{
			if (numMisMatches > 1) break;  // allow one mis-match 
		}
	}

	if (!exactMatchOnly && numMisMatches > 0) numMatches++;

	return numMatches;
}

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{

	m_minSearchLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	genomeNameIndex[genome.name()] = m_genomes.size(); // save maps between genome name and index number in m_genomes
	m_genomes.push_back(genome);

	string fragment;
	for (int pos = 0; pos <= genome.length() - m_minSearchLength; pos++)
	{
		if (genome.extract(pos, m_minSearchLength, fragment))
		{
			int index = m_genomes.size() - 1; // use -1 is due to index start from 0
			m_trie.insert(fragment, GenomePos(index, pos));
		}
	}
}

int GenomeMatcherImpl::minimumSearchLength() const
{
	return m_minSearchLength;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	if (fragment.length() < minimumLength) return false; //fragment's length is less than minimumLength, page 24
	if (minimumLength < m_minSearchLength) return false; //minimumLength is less than the minSearchLength

	vector<GenomePos> match_pos = m_trie.find(fragment.substr(0, m_minSearchLength), exactMatchOnly);  // get match sub_string positions
	if (match_pos.empty()) return false; // no matches between fragment and any segment of any genome

	matches.clear(); // clear the vector first

	// vector to save index of mtaches for each genome, if no match for that genome, set it to -1

	vector<int> matches_index(m_genomes.size(), -1); // initialize to -1

	for (int i = 0; i < match_pos.size(); i++)
	{
		string str;
		if (m_genomes[match_pos[i].index].extract(match_pos[i].position, fragment.length(), str))
		{
			int matchLength = countMatches(fragment, str, exactMatchOnly);
			if (matchLength < minimumLength) continue;  // no match found, skip it

			if (matches_index[match_pos[i].index] >= 0) // already has match for the genome
			{
				// if the new match is longer, replace with this new one, otherwise, keep the old one
				int k = matches_index[match_pos[i].index];
				if (matches[k].length < matchLength) // find a longer one
				{
					matches[k].length = matchLength;
					matches[k].position = match_pos[i].position;
				}
			}
			else {
				int index = matches.size();
				matches_index[match_pos[i].index] = index;  // save this index
				matches.push_back(DNAMatch{ m_genomes[match_pos[i].index].name(), matchLength, match_pos[i].position });
			}
		}
	}

	return (!matches.empty());  // if no match found return false, otherwise, return true
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength,
	bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	if (fragmentMatchLength < m_minSearchLength) return false;

	results.clear();
	vector<string> query_fragments;

	// Extract that sequence from the queried genome, and save it to vector, spec page 27
	int numFragment = query.length() / fragmentMatchLength;  // number of fragments
	for (int i = 0; i < numFragment; i++)
	{
		int pos = i * fragmentMatchLength;
		string fragment;
		query.extract(pos, fragmentMatchLength, fragment);
		query_fragments.push_back(fragment);
	}

	vector<DNAMatch> matches;

	std::vector<int> count(m_genomes.size(), 0);
	std::vector<int> count_index;  // save the index of genome that matches at leat one fragment

	// count number of matches for each genome
	for (int i = 0; i < query_fragments.size(); i++)
	{
		if (findGenomesWithThisDNA(query_fragments[i], fragmentMatchLength, exactMatchOnly, matches))
		{
			for (int j = 0; j < matches.size(); j++)
			{
				int k = genomeNameIndex.find(matches[j].genomeName)->second;  // get index from genome name
				count[k]++;  // count number of matches
				if (count[k] == 1) count_index.push_back(k);  // save index number of genome that has matches
			}
		}
	}

	// sort based on count with multimap
	multimap<int, int> sorted;
	for (int i = 0; i < count_index.size(); i++)
		sorted.insert(pair<int, int>(count[count_index[i]], count_index[i]));

	std::map<int, int>::reverse_iterator rit; // use reverse_iterator for descending order

	// create vector results in descending order by the percentage
	for (rit = sorted.rbegin(); rit != sorted.rend(); ++rit)
	{
		double percentage = 100.0 * rit->first / numFragment;
		if (percentage >= matchPercentThreshold)
		{
			int index = rit->second;
			results.push_back(GenomeMatch{ m_genomes[index].name(), percentage });
		}
	}

	return !matches.empty();
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

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}