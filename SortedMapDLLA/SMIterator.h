#pragma once
#include "SortedMap.h"

class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& map);
	int currentPosition;

public:
	void first();
	void next() noexcept(false);
	bool valid() const;
    TElem getCurrent() const noexcept(false);
};

