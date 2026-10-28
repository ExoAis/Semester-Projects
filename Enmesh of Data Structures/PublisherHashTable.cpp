#include "PublisherHashTable.h"
#include <iostream>
using namespace std;

int collisions = 0;
PublisherHashTable::PublisherHashTable(string** content) {
	string publisher;
	initializeHashTable();
	for (int i = 0; i < 29000; i++) {
		if (i == 0) {
			continue;
		}
		if (content[i][7] == "-1") {
			continue;
		}
		publisher = content[i][7];
		insertPublisher(content, publisher);
		for (int j = i; j < 29000; j++) {
			if (content[j][7] == publisher) {
				content[j][7] = "-1";
			}
		}
	}
	double percen = ((double)collisions / (double)inUse) * 100;
	cout << percen << "% collisions" << endl;
}
void PublisherHashTable::initializeHashTable() {
	for (int i = 0; i < size; i++) {
		publisherTable[i] = nullptr;
	}
}
void PublisherHashTable::insertPublisher(string** content, string publisher) {
	NodeHash* nn = getNewNode(content, publisher);
	int idx = hashFunction(publisher);
	if (publisherTable[idx] != nullptr) {
		collisions++;
		collisionHandler(nn, idx);
		return;
	}
	publisherTable[idx] = nn;
	inUse++;
}
void PublisherHashTable::deletePublisher(string publisher) {
	int idx = searhHelper(publisher);
	if (idx == -2) {
		cout << "Hash Table Is Empty" << endl;
		return;
	}
	else if (idx == -1) {
		cout << "Publisher Is Not Found" << endl;
		return;
	}
	publisherTable[idx]->games->destroyTree(publisherTable[idx]->games->root);
	delete[] publisherTable[idx];
	publisherTable[idx] = nullptr;
	size--;
}
int PublisherHashTable::searhHelper(string publisher) {
	if (inUse == 0) {
		return -2;
	}
	int index = hashFunction(publisher);
	int i = 1;
	int idx = index;
	int coll = 0;
	while (publisherTable[idx]->publisher != publisher && publisherTable[index]->collisionCounter != coll) {
		idx = (hashFunction(publisher) + i * i) % size;
		i++;
		coll++;
	}
	if (publisherTable[index]->collisionCounter < coll) {
		return -1;
	}
	return idx;
}
void PublisherHashTable::search(string publisher, string game) {
	int isThere = searhHelper(publisher);
	if (isThere == -1 || isThere == -2) {
		cout << "Publisher Is Not Found" << endl;
		return;
	}
	cout << "Games Associated With Searched Publisher Are" << endl;
	publisherTable[isThere]->games->inOrderTraversal(publisherTable[isThere]->games->root);
	cout << "Information List of " << game << " Is" << endl;
	publisherTable[isThere]->games->getGameNode(publisherTable[isThere]->games->root, game);
	NodeAVL* reqNode = publisherTable[isThere]->games->gameNode;
	if (reqNode == nullptr) {
		cout << "Game Is Not Found" << endl;
		return;
	}
	reqNode->information->printForward();
	cout << "Games With Similar Genres As The Aforementioned Game Are" << endl;
	NodeGraph* graph = publisherTable[isThere]->games->searchIfGraphExists();
	graph->adjGames->inOrderTraversal(graph->adjGames->root);
}
NodeHash* PublisherHashTable::getNewNode(string** content, string publisher) {
	NodeHash* newNode = new NodeHash;
	newNode->publisher = publisher;
	newNode->games = new GameTree(content, publisher);
	return newNode;
}
int PublisherHashTable::hashFunction(string publisher) {
	int idx = 0;
	int p = 31;
	for (int i = 0; i < publisher.length(); i++) {
		idx += (publisher[i] * (int)pow(p, i)) % size;
	}
	return abs(idx % size);
}
void PublisherHashTable::collisionHandler(NodeHash* publisher, int index) {
	int idx = quadProbing(publisher->publisher, index);
	if (idx == -1) {
		cout << "Hash Table Is Full" << endl;
		return;
	}
	publisherTable[idx] = publisher;
	inUse++;
}
int PublisherHashTable::quadProbing(string publisher, int index) {
	int idx = index;
	int i = 1;
	while (publisherTable[idx] != nullptr) {
		idx = (hashFunction(publisher) + i * i) % size;
		i++;
		publisherTable[index]->collisionCounter++;
		if (inUse == size) {
			return -1;
		}
	}
	return idx;
}
NodeHash** PublisherHashTable::returnHashTable() {
	return publisherTable;
}
void PublisherHashTable::DestroyPublisherHashTable() {
	for (int i = 0; i < 19500; i++) {
		if (publisherTable[i] == nullptr) {
			continue;
		}
		publisherTable[i]->games->destroyTree(publisherTable[i]->games->root);
		delete publisherTable[i];
		publisherTable[i] = nullptr;
	}
	delete[] publisherTable;
}