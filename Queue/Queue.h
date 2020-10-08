#pragma once
using namespace std;

typedef int TElem;
#define NULL_TELEM -11111

class Queue
{
private:
	TElem* elems;
	int capacity;
	int rear;
	int front;

private:
	void resize();

public:
	Queue();

	void push(TElem e);

	TElem top() const noexcept(false);

	TElem pop() noexcept(false);

	bool isEmpty() const;

	~Queue();
};
