#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TKey;
typedef int TValue;
typedef pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(NULL_TVALUE, NULL_TVALUE)
class MultiMapIterator;


class Node {
	friend class MultiMap;
	friend class MultiMapIterator;

private:
	TElem info;
	Node* next;

public:
	Node(TKey key = NULL_TVALUE, TValue value = NULL_TVALUE) { this->info = TElem(key, value); this->next = NULL; }
	~Node(){}
};


inline Node* alloc(TKey key, TValue value) {
	return new Node(key, value);
}

inline void dealloc(Node* nodePointer) {
	delete nodePointer;
}


class MultiMap
{
	friend class MultiMapIterator;
private:
	Node* list;
	int lenght;

private:
	Node* searchNode(TKey key, TValue value) const;

public:
	MultiMap();

	void add(TKey key, TValue value);

	bool remove(TKey key, TValue value);

	vector<TValue> search(TKey key) const;

	int size() const;

	bool isEmpty() const;

	MultiMapIterator iterator() const;

	~MultiMap();
};

