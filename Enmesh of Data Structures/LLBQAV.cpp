#include "LLBQAV.h"
#include <iostream>
using namespace std;

void LLBQAV::Enqueue(NodeAVL* k) {
	NodeAV* temp = new NodeAV;
	temp->data = k;
	temp->next = nullptr;
	if (isEmpty()) {
		head = rear = temp;
	}
	else {
		rear->next = temp;
		rear = temp;
	}
}
void LLBQAV::Dequeue() {
	NodeAV* temp = head;
	if (isEmpty()) {
		return;
	}
	else if (head == rear) {
		head = rear = nullptr;
	}
	else {
		head = head->next;
	}
	delete temp;
	temp = nullptr;
}
bool LLBQAV::isEmpty() {
	if (head == nullptr && rear == nullptr) {
		return true;
	}
	return false;
}
NodeAVL* LLBQAV::frontElem() {
	if (isEmpty()) {
		return NULL;
	}
	return head->data;
}
void LLBQAV::print() {
	if (isEmpty()) {
		return;
	}
	NodeAV* temp = head;
	while (temp != nullptr) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}