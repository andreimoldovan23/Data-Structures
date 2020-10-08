#include "Queue.h"
#include <exception>
#include <iostream>
#include <stdexcept>

using namespace std;


Queue::Queue() {
	this->capacity = 5;
	this->elems = new TElem[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		this->elems[i] = NULL_TELEM;
	this->front = -1;
	this->rear = -1;
}

void Queue::resize() {
	int newCapacity = this->capacity * 2;
	TElem* newElems = new TElem[newCapacity];
	int position = 0;
	for (int i = this->rear; i != this->front; i=(i+1)%this->capacity){
		newElems[position] = this->elems[i];
		position++;
	}
	newElems[position] = this->elems[this->front];
	delete[] this->elems;
	this->elems = newElems;
	this->capacity = newCapacity;
	for (int i = position+1; i < this->capacity; i++)
		this->elems[i] = NULL_TELEM;
	this->front = position;
	this->rear = 0;
}

void Queue::push(TElem elem) {
	if (this->rear == -1) {
		this->rear = 0;
		this->front = 0;
		this->elems[this->front] = elem;
		return;
	}

	if ((this->front + 1) % this->capacity == this->rear)
		this->resize();

	this->front = (this->front + 1) % this->capacity;
	this->elems[this->front] = elem;
}


TElem Queue::top() const {
	if (this->isEmpty())
		throw logic_error("Empty queue");
	return this->elems[this->rear];
}

TElem Queue::pop() {
	if (this->isEmpty())
		throw logic_error("Empty queue");
	TElem toReturn = this->elems[this->rear];
	this->elems[this->rear] = NULL_TELEM;
	this->rear = (this->rear + 1) % this->capacity;
	
	if ((this->front + 1) % this->capacity == this->rear){
		this->rear = -1;
		this->front = -1;
	}

	return toReturn;
}

bool Queue::isEmpty() const {
	if (this->rear == -1) return true;
	return false;
}


Queue::~Queue() {
	delete[] this->elems;
}

