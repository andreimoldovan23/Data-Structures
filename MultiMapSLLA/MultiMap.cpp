#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
	this->tail = -1;
	this->head = -1;
	this->numberElements = 0;
	this->capacity = 10;
	for (int i = 0; i < this->capacity; i++) {
		this->elements.push_back(NULL_TELEM);
		this->nextList.push_back(i + 1);
	}
	this->nextList[this->capacity - 1] = -1;
	this->firstFree = 0;
}

void MultiMap::resize() {
	for (int i = this->capacity; i < 2 * this->capacity; i++) {
		this->elements.push_back(NULL_TELEM);
		this->nextList.push_back(i + 1);
	}
	this->nextList[2 * this->capacity - 1] = -1;
	this->firstFree = this->capacity;
	this->nextList[this->head] = this->firstFree;
	this->capacity *= 2;
}

int MultiMap::searchElement(TKey key, TValue val) const {
	int currentPosition = this->tail;
	int nextPosition = this->nextList[currentPosition];
	if (this->elements[currentPosition].first == key && this->elements[currentPosition].second == val) return currentPosition;
	while (nextPosition != -1 && this->elements[nextPosition] != NULL_TELEM &&
		!(this->elements[nextPosition].first == key && this->elements[nextPosition].second == val)) {
		currentPosition = nextPosition;
		nextPosition = this->nextList[currentPosition];
	}
	return currentPosition;
}

void MultiMap::add(TKey key, TValue val) {
	if (this->firstFree == -1) this->resize();
	if (this->numberElements == 0) {
		this->elements[this->firstFree] = TElem(key, val);
		this->tail = this->firstFree;
		this->head = this->firstFree;
	}
	else {
		int position = this->nextList[this->head];
		this->elements[position] = TElem(key, val);
		this->head = position;
	}

	this->firstFree = this->nextList[this->firstFree];
	this->nextList[this->head] = this->firstFree;
	this->numberElements++;
}

bool MultiMap::remove(TKey key, TValue val) {
	if (this->numberElements == 0) return false;
	int positionElement = this->searchElement(key, val);
	if (this->elements[positionElement].first == key && this->elements[positionElement].second == val) {
		if (this->head == this->tail) {
			this->elements[positionElement] = NULL_TELEM;
		}
		else {
			this->tail = this->nextList[this->tail];
			this->nextList[positionElement] = this->firstFree;
			this->firstFree = positionElement;
			this->nextList[this->head] = this->firstFree;
			this->elements[positionElement] = NULL_TELEM;
		}
		this->numberElements--;
		return true;
	}

	else if (this->elements[this->nextList[positionElement]].first == key && this->elements[this->nextList[positionElement]].second == val) {
		int nextPosition = this->nextList[positionElement];
		if (nextPosition == this->head)
			this->head = positionElement;
		this->nextList[positionElement] = this->nextList[nextPosition];
		this->elements[nextPosition] = NULL_TELEM;
		this->nextList[nextPosition] = this->firstFree;
		this->firstFree = nextPosition;
		this->nextList[this->head] = this->firstFree;
		this->numberElements--;
		return true;
	}
	return false;
}

vector<TValue> MultiMap::search(TKey c) const {
	if(this->numberElements == 0) return vector<TValue>();
	vector<TValue> values;
	int currentPosition = this->tail;
	while (currentPosition != -1 && this->elements[currentPosition] != NULL_TELEM)
	{
		if (this->elements[currentPosition].first == c)
			values.push_back(this->elements[currentPosition].second);
		currentPosition = this->nextList[currentPosition];
	}
	return values;
}

int MultiMap::size() const { return this->numberElements; }

bool MultiMap::isEmpty() const { return (this->numberElements == 0); }

MultiMapIterator MultiMap::iterator() const { return MultiMapIterator(*this); }

MultiMap::~MultiMap() {}

