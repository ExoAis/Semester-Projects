#include "GraphRelated.h"
#include <iostream>
using namespace std;

GraphRelated::GraphRelated(NodeHash** publisherTable, string** content) {
	GameTree* entry;
	GameTree* root;
	NodeAVL* g;
	NodeAVL* searchedNode;
	int random = 0;
	int n = 0;
	string* genres;
	string genre1, genre2, genre3;
	for (int i = 0; i < 19500; i++) {
		if (publisherTable[i] == nullptr) {
			continue;
		}
		if (n % 50 == 0) {
			start = end = nullptr;
			root = publisherTable[i]->games;
			root->countNodes(root->root);
			random = root->generateRandom();
			genres = root->root->information->getGenres(content);
			genre1 = genres[0];
			genre2 = genres[1];
			genre3 = genres[2];
			g = root->randomNode(random);
			insertVertex(g);
		}
		else {
			entry = publisherTable[i]->games;
			searchedNode = entry->searchForGraph(content, genre1, genre2, genre3);
			if (searchedNode != nullptr) {
				insertVertex(searchedNode);
			}
		}
		n++;
	}
}
NodeGraph* GraphRelated::getVertex(NodeAVL* game) {
	NodeGraph* newNode = new NodeGraph;
	newNode->bottom = nullptr;
	newNode->weight = 1;
	newNode->pred = nullptr;
	newNode->adjGames = new RelatedBST;
	newNode->held = game;
	return newNode;
}
void GraphRelated::insertVertex(NodeAVL* game) {
	NodeGraph* nn = getVertex(game);
	if (start == nullptr && end == nullptr) {
		start = nn; end = nn;
	}
	else {
		end->bottom = nn;
		end = nn;
	}
	NodeGraph* temp = start;
	NodeGraph* temp_;
	while (temp != nullptr) {
		if (temp->held != game) {
			temp->adjGames->insertNode(temp->adjGames->root, game);
		}
		else {
			game->relatedGame = temp;
			game->head = start;
			game->last = end;
			temp_ = start;
			while (temp_ != temp) {
				temp->adjGames->insertNode(temp->adjGames->root, temp_->held);
				temp_ = temp_->bottom;
			}
		}
		temp = temp->bottom;
	}
}
void GraphRelated::deleteVertex(string game) {
	if (start == nullptr) {
		return;
	}
	NodeAVL* dNode; NodeGraph* temp;
	if (start->held->game == game) {
		dNode = start->held;
		start->adjGames->destroyTree(start->adjGames->root);
		NodeGraph* temp = start;
		if (start == end) {
			start = start->bottom;
			end = start;
		}
		else {
			start = start->bottom;
			temp = start;
			while (temp != nullptr) {
				temp->adjGames->deleteNode(dNode);
				temp = temp->bottom;
			}
		}
		delete temp;
		cout << "Game Is Found. Vertex Is Deleted Successfully" << endl;
		return;
	}
	deleteHelper(game);
	if (curr->held->game == game) {
		dNode = curr->held;
		curr->adjGames->destroyTree(curr->adjGames->root);
		prev->bottom = curr->bottom;
		if (curr == end) {
			end = prev;
		}
		temp = start;
		while (temp != nullptr) {
			temp->adjGames->deleteNode(dNode);
			temp = temp->bottom;
		}
		delete curr;
		cout << "Game Is Found. Vertex Is Deleted Successfully" << endl;
		return;
	}
	cout << "Game Is Not Found. Deletion Is Not Possible" << endl;
}
void GraphRelated::deleteHelper(string game) {
	curr = start->bottom; prev = start;
	while (curr != nullptr && curr->held->game != game) {
		curr = curr->bottom;
		prev = prev->bottom;
	}
}
void GraphRelated::searchAdj(NodeGraph* node) {
	if (node == nullptr) {
		cout << "No Suggestions Are Found. Game Does Not Exist" << endl;
		return;
	}
	cout << endl;
	cout << "Games With Similar Genres Are: " << endl;
	node->adjGames->inOrderTraversal(node->adjGames->root);
	cout << endl;
}
void GraphRelated::destroyGraph(NodeAVL* n, NodeGraph* start, NodeGraph* end) {
	if (start == nullptr && end == nullptr) {
		return;
	}
	if (n->isDeleteGraph) {
		return;
	}
	NodeAVL* node;
	NodeGraph* temp = start;
	while (temp != nullptr) {
		node = start->held;
		node->isDeleteGraph = true;
		start = start->bottom;
		temp->adjGames->destroyTree(temp->adjGames->root);
		delete temp;
		temp = start;
	}
	end = nullptr;
}