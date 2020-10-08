#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

MapIterator::MapIterator(const Map& map) : map(map) { this->first(); }

void MapIterator::first() {
	this->currentSlot = 0;
	while (this->currentSlot < this->map.nrSlots && this->map.table[this->currentSlot] == NULL_TELEM) this->currentSlot++;
}

void MapIterator::next() {
	if (!this->valid()) throw exception("Invalid iterator");
	this->currentSlot++;
	while (this->currentSlot < this->map.nrSlots && this->map.table[this->currentSlot] == NULL_TELEM) this->currentSlot++;
}

TElem MapIterator::getCurrent(){
	if (!this->valid()) throw exception("Invalid iterator");
	return this->map.table[this->currentSlot];
}

bool MapIterator::valid() const {
	if (this->currentSlot < this->map.nrSlots && this->map.size() > 0) return true;
	return false;
}
