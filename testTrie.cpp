//#include "Trie.h"
//#include <iostream>
//#include <vector>
//#include <cassert>
//
//using namespace std;
//
//static int countNew = 0;
//static int countDelete = 0;
//static bool bDebugPrint = false;
//
//#include <random>
//inline
//int randInt(int min, int max)
//{
//	if (max < min)
//		std::swap(max, min);
//	static std::random_device rd;
//	static std::mt19937 generator(rd());
//	std::uniform_int_distribution<> distro(min, max);
//	return distro(generator);
//}
//
//void testTrie1() {
//
//	countNew = countDelete = 0;
//	Trie<int>* head = new Trie<int>();
//
//	head->insert("HELLO", 6);
//	head->insert("HELLA", 66);
//	head->insert("HFLLO", 67);
//	head->insert("HEGLO", 68);
//	head->insert("HELHO", 69);
//	head->insert("HE", 63);
//
//	//std::vector<int> v = head->find("HELLO",true);
//	std::vector<int> v = head->find("HELLO", false);
//	std::cout << " vector size = " << v.size() << ":: ";
//	for (int i = 0; i < v.size(); i++) std::cout << "  " << v[i];
//	std::cout << std::endl;
//
//	////v = head->find("HE", true);
//	//v = head->find("HE", true);
//	//std::cout << " vector size = " << v.size() << ":: ";
//	//for (int i = 0; i < v.size(); i++) std::cout << "  " << v[i];
//	//std::cout <<  std::endl;
//
//	////v = head->find("HEL", true);
//	//v = head->find("HEL", true);
//	//std::cout << " vector size = " << v.size() << ":: ";
//	//for (int i = 0; i < v.size(); i++) std::cout << "  " << v[i];
//	//std::cout << std::endl;
//
//	//std::cout << "past all tests in testTrie1()" <<  std::endl;
//
//	//head->reset();
//
//	delete head;
//}
//
//void testTrie2() {
//
//	countNew = countDelete = 0;
//	Trie<int>* head = new Trie<int>();
//
//	head->insert("HELLO");
//	assert(head->search("HELLO"));
//
//	head->insert("HELLOWORLD");
//	assert(head->search("HELLOWORLD"));
//
//	assert(!head->search("HELLL"));  // not found
//
//	head->insert("HELL");
//	assert(!head->search("HELLL"));
//
//	head->insert("H");
//	assert(head->search("H"));
//
//	assert(!head->search("HE"));
//
//	head->insert("4");
//
//	delete head;
//	assert(countNew == countDelete);
//	std::cout << "past all tests in testTrie2()" << std::endl;
//}
//
//void testTrie3() {
//	countNew = countDelete = 0;
//	Trie<int>* head = new Trie<int>();
//
//	int n = randInt(30, 50);
//	vector<string> vs;
//	//cout << "n=" << n << endl;
//	for (int i = 0; i < n; i++)
//	{
//		string s;
//		int m = randInt(100, 200);
//		for (int j = 0; j < m; j++)
//		{
//			char c = randInt(65, 90);
//			s += c;
//		}
//		head->insert(s, m + i);
//		vs.push_back(s);
//	}
//
//	for (int i = 0; i < vs.size(); i++)
//	{
//		assert(head->search(vs[i]));
//	}
//
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	cout << vs[i].c_str()<< endl;
//	//}
//
//
//	//head->reset();
//	delete head;
//	assert(countNew == countDelete);
//	std::cout << "past all tests in testTrie3()" << std::endl;
//}
//
//void testTrie4() {
//
//	countNew = countDelete = 0;
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
//	v = head->find("hit", false); // returns {1, 2, 10, 20, 7, 8, 9}
//	std::cout << " vector size = " << v.size() << ":: ";
//	for (int i = 0; i < v.size(); i++) std::cout << "  " << v[i];
//	std::cout << std::endl;
//
//	//v = head->findHelper(head->root, "sit", false); // returns {}
//	//std::cout << " vector size = " << v.size() << ":: ";
//	//for (int i = 0; i < v.size(); i++) std::cout << "  " << v[i];
//	//std::cout << std::endl;
//
//	std::cout << "past all tests in testTrie4()" << std::endl;
//
//	//head->reset();
//
//	delete head;
//}
//
