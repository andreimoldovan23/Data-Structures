#pragma once

#include<vector>
#include "Project/Nodes.h"

class MultiMapIterator;

class MultiMap
{	
	friend class MultiMapIterator;
private:
	KeyNode* tail;
	KeyNode* head;
	int numberElements;

private:
	KeyNode* searchKey(TKey key) const;
	ValueNode* searchValue(KeyNode* keyPointer, TValue value) const;
	void addEmptyList(TKey key, TValue value);
	void addNewElement(TKey key, TValue value);
	void addNewValue(KeyNode* keyPointer, TValue value);
	void removeKey(KeyNode* keyPointer);
	void removeValue(KeyNode* keyPointer, ValueNode* valuePointer);

public:
	MultiMap();

	void add(TKey c, TValue v);

	bool remove(TKey c, TValue v);

	vector<TValue> search(TKey c) const;

	int size() const;

	bool isEmpty() const;

	MultiMapIterator iterator() const;

	~MultiMap();
};

