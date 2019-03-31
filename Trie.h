#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED
#include <iostream>
#include <vector>
#include <cassert>
#include <cassert>
//using namespace std;
const int CHAR_SIZE = 128;
template <typename ValueType>
class Trie {
private:
	struct Node {
		Node() :is_leaf(false), children(CHAR_SIZE, nullptr) {}
		~Node() {}
		bool is_leaf;
		std::vector<Node*> children;
		std::vector<ValueType> values;
	};

	Node* root;
	std::vector<ValueType> findExactlyMatch(const Node* node, const std::string& key) const;
	std::vector<ValueType> findSnipMatch(const Node* node, const std::string& key, bool exactMatchOnly) const;
	void removeChildren(struct Node*& root_node); // remove all the Nodes from Trie
public:
	Trie();
	~Trie();
	Trie(const Trie&) = delete; // C++11 syntax for preventing copying
	Trie& operator=(const Trie&) = delete; // C++11 syntax for preventing assignment
	void insert(const std::string& key, const ValueType& value); //Inserts a key into the trie
	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
	void reset();  // free memory for all nodes in Trie Tree.
};

template <typename ValueType>
Trie<ValueType>::Trie() {
	root = new Node();
}

template <typename ValueType>
Trie<ValueType>::~Trie() {
	removeChildren(root);
}

//Inserts a key into the trie
template <typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
	Node* node = root;
	for (const char c : key) {
		if (node->children[c]==nullptr)
		{
			node->children[c] = new Node();
		}
		node = node->children[c];
	}
	node->values.push_back(value);
	node->is_leaf = true;
}

template <typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
	if (exactMatchOnly) {
		return findExactlyMatch(root, key);
	}
	else {
		if (root->children[key[0]] == nullptr) return {};  // if not match the first character, return empty
		return findSnipMatch(root, key, exactMatchOnly);
	}
};

template <typename ValueType>
std::vector<ValueType> Trie<ValueType>::findExactlyMatch(const Node* root_node, const std::string& key) const
{
	if (root_node == nullptr) return {}; // return empty vector, C++ 11

	const Node* node = root_node;
	for (const char c : key) {
		node = node->children[c];
		if (node == nullptr) break;
	}
	if (node && node->is_leaf)
		return node->values;
	else
		return {}; // return empty vector
};

template <typename ValueType>
std::vector<ValueType> Trie<ValueType>::findSnipMatch(const Node* root_node,const std::string& key, bool exactMatchOnly) const
{
	if (root_node == nullptr || key.length() == 0) return {}; // return an empty vector

	if (exactMatchOnly) return  findExactlyMatch(root_node, key);

	std::vector<ValueType> v;

	if (key.length() == 1) {
		for (int j = 0; j < CHAR_SIZE; j++)
		{
			if (root_node->children[j] != nullptr)
			{
				//std::vector<ValueType>* v2 = &root_node->children[j]->values;
				if (root_node->children[j]->is_leaf && !root_node->children[j]->values.empty())
					 v.insert(v.end(), root_node->children[j]->values.begin(), root_node->children[j]->values.end());
			}
		}
		return v;
	}

	const Node* node = root_node;

	int i;
	for (i = 0; i < key.length(); i++) {
		for (int j = 0; j < CHAR_SIZE; j++) {
			if (node->children[j] == nullptr) continue;
			std::vector<ValueType> v2;
			if (j == key[i]) {
				v2 = findSnipMatch(node->children[j], key.substr(i + 1), exactMatchOnly);
			}
			else {
				v2 = findSnipMatch(node->children[j], key.substr(i + 1), true);
			}
			if (!v2.empty()) v.insert(v.end(), v2.begin(), v2.end());
		}
	}

	return v;
};

template <typename ValueType>
void Trie<ValueType>::removeChildren(struct Node*& root_node)
{
	if (root_node == nullptr) return;
	// remove all the nodes from the tree and release memory
	for (int i = 0; i < CHAR_SIZE; i++)
	{
		if (root_node->children[i] != nullptr)
			removeChildren(root_node->children[i]);
	}

	if (root_node != nullptr)
	{
		delete root_node;
		root_node = nullptr;  // reset the pointer to null
	}
}

// free memory for all nodes in Trie Tree.
template <typename ValueType>
void Trie<ValueType>::reset() {
	removeChildren(root);
	root = new Node();
}

#endif // TRIE_INCLUDED
