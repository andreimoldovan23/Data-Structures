#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;
private:
	const MultiMap& multiMap;
	int currentPosition;
	MultiMapIterator(const MultiMap& multiMap);

public:
	TElem getCurrent() const noexcept(false);
	bool valid() const;
	void next() noexcept(false);
	void first();
};

