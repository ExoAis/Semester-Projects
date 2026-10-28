#include "InformationList.h"
#include <iostream>
using namespace std;

InformationList::InformationList(string** content, int idx) {
	this->idx = idx;
	for (int i = 0; i < 15; i++) {
		if (i == 7) {
			continue;
		}
		insertTail(content[idx][i]);
	}
}
NodeLL* InformationList::getNewNode(string k) {
	NodeLL* node = new NodeLL;
	node->info = k;
	node->next = nullptr;
	node->prev = nullptr;
	return node;
}
void InformationList::insertHead(string k) {
	NodeLL* node = getNewNode(k);
	if (head == nullptr) {
		head = node;
		end = node;
		return;
	}
	node->next = head;
	head->prev = node;
	head = node;
}
void InformationList::insertTail(string k) {
	NodeLL* node = getNewNode(k);
	if (head == nullptr) {
		head = node;
		end = node;
		return;
	}
	end->next = node;
	node->prev = end;
	end = node;
}
void InformationList::insertNth(int pos, string k) {
	NodeLL* temp = new NodeLL; NodeLL* temp1 = new NodeLL;
	temp = head;
	for (int i = 0; i < pos - 2; i++) {
		temp = temp->next;
		temp1 = temp->next;
	}
	NodeLL* node = getNewNode(k);
	temp->next = node;
	temp1->prev = node;
	node->prev = temp;
	node->next = temp1;
	temp = nullptr;
	temp1 = nullptr;
}
string InformationList::getInfo(int pos) {
	NodeLL* start;
	start = head;
	for (int i = 0; i < pos - 1; i++) {
		start = start->next;
	}
	return start->info;
}
void InformationList::printForward() {
	NodeLL* temp = head;
	if (temp == nullptr) {
		return;
	}
	int i = 0;
	cout << endl;
	while (temp != nullptr) {
		cout << i + 1 << ": " << temp->info << endl;
		temp = temp->next;
		i++;
	}
	cout << endl;
}
void InformationList::printBackward() {
	NodeLL* temp = end;
	if (temp == nullptr) {
		return;
	}
	cout << endl;
	int i = 0;
	while (temp != nullptr) {
		cout << i + 1 << ": " << temp->info << endl;
		temp = temp->prev;
		i++;
	}
	cout << endl;
}
bool InformationList::searchVal(string n) {
	if (head == nullptr || (head->next == nullptr && head->prev == nullptr)) {
		return false;
	}
	NodeLL* start = head;
	while (start != nullptr) {
		if (start->info == n) {
			cout << "Information is Found" << endl;
			return true;
		}
		start = start->next;
	}
	cout << "Information is Not Found" << endl;
	return false;
}
void InformationList::deleteNode(int pos) {
	NodeLL* temp;
	temp = head;
	for (int i = 0; i < pos - 1; i++) {
		temp = temp->next;
	}
	if (temp->next == nullptr) {
		end = end->prev;
		end->next = nullptr;
		temp->next = nullptr;
		delete temp;
		return;
	}
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	delete temp;
	return;
}
void InformationList::destroyList() {
	NodeLL* temp;
	while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}
	head = end = nullptr;
}
string InformationList::deleteFront() {
	NodeLL* temp = head;
	string k = head->info;
	head = head->next;
	head->prev = nullptr;
	delete temp;
	return k;
}
string InformationList::deleteBack() {
	NodeLL* temp = end;
	end = end->prev;
	end->next = nullptr;
	string k = temp->info;
	temp->next = nullptr;
	temp->prev = nullptr;
	delete temp;
	return k;
}
string* InformationList::getGenres(string** content) {
	string* genres = new string[3];
	string genre_s = content[idx][11];
	string genre = "";
	int index = 0;
	for (int i = 0; i < genre_s.length(); i++) {
		if (index == 3) {
			break;
		}
		if (genre_s[i] == ',') {
			genres[index] = genre;
			index++;
			genre = "";
			continue;
		}
		genre += genre_s[i];
	}
	if (index != 3) {
		if (genre[genre.length() - 1] != ',') {
			genres[index] = genre;
		}
	}
	return genres;
}