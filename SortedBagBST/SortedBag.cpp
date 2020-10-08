#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->rel = r;
	this->root = NULL;
	this->nrElements = 0;
}

Node* SortedBag::findMaxLeftSubtree(Node* target) const {
	Node* current = target->left;
	if (current == NULL) return NULL;
	while (current->right != NULL) current = current->right;
	return current;
}

Node* SortedBag::findMinRightSubtree(Node* target) const {
	Node* current = target->right;
	if (current == NULL) return NULL;
	while (current->left != NULL) current = current->left;
	return current;
}

void SortedBag::deleteChild(Node* child) {
	Node* parent = child->parent;
	if (parent->left == child) parent->left = NULL;
	else parent->right = NULL;
	deallocateNode(child);
}

Node* SortedBag::findNode(Node* start, TComp elem) const {
	Node* current = start;
	while (current != NULL && current->info != elem) {
		if (this->rel(current->info, elem)) current = current->right;
		else current = current->left;
	}
	return current;
}

void SortedBag::add(TComp elem) {
	if (this->root == NULL) {
		this->root = allocateNode(elem, NULL);
		this->nrElements = 1;
		return;
	}

	Node* current = this->root;
	while (current != NULL) {
		Node* next;
		if (this->rel(current->info, elem)) {
			next = current->right;
			if (next == NULL) {
				current->right = allocateNode(elem, current);
				current->right->parent = current;
			}
		}
		else {
			next = current->left;
			if (next == NULL) {
				current->left = allocateNode(elem, current);
				current->left->parent = current;
			}
		}
		current = next;
	}
	this->nrElements++;
}

bool SortedBag::remove(TComp elem) {
	Node* toRemove = this->findNode(this->root, elem);
	if (toRemove == NULL) return false;

	Node* toReplace;
	if (toRemove->right != NULL) {
		toReplace = this->findMinRightSubtree(toRemove);
		if (toReplace->parent == toRemove) {
			toRemove->right = toReplace->right;
			if(toReplace->right != NULL) toReplace->right->parent = toRemove;
		}
		else if (toReplace->right != NULL) {
			toReplace->parent->left = toReplace->right;
			toReplace->right->parent = toReplace->parent;
		}
		else
			toReplace->parent->left = NULL;
		toRemove->info = toReplace->info;
		delete toReplace;
	}

	else if (toRemove->left != NULL) {
		toReplace = this->findMaxLeftSubtree(toRemove);
		if (toReplace->parent == toRemove) {
			toRemove->left = toReplace->left;
			if(toReplace->left != NULL) toReplace->left->parent = toRemove;
		}
		else if (toReplace->left != NULL) {
			toReplace->parent->right = toReplace->left;
			toReplace->left->parent = toReplace->parent;
		}
		else
			toReplace->parent->right = NULL;
		toRemove->info = toReplace->info;
		delete toReplace;
	}

	else {
		if (toRemove->parent == NULL) {
			delete this->root;
			this->root = NULL;
		}
		else this->deleteChild(toRemove);
	}

	this->nrElements--;
	return true;
}

bool SortedBag::search(TComp elem) const {
	Node* node = this->findNode(this->root, elem);
	if (node == NULL) return false;
	return true;
}

void SortedBag::traverse(Node* node, int* apparitions, TComp elem) const {
	if (node != NULL) {
		traverse(node->left, apparitions, elem);
		if (node->info == elem) (*apparitions)++;
		traverse(node->right, apparitions, elem);
	}
}

int SortedBag::nrOccurrences(TComp elem) const {
	int nrApparitions = 0;
	this->traverse(this->root, &nrApparitions, elem);
	return nrApparitions;
}

int SortedBag::size() const { return this->nrElements; }

bool SortedBag::isEmpty() const {return (this->size() == 0); }

SortedBagIterator SortedBag::iterator() const { return SortedBagIterator(*this); }

void SortedBag::deleteTree(Node* root) {
	if (root != NULL) {
		deleteTree(root->left);
		deleteTree(root->right);
		deallocateNode(root);
	}
}

SortedBag::~SortedBag() { deleteTree(this->root); }
