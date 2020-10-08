#pragma once
#include <utility>
#include <vector>

using namespace std;

#define NULL_TKEY -111111
#define NULL_TELEM TElem(NULL_TKEY, NULL_TKEY)
#define threshhold 0.7
#define A 0.6180339887

typedef int TKey;
typedef pair<TKey, int> TElem;
typedef double(*hashFunction)(TKey, double);

class BagIterator; 

inline double multiplyHash(TKey key, double nrSlots) { return floor(nrSlots * (abs(key) * A - floor(abs(key) * A))); }

class Node {
	friend class Bag;
	friend class BagIterator;
private:
	TElem info;
	Node* next;
public:
	Node(TKey key = NULL_TKEY, int freq = NULL_TKEY) { this->info.first = key; this->info.second = freq; this->next = NULL; }
	~Node(){}
	friend void deallocateNode(Node* nodePointer);
	friend Node* searchNode(Node* nodePointer, TKey elem);
};

inline Node* allocateNode(TKey key, int freq) { return new Node(key, freq); }

inline void deallocateNode(Node* nodePointer) {
	Node* currentNode = nodePointer;
	while (currentNode != NULL) {
		Node* toDelete = currentNode;
		currentNode = currentNode->next;
		delete toDelete;
	}
}

inline Node* searchNode(Node* nodePointer, TKey elem) {
	if (nodePointer->info.first == elem) return nodePointer;
	while (nodePointer->next != NULL && nodePointer->next->info.first != elem) nodePointer = nodePointer->next;
	return nodePointer;
}


class Bag {
	friend class BagIterator;
private:
	hashFunction hf;
	vector<Node*> table;
	double nrSlots;
	double loadFactor;
	double nrOccupiedSlots;
	int nrElements;

private:
	void resizeAndRehash();

public:
	Bag();

	void add(TKey elem);

	bool remove(TKey elem);

	bool search(TKey elem) const;

	int nrOccurrences(TKey elem) const;

	int size() const;

	BagIterator iterator() const;

	bool isEmpty() const;

	~Bag();
};