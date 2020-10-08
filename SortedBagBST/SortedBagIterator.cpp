#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& bag) : bag(bag) {
	this->traverse(this->bag.root);
	this->currentPosition = 0;
}

void SortedBagIterator::traverse(Node* node) {
	if (node != NULL) {
		this->traverse(node->left);
		this->inorder.push_back(node);
		this->traverse(node->right);
	}
}

TComp SortedBagIterator::getCurrent() {
	if (!this->valid()) throw exception("Invalid iterator");
	return this->inorder[this->currentPosition]->info;
}

bool SortedBagIterator::valid() {
	return (this->inorder.empty() || this->currentPosition >= this->inorder.size()) ? false : true;
}

void SortedBagIterator::next() {
	if (!this->valid()) throw exception("Invalid iterator");
	this->currentPosition++;
}

void SortedBagIterator::first() { this->currentPosition = 0; }

