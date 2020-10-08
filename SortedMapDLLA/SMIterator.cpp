#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& map) : map(map){ this->currentPosition = this->map.tail; }

void SMIterator::first(){ this->currentPosition = this->map.tail; }

void SMIterator::next(){
	if (!this->valid()) throw exception("Invalid iterator");
	this->currentPosition = this->map.nextList[this->currentPosition];
}

bool SMIterator::valid() const{
	return (this->currentPosition == -1 || this->map.elements[this->currentPosition] == NULL_TELEM) ? false : true;
}

TElem SMIterator::getCurrent() const{
	if (!this->valid()) throw exception("Invalid iterator");
	return this->map.elements[this->currentPosition];
}
