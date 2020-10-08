#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

BagIterator::BagIterator(const Bag& bag): bag(bag)
{
	this->currentSlot = -1;
	this->currentElement = NULL;
	this->currentFrequency = 0;
	this->first();
}

void BagIterator::first() {
	int i = 0;
	for (; i < this->bag.nrSlots; i++)
		if (this->bag.table[i] != NULL) {
			this->currentElement = this->bag.table[i];
			this->currentFrequency = this->currentElement->info.second;
			this->currentSlot = i;
			break;
		}
}

void BagIterator::next() {
	if (!this->valid()) throw exception("Invalid iterator");
	this->currentFrequency--;
	if (this->currentFrequency == 0) {
		this->currentElement = this->currentElement->next;
		if (this->currentElement == NULL) {
			this->currentSlot++;
			while (this->currentSlot < this->bag.nrSlots && this->bag.table[this->currentSlot] == NULL) this->currentSlot++;
			if (this->currentSlot < this->bag.nrSlots) {
				this->currentElement = this->bag.table[this->currentSlot];
				this->currentFrequency = this->currentElement->info.second;
			}
		}
		else this->currentFrequency = this->currentElement->info.second;
	}
}

bool BagIterator::valid() const {
	return (this->currentSlot == this->bag.nrSlots || this->currentSlot == -1) ? false : true;
}

TKey BagIterator::getCurrent() const
{
	if (!this->valid()) throw exception("Invalid iterator");
	return this->currentElement->info.first;
}
