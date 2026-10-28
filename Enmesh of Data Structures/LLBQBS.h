#ifndef LLBQ1_H
#define LLBQ1_H
#include "NodeBS.h"

class LLBQBS {
	private:
		NodeBS* head = nullptr;
		NodeBS* rear = nullptr;
	public:
		void Enqueue(NodeBST* k);
		void Dequeue();
		bool isEmpty();
		NodeBST* frontElem();
		void print();
};

#endif

