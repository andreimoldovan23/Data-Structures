#pragma once
#include <utility>

using namespace std;

typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

class SortedBagIterator;

class Node {
	friend class SortedBag;
	friend class SortedBagIterator;
private:
	TComp info;
	Node* left;
	Node* right;
	Node* parent;
public:
	Node(TComp elem = NULL_TCOMP, Node* parent = NULL) { this->info = elem; this->left = NULL; this->right = NULL; this->parent = parent; }
	~Node(){}
};
inline Node* allocateNode(TComp elem, Node* parent) { return new Node(elem, parent); }
inline void deallocateNode(Node* nodePointer) { delete nodePointer; }

class SortedBag {
	friend class SortedBagIterator;
private:
	Node* root;
	Relation rel;
	int nrElements;

private:
	Node* findMaxLeftSubtree(Node* target) const;
	Node* findMinRightSubtree(Node* target) const;
	void deleteChild(Node* child);
	Node* findNode(Node*, TComp) const;
	void deleteTree(Node*);
	void traverse(Node*, int*, TComp) const;

public:
	SortedBag(Relation r);

	void add(TComp elem);

	bool remove(TComp elem);

	bool search(TComp elem) const;

	int nrOccurrences(TComp elem) const;

	int size() const;

	SortedBagIterator iterator() const;

	bool isEmpty() const;

	~SortedBag();
};