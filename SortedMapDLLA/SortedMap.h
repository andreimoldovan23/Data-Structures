#pragma once
#include <utility>
#include <vector>

using namespace std;

typedef int TKey;
typedef int TValue;
typedef bool(*Relation)(TKey, TKey);
typedef pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)

class SMIterator;

class SortedMap {
	friend class SMIterator;
private:
	Relation r;
	vector<TElem> elements;
	vector<int> nextList;
	vector<int> previousList;
	int tail;
	int head;
	int firstFree;
	int capacity;
	int numberElements;

private:
	void resize();
	int searchElement(TKey key) const;
	void setLinks();
	void addEmptyList(TKey key, TValue val);
	void addBeforeFirst(TKey key, TValue val);
	void addBetween(int position, TKey key, TValue val);
	void addAfterLast(TKey key, TValue val);
	void removeFirst();
	void removeBetween(int position);
	void removeLast();
	void removeOnlyElement();

public:
    SortedMap(Relation r);

	TValue add(TKey key, TValue value);

	TValue search(TKey key) const;

	TValue remove(TKey key);

	int size() const;

	bool isEmpty() const;

    SMIterator iterator() const;

    ~SortedMap();
};
