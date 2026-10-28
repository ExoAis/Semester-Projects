#ifndef LLBQ_H
#define LLBQ_H
#include "NodeAV.h"

class LLBQAV {
	private:
		NodeAV* head = nullptr;
		NodeAV* rear = nullptr;
	public:
		void Enqueue(NodeAVL* k);
		void Dequeue();
		bool isEmpty();
		NodeAVL* frontElem();
		void print();
};

#endif
