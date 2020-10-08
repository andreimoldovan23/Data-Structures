#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	this->list = NULL;
	this->lenght = 0;
}

Node* MultiMap::searchNode(TKey key, TValue value) const {
	Node* currentNode = this->list;
	if (currentNode->info.first == key && currentNode->info.second == value)
		return currentNode;
	while (currentNode->next != NULL && (currentNode->next->info.first != key || currentNode->next->info.second != value))
		currentNode = currentNode->next;
	return currentNode;
}

void MultiMap::add(TKey key, TValue value) {
	if (this->lenght == 0) this->list = alloc(key, value);
	else {
		Node* currentNode = this->list;
		while (currentNode->next != NULL)
			currentNode = currentNode->next;
		currentNode->next = alloc(key, value);
	}
	this->lenght ++;
}


bool MultiMap::remove(TKey key, TValue value) {
	if (this->lenght == 0) return false;

	Node* previous = this->searchNode(key, value);
	if (previous == this->list && previous->info.first == key && previous->info.second == value) {
		this->list = previous->next;
		dealloc(previous);
		this->lenght--;
		return true;
	}

	if (previous->next == NULL)
		return  false;
	
	Node* toRemove = previous->next;
	previous->next = toRemove->next;
	dealloc(toRemove);
	this->lenght--;
	return true;
}


vector<TValue> MultiMap::search(TKey key) const {
	vector<TValue> values;
	if (this->lenght == 0)	return vector<TValue>();

	Node* currentNode = this->list;
	while (currentNode != NULL) {
		if (currentNode->info.first == key)
			values.push_back(currentNode->info.second);
		currentNode = currentNode->next;
	}

	if (values.size() == 0) return vector<TValue>();
	return values;
}


int MultiMap::size() const { return this->lenght; }


bool MultiMap::isEmpty() const { return (this->lenght == 0) ? true : false; }

MultiMapIterator MultiMap::iterator() const { return MultiMapIterator(*this); }


MultiMap::~MultiMap() {
	Node* currentNode = this->list;
	while (currentNode != NULL) {
		Node* copy = currentNode;
		currentNode = currentNode->next;
		dealloc(copy);
	}
}

