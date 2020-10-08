#pragma once
#include <utility>
#include <vector>

using namespace std;

typedef int TKey;
typedef int TValue;
typedef pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)

#define A 0.61803
#define threshhold 0.7
typedef double(*hashFunction)(TKey, double);

inline double multiplyHash(TKey key, double nrSlots) { return floor(nrSlots * (abs(key) * A - floor(abs(key) * A))); }


class MapIterator;

inline int findFirstFree(vector<TElem> v, double dimension) {
	int i = 0;
	for (i; i < dimension; i++) if (v[i] == NULL_TELEM) break;
	return i;
}

class Map {
	friend class MapIterator;
private:
	vector<TElem> table;
	vector<int> next;
	hashFunction hf;
	double nrSlots;
	double nrOccupied;
	double loadFactor;
	int firstFree;

private:
	void resizeAndRehash();

public:
	Map();

	TValue add(TKey c, TValue v);

	TValue search(TKey c) const;

	TValue remove(TKey c);

	int size() const;

	bool isEmpty() const;

	MapIterator iterator() const;

	~Map();
};



