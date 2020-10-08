#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& mMap): multiMap(mMap) { this->currentPosition = this->multiMap.tail; }

TElem MultiMapIterator::getCurrent() const{
	if (!this->valid()) throw std::exception("Invalid iterator");
	return this->multiMap.elements[this->currentPosition];
}

bool MultiMapIterator::valid() const {
	return (this->currentPosition == -1 || this->multiMap.elements[this->currentPosition] == NULL_TELEM) ? false : true;
}

void MultiMapIterator::next() {
	if (!this->valid()) throw std::exception("Invalid iterator");
	this->currentPosition = this->multiMap.nextList[this->currentPosition];
}

void MultiMapIterator::first() { this->currentPosition = this->multiMap.tail; }

