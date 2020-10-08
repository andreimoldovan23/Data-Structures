#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& mMap): multiMap(mMap) { this->currentNode = this->multiMap.list; }

TElem MultiMapIterator::getCurrent() const{
	if (!this->valid()) throw exception("Invalid iterator");
	return this->currentNode->info;
}

bool MultiMapIterator::valid() const {
	return (this->currentNode == NULL || this->multiMap.isEmpty()) ? false : true;
}

void MultiMapIterator::next() {
	if (!this->valid()) throw exception("Invalid access");
	this->currentNode = this->currentNode->next;
}

void MultiMapIterator::first() { this->currentNode = this->multiMap.list; }

