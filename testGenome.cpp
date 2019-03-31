//#include "provided.h"
//#include <iostream>
//#include <vector>
//#include <cassert>
//#include <fstream> // needed to open files
//#include <string>
//using namespace std;
//
//static int countNew = 0;
//static int countDelete = 0;
//static bool bDebugPrint = false;
//
//
//void testGenome() {
//
//	// Specify the full path and name of the gene data file on your hard drive.
//	string filename = "E:/UCLA/CS32/Project4/code/dna.txt";
//	// Open the data file and get a ifstream object that can be used to read its
//	// contents.
//	ifstream strm(filename);
//	if (!strm)
//	{
//		cout << "Cannot open " << filename << endl;
//		return;
//	}
//	vector<Genome> vg;
//	bool success = Genome::load(strm, vg); // Load the data via the stream.
//	if (success)
//	{
//		cout << "Loaded " << vg.size() << " genomes successfully:" << endl;
//		for (int k = 0; k != vg.size(); k++)
//			cout << vg[k].name() << endl;
//	}
//	else
//		cout << "Error loading genome data" << endl;
//
//	std::cout << "past all tests in testGenome()" << std::endl;
//
//
//}