#include "Filter.h"
#include "LLBQAV.h"
#include <iostream>
#include <cstring>
using namespace std;

Filter::Filter(NodeHash** publisherTable) {
	int choice; int col = 0;
	cout << "Do You Want To Filter By: " << endl;
	cout << "1)Release Date" << endl;
	cout << "2)Developer" << endl;
	cout << "3)Tags" << endl;
	cout << "4)Achievements" << endl;
	cout << "5)Price" << endl;
	cin >> choice;
	if (choice == 1) {
		isDate = true;
		col = 6;
	}
	else if (choice == 2) {
		col = 7;
	}
	else if (choice == 3) {
		col = 9;
	}
	else if (choice == 4) {
		col = 11;
	}
	else if (choice == 5) {
		col = 14;
	}
	LLBQAV* games;
	NodeAVL* game;
	for (int i = 0; i < 19500; i++) {
		if (publisherTable[i] == nullptr) {
			continue;
		}
		games = publisherTable[i]->games->storeAllGames();
		while (!games->isEmpty()) {
			game = games->frontElem();
			if (game->information->getInfo(col) != "Not Available" && game->information->getInfo(col) != "NotAvailable") {
				insert(root, game->game, game->information->getInfo(col));
			}
			games->Dequeue();
		}
	}
	inOrderTraversal(root);
}
NodeBST* Filter::getNode(std::string game, std::string info) {
	NodeBST* newNode = new NodeBST;
	newNode->data = nullptr;
	newNode->game = game;
	newNode->info = info;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}
void Filter::insert(NodeBST* node, string game, string info) {
	if (!isDate) {
		if (root == nullptr) {
			NodeBST* n = getNode(game, info);
			root = n;
		}
		else if (node != nullptr) {
			if (strcmp(info.c_str(), node->info.c_str()) <= 0) {
				temp = node;
				insert(node->left, game, info);
			}
			else if (strcmp(info.c_str(), node->info.c_str()) > 0) {
				temp = node;
				insert(node->right, game, info);
			}
		}
		else {
			NodeBST* n = getNode(game, info);
			if (strcmp(info.c_str(), temp->info.c_str()) <= 0) {
				temp->left = n;
			}
			else {
				temp->right = n;
			}
		}
		return;
	}
	if (isDate) {
		if (root == nullptr) {
			NodeBST* n = getNode(game, info);
			root = n;
		}
		else if (node != nullptr) {
			if ((DateComparator(info, node->info) == 0) || ((DateComparator(info, node->info) == -1))) {
				temp = node;
				insert(node->left, game, info);
			}
			else if (DateComparator(info, node->info) == 1) {
				temp = node;
				insert(node->right, game, info);
			}
		}
		else {
			NodeBST* n = getNode(game, info);
			if ((DateComparator(info, temp->info) == 0) || (DateComparator(info, temp->info) == -1)) {
				temp->left = n;
			}
			else if (DateComparator(info, temp->info) == 1) {
				temp->right = n;
			}
		}
		return;
	}
	return;
}
void Filter::inOrderTraversal(NodeBST* node) {
	if (node == nullptr) {
		return;
	}
	inOrderTraversal(node->left);
	cout << node->game << " : " << node->info << endl;
	inOrderTraversal(node->right);
}
void Filter::destroyTree(NodeBST* node) {
	if (node == nullptr || root == nullptr) {
		return;
	}
	destroyTree(node->left);
	destroyTree(node->right);
	if (node == root) {
		delete node;
		root = nullptr;
		return;
	}
	delete node;
}
int Filter::DateComparator(string date1, string date2) {
	if ((date1[0] != '0' && date1[0] != '1' && date1[0] != '2' && date1[0] != '3' && date1[0] != '4' && date1[0] != '5' && date1[0] != '6' && date1[0] != '7' && date1[0] != '8' && date1[0] != '9')) {
		return 1;
	}
	int count = 0;
	string td1 = "";
	string td2 = "";
	string d1 = "";
	string m1 = "";
	string y1 = "";
	string d2 = "";
	string m2 = "";
	string y2 = "";
	for (int i = 0; i < date1.length(); i++) {
		if (count == 0) {
			if (date1[i] != '-') {
				d1 += date1[i];
			}
			else {
				count++;
				continue;
			}
		}
		else if (count == 1) {
			if (date1[i] != '-') {
				m1 += date1[i];
			}
			else {
				count++;
				continue;
			}
		}
		else if (count == 2) {
			if (date1[i] != '-') {
				y1 += date1[i];
			}
			else {
				count++;
				break;
			}
		}
	}
	count = 0;
	for (int i = 0; i < date2.length(); i++) {
		if (count == 0) {
			if (date2[i] != '-') {
				d2 += date2[i];
			}
			else {
				count++;
				continue;
			}
		}
		else if (count == 1) {
			if (date2[i] != '-') {
				m2 += date2[i];
			}
			else {
				count++;
				continue;
			}
		}
		else if (count == 2) {
			if (date2[i] != '-') {
				y2 += date2[i];
			}
			else {
				count++;
				break;
			}
		}
	}
	if (d1.length() == 1) {
		td1 = d1[0];
		d1 = "0" + td1;
	}
	if (d2.length() == 1) {
		td2 = d2[0];
		d2 = "0" + td2;
	}
	if (y1[0] == '9' || y1[0] == '8') {
		y1 = "19" + y1;
	}
	else {
		y1 = "20" + y1;
	}
	if (y2[0] == '9' || y2[0] == '8') {
		y2 = "19" + y2;
	}
	else {
		y2 = "20" + y2;
	}
	if (y1 > y2) {
		return 1;
	}
	if (y2 > y1) {
		return -1;
	}
	if (y1 == y2) {
		if (m1 > m2) {
			return 1;
		}
		if (m2 > m1) {
			return -1;
		}
		if (m1 == m2) {
			if (d1 > d2) {
				return 1;
			}
			if (d2 > d1) {
				return -1;
			}
			if (d1 == d2) {
				return 0;
			}
		}
	}
}