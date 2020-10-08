#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
	this->r = r;
	this->tail = -1;
	this->head = -1;
	this->numberElements = 0;
	this->capacity = 10;
	for (int i = 0; i < this->capacity; i++) {
		this->elements.push_back(NULL_TELEM);
		this->nextList.push_back(i + 1);
		this->previousList.push_back(i - 1);
	}
	this->nextList[this->capacity - 1] = -1;
	this->firstFree = 0;
}

void SortedMap::resize() {
	for (int i = this->capacity; i < 2 * this->capacity; i++) {
		this->elements.push_back(NULL_TELEM);
		this->nextList.push_back(i + 1);
		this->previousList.push_back(i - 1);
	}
	this->nextList[this->head] = this->capacity;
	this->firstFree = this->capacity;
	this->previousList[this->capacity] = this->head;
	this->capacity *= 2;
	this->nextList[this->capacity - 1] = -1;
}

int SortedMap::searchElement(TKey key) const {
	int currentPosition = this->tail;
	while (currentPosition != -1 && this->elements[currentPosition] != NULL_TELEM && this->r(this->elements[currentPosition].first, key))
		currentPosition = this->nextList[currentPosition];
	return currentPosition;
}

void SortedMap::setLinks() {
	if(this->firstFree != -1) this->previousList[this->firstFree] = this->head;
	this->nextList[this->head] = this->firstFree;
}

void SortedMap::addEmptyList(TKey key, TValue val) {
	this->elements[this->firstFree] = TElem(key, val);
	this->tail = this->firstFree;
	this->head = this->firstFree;
	this->previousList[this->tail] = -1;
	this->firstFree = this->nextList[this->firstFree];
	this->setLinks();
}

void SortedMap::addBeforeFirst(TKey key, TValue val) {
	int formerFree = this->firstFree;
	this->firstFree = this->nextList[this->firstFree];
	this->setLinks();
	this->previousList[formerFree] = -1;
	this->nextList[formerFree] = this->tail;
	this->previousList[this->tail] = formerFree;
	this->tail = formerFree;
	this->elements[this->tail] = TElem(key, val);
}

void SortedMap::addAfterLast(TKey key, TValue val) {
	this->head = this->firstFree;
	this->elements[this->head] = TElem(key, val);
	this->firstFree = this->nextList[this->firstFree];
	this->setLinks();
}

void SortedMap::addBetween(int position, TKey key, TValue val) {
	int next = this->nextList[position];
	this->nextList[position] = this->firstFree;
	this->previousList[next] = this->firstFree;
	int formerFree = this->firstFree;
	this->firstFree = this->nextList[this->firstFree];
	this->setLinks();
	this->previousList[formerFree] = position;
	this->nextList[formerFree] = next;
	this->elements[formerFree] = TElem(key, val);
}

void SortedMap::removeFirst() {
	int position = this->tail;
	this->tail = this->nextList[this->tail];
	this->previousList[this->tail] = -1;
	this->nextList[position] = this->firstFree;
	this->previousList[this->firstFree] = position;
	this->firstFree = position;
	this->setLinks();
	this->elements[position] = NULL_TELEM;
}

void SortedMap::removeLast() {
	int position = this->head;
	this->head = this->previousList[this->head];
	this->nextList[position] = this->firstFree;
	this->previousList[this->firstFree] = position;
	this->firstFree = position;
	this->setLinks();
	this->elements[position] = NULL_TELEM;
}

void SortedMap::removeBetween(int position) {
	int prev = this->previousList[position];
	int next = this->nextList[position];
	this->nextList[prev] = next;
	this->previousList[next] = prev;
	this->nextList[position] = this->firstFree;
	this->previousList[this->firstFree] = position;
	this->firstFree = position;
	this->setLinks();
	this->elements[position] = NULL_TELEM;
}

void SortedMap::removeOnlyElement() {
	this->elements[this->tail] = NULL_TELEM;
	this->firstFree = this->head;
}

TValue SortedMap::add(TKey key, TValue val) {
	if (this->firstFree == -1) this->resize();

	if (this->numberElements == 0) {
		this->addEmptyList(key, val);
		this->numberElements++;
		return NULL_TVALUE;
	}

	int position = this->searchElement(key);
	if (this->elements[position].first == key) {
		TValue oldVal = this->elements[position].second;
		this->elements[position].second = val;
		return oldVal;
	}
	else if (this->elements[position] == NULL_TELEM) this->addAfterLast(key, val);
	else if (position == this->tail) this->addBeforeFirst(key, val);
	else this->addBetween(this->previousList[position], key, val);
	this->numberElements++;
	return NULL_TVALUE;
}

TValue SortedMap::search(TKey key) const{
	int position = this->searchElement(key);
	if (position != -1 && this->elements[position].first == key) return this->elements[position].second;
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey key) {
	if (this->numberElements == 0) return NULL_TVALUE;

	int position = this->searchElement(key);
	if (position == -1 || this->elements[position] == NULL_TELEM || this->elements[position].first != key) return NULL_TVALUE;
	TValue oldVal;
	if (position == this->tail && this->tail == this->head && this->elements[this->tail].first == key) {
		oldVal = this->elements[this->tail].second;
		this->removeOnlyElement();
	}
	if (position == this->tail && this->elements[position].first == key) {
		oldVal = this->elements[this->tail].second;
		this->removeFirst();
	}
	else if (position == this->head && this->elements[position].first == key) {
		oldVal = this->elements[this->head].second;
		this->removeLast();
	}
	else if (this->elements[position].first == key) {
		oldVal = this->elements[position].second;
		this->removeBetween(position);
	}
	this->numberElements--;
	return oldVal;
}

int SortedMap::size() const { return this->numberElements; }

bool SortedMap::isEmpty() const { return (this->numberElements == 0); }

SMIterator SortedMap::iterator() const { return SMIterator(*this); }

SortedMap::~SortedMap() {}
