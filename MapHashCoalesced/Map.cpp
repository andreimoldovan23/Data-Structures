#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->nrOccupied = 0;
	this->nrSlots = 16;
	this->loadFactor = 0;
	for (int i = 0; i < this->nrSlots; i++) {
		this->next.push_back(-1);
		this->table.push_back(NULL_TELEM);
	}
	this->hf = multiplyHash;
	this->firstFree = 0;
}

void Map::resizeAndRehash() {
	vector<TElem> newTable;
	vector<int> newNext;
	
	for (int i = 0; i < 2 * this->nrSlots; i++) {
		newTable.push_back(NULL_TELEM);
		newNext.push_back(-1);
	}

	this->nrOccupied = 0;
	this->firstFree = 0;
	for (int i = 0; i < this->nrSlots; i++) {
		if (this->table[i] == NULL_TELEM) continue;
		TElem e = this->table[i];
		int newSlot = this->hf(e.first, 2*this->nrSlots);		
		if (newTable[newSlot] == NULL_TELEM) {
			newTable[newSlot] = e;
			if (newSlot == this->firstFree) this->firstFree = findFirstFree(newTable, 2 * this->nrSlots);
		}
		else {
			while (newNext[newSlot] != -1) newSlot = newNext[newSlot];
			newNext[newSlot] = this->firstFree;
			newTable[this->firstFree] = e;
			this->firstFree = findFirstFree(newTable, 2 * this->nrSlots);
		}
		this->nrOccupied++;
	}
	this->nrSlots *= 2;
	this->table = newTable;
	this->next = newNext;
	this->loadFactor = this->nrOccupied / this->nrSlots;
}

Map::~Map() {}

TValue Map::add(TKey key, TValue val){
	if (this->loadFactor > threshhold) this->resizeAndRehash();
	
	int slot = this->hf(key, this->nrSlots);
	if (this->table[slot] == NULL_TELEM) {
		this->table[slot] = TElem(key, val);
		if (this->firstFree == slot) this->firstFree = findFirstFree(this->table, this->nrSlots);
		this->nrOccupied++;
		this->loadFactor = this->nrOccupied / this->nrSlots;
		return NULL_TVALUE;
	}
	else {
		int currentPosition = slot;
		while (this->next[currentPosition] != -1 && this->table[currentPosition].first != key) currentPosition = this->next[currentPosition];
		if (this->table[currentPosition].first == key) {
			TValue oldValue = this->table[currentPosition].second;
			this->table[currentPosition].second = val;
			return oldValue;
		}
		else {
			this->table[this->firstFree] = TElem(key, val);
			this->next[currentPosition] = this->firstFree;
			this->firstFree = findFirstFree(this->table, this->nrSlots);
			this->nrOccupied++;
			this->loadFactor = this->nrOccupied / this->nrSlots;
			return NULL_TVALUE;
		}
	}
}

TValue Map::search(TKey key) const{
	int slot = this->hf(key, this->nrSlots);
	if (this->table[slot] == NULL_TELEM) return NULL_TVALUE;
	else {
		while (this->next[slot] != -1 && this->table[slot].first != key) slot = this->next[slot];
		if (this->table[slot].first == key) return this->table[slot].second;
		return NULL_TVALUE;
	}
}

TValue Map::remove(TKey key){
	int slot = this->hf(key, this->nrSlots);
	if (this->table[slot] == NULL_TELEM) return NULL_TVALUE;
	else {
		int previous = -1;
		while (this->next[slot] != -1 && this->table[slot].first != key) {
			previous = slot;
			slot = this->next[slot];
		}
		if (this->table[slot].first == key) {
			TValue oldValue = this->table[slot].second;
			bool over = false;
			do {
				int pp = slot;
				int p = this->next[pp];
				while (p != -1 && this->hf(this->table[p].first, this->nrSlots) != slot) {
					pp = p;
					p = this->next[p];
				}
				if (p == -1) over = true;
				else {
					this->table[slot] = this->table[p];
					slot = p;
					previous = pp;
				}
			} while (!over);
			if (previous == -1) {
				int j = 0;
				for (j; j < slot; j++) if (this->next[j] == slot) break;
				previous = j;
			}
			this->next[previous] = this->next[slot];
			this->next[slot] = -1;
			this->table[slot] = NULL_TELEM;
			this->nrOccupied--;
			this->loadFactor = this->nrOccupied / this->nrSlots;
			return oldValue;
		}
		else return NULL_TVALUE;
	}
}

int Map::size() const { return this->nrOccupied; }

bool Map::isEmpty() const { return (this->size() == 0); }

MapIterator Map::iterator() const { return MapIterator(*this); }
