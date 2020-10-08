#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)

class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;
private:
	vector<TElem> elements;
	vector<int> nextList;
	int tail;
	int head;
	int firstFree;
	int numberElements;
	int capacity;

private:
	void resize();
	int searchElement(TKey key, TValue val) const;

public:
	MultiMap();

	void add(TKey key, TValue val);

	bool remove(TKey key, TValue val);

	vector<TValue> search(TKey key) const;

	int size() const;

	bool isEmpty() const;

	MultiMapIterator iterator() const;

	~MultiMap();
};

