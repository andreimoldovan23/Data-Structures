#pragma once
#include "Map.h"
class MapIterator
{
	friend class Map;
private:
	const Map& map;
	int currentSlot;
	MapIterator(const Map& map);
public:
	void first();
	void next() noexcept(false);
	TElem getCurrent() noexcept(false);
	bool valid() const;
};


