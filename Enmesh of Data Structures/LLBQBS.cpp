#include "LLBQBS.h"
#include <iostream>
using namespace std;

void LLBQBS::Enqueue(NodeBST* k) {
	NodeBS* temp = new NodeBS;
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
void LLBQBS::Dequeue() {
	NodeBS* temp = head;
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
bool LLBQBS::isEmpty() {
	if (head == nullptr && rear == nullptr) {
		return true;
	}
	return false;
}
NodeBST* LLBQBS::frontElem() {
	if (isEmpty()) {
		return NULL;
	}
	return head->data;
}
void LLBQBS::print() {
	if (isEmpty()) {
		return;
	}
	NodeBS* temp = head;
	while (temp != nullptr) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}