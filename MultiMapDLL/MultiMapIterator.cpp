#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& mMap): multiMap(mMap) {
	this->currentKey = this->multiMap.tail;
	if (this->currentKey != NULL) this->currentValue = this->currentKey->info.second.first;
	else this->currentValue = NULL;
}

TElem MultiMapIterator::getCurrent() const{
	if(this->valid()) return TElem(this->currentKey->info.first, this->currentValue->info);
	throw std::exception("Invalid iterator");
}

bool MultiMapIterator::valid() const { return !(this->currentKey == NULL); }

void MultiMapIterator::next() {
	if(!this->valid()) throw std::exception("Invalid iterator");
	this->currentValue = this->currentValue->next;
	if (this->currentValue == NULL) {
		this->currentKey = this->currentKey->next;
		if (this->currentKey == NULL)
			this->currentValue = NULL;
		else
			this->currentValue = this->currentKey->info.second.first;
	}
}

void MultiMapIterator::first() {
	this->currentKey = this->multiMap.tail;
	this->currentValue = this->currentKey->info.second.first;
}

