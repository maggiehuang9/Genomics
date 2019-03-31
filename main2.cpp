//#include "Trie.h"
//#include "provided.h"
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <cctype>
//#include <cstdlib>
//#include <cassert>
//#include <algorithm>
//#include <map>
//
//using namespace std;
//
//void testFindDNA()
//{
//	// this function test the cases on pages 25,26,27  in the spec
//	string dna[] = { "GAAG"                 ,
//					 "GAATAC"               ,
//					 "GAATAC"               ,
//					 "GAATAC"               ,
//					 "GTATAT"               ,
//					 "GAATACG"              ,
//					 "GAAGGGTT"             ,
//					 "GAAGGGTT"             ,
//					 "ACGTGCGAGACTTAGAGCC"  ,
//					 "ACGTGCGAGACTTAGAGCG"  ,
//					 "GAAG"                 ,
//					 "GAAG" };
//
//	int length[] = { 4,	4,	6,	6,	6,	6,	5,	6,	12 , 12 , 3, 5 };
//
//	bool match[] = { true,	true,	true,	false,	false,	false,	false,	false,	false,	false, true, true };
//
//	const int defaultMinSearchLength = 4;
//	GenomeMatcher* library = new GenomeMatcher(defaultMinSearchLength);
//	library->addGenome(Genome("Genome 1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
//	library->addGenome(Genome("Genome 2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
//	library->addGenome(Genome("Genome 3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
//
//	for (int i = 0; i < 12; i++) {
//		string match_str;
//		if (match[i]) match_str = "true";
//		else match_str = "false";
//		vector<DNAMatch> matches;
//		if (!library->findGenomesWithThisDNA(dna[i], length[i], match[i], matches))
//		{
//			cout << endl << "findGenomesWithThisDNA(" << dna[i] << ", " << length[i] << "," << match_str << ")" << endl;
//			cout << "result: false; matches: none" << endl;
//		}
//		else {
//			cout << endl << "findGenomesWithThisDNA(" << dna[i] << ", " << length[i] << "," << match_str << ")" << endl;
//			cout << "result: true; matches:" << endl;
//			for (const auto& m : matches)
//				cout << m.genomeName << " of length " << m.length << " at position " << m.position << endl;
//		}
//	}
//
//	delete library;
//}
//
//void testRelatedGenome()
//{
//	const int defaultMinSearchLength = 4;
//	GenomeMatcher* library = new GenomeMatcher(defaultMinSearchLength);
//	library->addGenome(Genome("yeti", "ACGTACGTAAAACCCCGGGGTTTTNANANANANA"));
//	library->addGenome(Genome("sasquatch", "GGGGTTTTAAAACCCCACGTACGTACGTNANANANA"));
//
//	Genome query("query", "AAATCCCTGGGGTTTTNANA");
//
//	int fragmentMatchLength = 8;
//	double matchPercentThreshold = 20;
//	bool exactMatchOnly = false;
//	vector<GenomeMatch> matches;
//	library->findRelatedGenomes(query, fragmentMatchLength,
//		exactMatchOnly, matchPercentThreshold, matches);
//
//	if (matches.empty())
//	{
//		cout << "    No related genomes were found" << endl;
//		return;
//	}
//
//	cout << "    " << matches.size() << " related genomes were found:" << endl;
//	cout.setf(ios::fixed);
//	cout.precision(2);
//	for (const auto& m : matches)
//		cout << " " << setw(6) << m.percentMatch << "%  " << m.genomeName << endl;
//
//	cout << "testRelatedGenome()" << endl;
//
//	delete library;
//
//}
//
//void testTrie() {
//
//	// this function test the cases on pages 14 and 15 in the spec
//	//std::vector<int> result1 = trie.find("hit", true); // returns {1, 2} or {2, 1}
//	//std::vector<int> result2 = trie.find("hit", false); // returns {1, 2, 10, 20, 7, 8, 9}
//
//	Trie<int>* head = new Trie<int>();
//	vector<int> v;
//
//	head->insert("hi", 9);
//	head->insert("hi", 17);
//
//	head->insert("hit", 1);
//	head->insert("hit", 2);
//
//	head->insert("hip", 10);
//	head->insert("hip", 20);
//
//	head->insert("hat", 7);
//	head->insert("hat", 8);
//	head->insert("hat", 9);
//
//	head->insert("a", 14);
//
//	head->insert("to", 22);
//	head->insert("to", 23);
//
//	head->insert("tap", 19);
//	head->insert("tap", 6);
//	head->insert("tap", 32);
//
//	v = head->find("hit", true);  // returns {1, 2} or {2, 1}
//	std::cout << " vector size = " << v.size() << ":: ";
//	for (int i = 0; i < v.size(); i++) std::cout << "  " << v[i];
//	std::cout << std::endl;
//
//	assert(v.size() == 2);
//	sort(v.begin(), v.end());
//	assert(v[0] == 1);
//	assert(v[1] == 2);
//
//	v = head->find("hit", false); // returns {1, 2, 10, 20, 7, 8, 9}
//	std::cout << " vector size = " << v.size() << ":: ";
//	for (int i = 0; i < v.size(); i++) std::cout << "  " << v[i];
//	std::cout << std::endl;
//
//	assert(v.size() == 7);
//	sort(v.begin(), v.end());
//	assert(v[0] == 1);
//	assert(v[1] == 2);
//	assert(v[2] == 7);
//	assert(v[3] == 8);
//	assert(v[4] == 9);
//	assert(v[5] == 10);
//	assert(v[6] == 20);
//
//	v = head->find("sit", false); // returns {}
//	std::cout << " vector size = " << v.size() << ":: ";
//	for (int i = 0; i < v.size(); i++) std::cout << "  " << v[i];
//	std::cout << std::endl;
//	assert(v.size() == 0);
//
//	v = head->find("sit", false); // returns {}
//	std::cout << " vector size = " << v.size() << ":: ";
//	for (int i = 0; i < v.size(); i++) std::cout << "  " << v[i];
//	std::cout << std::endl;
//
//	std::cout << "past all tests in testTrie()" << std::endl;
//
//	delete head;
//}
//
//int main()
//{
//	testFindDNA();
//	testRelatedGenome();
//	testTrie();
//	return 0;
//}
