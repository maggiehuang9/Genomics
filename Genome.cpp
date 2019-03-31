#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <algorithm>
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
	static bool isValidBaseLine(const string & str);
	string m_name;
	string m_dna;
	int m_length;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
	m_name = nm;
	m_dna = sequence;
	m_length = sequence.length();
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
	string str;
	string name;
	string dna;
	while (std::getline(genomeSource, str)) {
		if (str[0] == '>') {
			if (str.length()==1) return false; // a line starting with > but containing no other characters
			if (!name.empty() && dna.empty()) return false;  // no	base lines after a name line
				
			if (!dna.empty()) {
				Genome g(name, dna); 
				genomes.push_back(g);
				dna = "";
				name= "";
			}
			name = str.substr(1);
		}
		else {
			if (name.empty()) return false;   // not starting with a name line
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);
			if (!isValidBaseLine(str)) return false;  // non-name lines containing any characters other than upper or lower case A C T G N,
			dna += str;
		}
	}

	if (name.empty() || dna.empty()) return false;
	Genome g(name, dna);
	genomes.push_back(g);

	return true;//went through eveything successfully
}

bool GenomeImpl::isValidBaseLine(const string & str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] != 'A' && str[i] != 'C' && str[i] != 'T' && str[i] != 'G' && str[i] != 'N') return false;
	return true;
}

int GenomeImpl::length() const
{
    return m_length; 
}

string GenomeImpl::name() const
{
    return m_name;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
	if (position + length > m_length) return false; //extract a string that goes past the end of the genome

	fragment = m_dna.substr(position, length);

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
