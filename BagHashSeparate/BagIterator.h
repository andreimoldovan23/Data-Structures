#include "Bag.h"

class BagIterator
{
	friend class Bag;
private:
	const Bag& bag;
	Node* currentElement;
	int currentFrequency;
	int currentSlot;
	BagIterator(const Bag& bag);
public:
	void first();
	void next() noexcept(false);
	TKey getCurrent() const noexcept(false);
	bool valid() const;
};
