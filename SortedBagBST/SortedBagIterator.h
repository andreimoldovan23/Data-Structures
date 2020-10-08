#pragma once
#include "SortedBag.h"
#include <vector>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;
private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& bag);
	vector<Node*> inorder;
	int currentPosition;

private:
	void traverse(Node*);

public:
	TComp getCurrent() noexcept(false);
	bool valid();
	void next() noexcept(false);
	void first();
};

