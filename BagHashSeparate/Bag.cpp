#include "Bag.h"
#include "BagIterator.h"
#include <algorithm>
#include <exception>
#include <iostream>
using namespace std;

Bag::Bag() {
	this->nrSlots = 16;
	for (int i = 0; i < this->nrSlots; i++)
		this->table.push_back(NULL);
	this->hf = multiplyHash;
	this->nrOccupiedSlots = 0;
	this->nrElements = 0;
	this->loadFactor = 0;
}

void Bag::resizeAndRehash() {
	this->nrOccupiedSlots = 0;
	vector<Node*> newTable;
	for (int i = 0; i < 2 * this->nrSlots; i++)
		newTable.push_back(NULL);
	for (int i = 0; i < this->nrSlots; i++) {
		if (this->table[i] == NULL) continue;
		Node* node = this->table[i];
		while(node != NULL){
			TKey key = node->info.first;
			int freq = node->info.second;
			int newSlot = this->hf(key, 2 * this->nrSlots);
			if (newTable[newSlot] == NULL) {
				newTable[newSlot] = allocateNode(key, freq);
				this->nrOccupiedSlots++;
			}
			else {
				Node* currentNode = searchNode(newTable[newSlot], key);
				currentNode->next = allocateNode(key, freq);
			}
			node = node->next;
		}
		deallocateNode(this->table[i]);
	}
	this->nrSlots *= 2;
	this->table = newTable;
	this->loadFactor = this->nrOccupiedSlots / this->nrSlots;
}

void Bag::add(TKey elem) {
	if (this->loadFactor > threshhold)	this->resizeAndRehash();
	this->nrElements++;
	int slot = this->hf(elem, this->nrSlots);
	if (this->table[slot] == NULL) {
		this->table[slot] = allocateNode(elem, 1);
		this->nrOccupiedSlots++;
		this->loadFactor = this->nrOccupiedSlots / this->nrSlots;
		return;
	}
	else {
		Node* currentNode = searchNode(this->table[slot], elem);
		if (currentNode->info.first == elem)
			currentNode->info.second++;
		else if (currentNode->next == NULL){
			currentNode->next = allocateNode(elem, 1);
			return;
		}
		else
			currentNode->next->info.second++;
	}
}

bool Bag::remove(TKey elem) {
	int slot = this->hf(elem, this->nrSlots);
	if (this->table[slot] == NULL) return false;
	else {
		Node* currentNode = searchNode(this->table[slot], elem);
		if (currentNode->info.first == elem) {
			currentNode->info.second--;
			if (currentNode->info.second == 0) {
				this->table[slot] = currentNode->next;
				delete currentNode;
				if (this->table[slot] == NULL) {
					this->nrOccupiedSlots--;
					this->loadFactor = this->nrOccupiedSlots / this->nrSlots;
				}
			}
			this->nrElements--;
			return true;
		}
		else if (currentNode->next == NULL) return false;
		else {
			currentNode->next->info.second--;
			if (currentNode->next->info.second == 0) {
				Node* aux = currentNode->next;
				currentNode->next = currentNode->next->next;
				delete aux;
			}
			this->nrElements--;
			return true;
		}
	}
}

bool Bag::search(TKey elem) const {
	int slot = this->hf(elem, this->nrSlots);
	if (this->table[slot] == NULL) return false;
	Node* currentNode = searchNode(this->table[slot], elem);
	if (currentNode->info.first == elem || currentNode->next != NULL) return true;
	return false;
}

int Bag::nrOccurrences(TKey elem) const {
	int slot = this->hf(elem, this->nrSlots);
	if (this->table[slot] == NULL) return 0;
	Node* currentNode = searchNode(this->table[slot], elem);
	if (currentNode->info.first == elem) return currentNode->info.second;
	else if (currentNode->next == NULL) return 0;
	else return currentNode->next->info.second;
}

int Bag::size() const { return this->nrElements; }

bool Bag::isEmpty() const { return (this->size() == 0); }

BagIterator Bag::iterator() const { return BagIterator(*this); }

Bag::~Bag() {
	for (int i = 0; i < this->nrSlots; i++) if (this->table[i] != NULL) deallocateNode(this->table[i]);
}

