#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
	this->tail = NULL;
	this->head = NULL;
	this->numberElements = 0;
}

KeyNode* MultiMap::searchKey(TKey key) const {
	KeyNode* currentNode = this->tail;
	while (currentNode != NULL && currentNode->info.first != key)
		currentNode = currentNode->next;
	return currentNode;
}

ValueNode* MultiMap::searchValue(KeyNode* keyPointer, TValue val) const {
	ValueNode* currentNode = keyPointer->info.second.first;
	while (currentNode != NULL && currentNode->info != val)
		currentNode = currentNode->next;
	return currentNode;
}

void MultiMap::addEmptyList(TKey key, TValue val) {
	this->tail = allocateNode(key, val);
	this->head = this->tail;
}

void MultiMap::addNewElement(TKey key, TValue val) {
	KeyNode* newNode = allocateNode(key, val);
	this->head->next = newNode;
	newNode->previous = this->head;
	this->head = newNode;
}

void MultiMap::addNewValue(KeyNode* keyPointer, TValue val) {
	ValueNode* valuesHead = keyPointer->info.second.second;
	ValueNode* newNode = allocateNode(val);
	valuesHead->next = newNode;
	newNode->previous = valuesHead;
	keyPointer->info.second.second = newNode;
}

void MultiMap::add(TKey key, TValue val) {
	if (this->numberElements == 0) this->addEmptyList(key, val);

	else {
		KeyNode* keyNode = this->searchKey(key);
		if (keyNode == NULL) this->addNewElement(key, val);
		else this->addNewValue(keyNode, val);
	}
	this->numberElements++;
}

void MultiMap::removeKey(KeyNode* keyPointer) {
	KeyNode* previous = keyPointer->previous;
	KeyNode* next = keyPointer->next;
	if (previous == NULL) {
		this->tail = this->tail->next;
		if(this->tail != NULL) this->tail->previous = NULL;
	}
	else if (next == NULL) {
		this->head = previous;
		if (this->head != NULL) this->head->next = NULL;
	}
	else {
		previous->next = next;
		next->previous = previous;
	}
	delete keyPointer;
}

void MultiMap::removeValue(KeyNode* keyPointer, ValueNode* valPointer) {
	ValueNode* previous = valPointer->previous;
	ValueNode* next = valPointer->next;
	ValueNode* valuesTail = keyPointer->info.second.first;
	ValueNode* valuesHead = keyPointer->info.second.second;
	if (previous == NULL) {
		valuesTail = valuesTail->next;
		valuesTail->previous = NULL;
		keyPointer->info.second.first = valuesTail;
	}
	else if (next == NULL) {
		valuesHead = valuesHead->previous;
		valuesHead->next = NULL;
		keyPointer->info.second.second = valuesHead;
	}
	else {
		previous->next = next;
		next->previous = previous;
	}
	delete valPointer;
}

bool MultiMap::remove(TKey key, TValue value) {
	if (this->numberElements == 0) return false;

	KeyNode* keyNode = this->searchKey(key);
	if (keyNode == NULL) return false;

	ValueNode* valNode = this->searchValue(keyNode, value);
	if (valNode == NULL) return false;

	if (keyNode->info.second.first == keyNode->info.second.second) this->removeKey(keyNode);
	else this->removeValue(keyNode, valNode);

	this->numberElements--;
	return true;
}

vector<TValue> MultiMap::search(TKey key) const{
	if (this->numberElements == 0) return vector<TValue>();

	KeyNode* keyNode = this->searchKey(key);
	if(keyNode == NULL) return vector<TValue>();

	vector<TValue> values;
	ValueNode* valTail = keyNode->info.second.first;
	while (valTail != NULL) {
		values.push_back(valTail->info);
		valTail = valTail->next;
	}
	return values;
}

int MultiMap::size() const { return this->numberElements; }

bool MultiMap::isEmpty() const { return (this->numberElements == 0); }

MultiMapIterator MultiMap::iterator() const { return MultiMapIterator(*this); }

MultiMap::~MultiMap() {
	while (this->tail != NULL) {
		KeyNode* currentNode = this->tail;
		this->tail = this->tail->next;
		delete currentNode;
	}
	this->tail = NULL;
	this->head = NULL;
}

