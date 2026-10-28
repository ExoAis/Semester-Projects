#include "GameTree.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

GameTree::GameTree(string** content, string pubName) {
	srand(time(nullptr));
	for (int i = 0; i < 29000; i++) {
		if (content[i][7] == pubName) {
			root = insert(root, content[i][1], i, content);
		}
	}
}
int GameTree::height(NodeAVL* node) {
	if (node == nullptr) {
		return 0;
	}
	return node->height;
}
int GameTree::max(int h1, int h2) {
	if (h1 > h2) {
		return h1;
	}
	return h2;
}
NodeAVL* GameTree::insert(NodeAVL* node, string game, int idx, string** content) {
	if (node == nullptr) {
		return new NodeAVL(game, idx, content);
	}
	if (game < node->game) {
		node->left = insert(node->left, game, idx, content);
	}
	else if (game > node->game) {
		node->right = insert(node->right, game, idx, content);
	}
	else {
		return node;
	}
	int lH = height(node->left);
	int rH = height(node->right);
	node->height = 1 + max(lH, rH);
	int balance = balanceFactor(node);
	if (balance > 1 && game < node->left->game) {
		return rightRotation(node);
	}
	else if (balance < -1 && game > node->right->game) {
		return leftRotation(node);
	}
	else if (balance > 1 && game > node->left->game) {
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}
	else if (balance < -1 && game < node->right->game) {
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}
	return node;
}
bool isDelete = false;
NodeAVL* GameTree::deleteNode(NodeAVL* node, string game) {
	if (!isDelete) {
		deleteNodeHelper(game);
		isDelete = true;
	}
	if (node == nullptr) {
		return node;
	}
	node->left = deleteNode(node->left, game);
	node->right = deleteNode(node->right, game);
	int lH = height(node->left);
	int rH = height(node->right);
	node->height = max(lH, rH) + 1;
	int bf = balanceFactor(node);
	if (bf > 1 && game < node->left->game) {
		return rightRotation(node);
	}
	else if (bf < -1 && game > node->right->game) {
		return leftRotation(node);
	}
	else if (bf > 1 && game > node->left->game) {
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}
	else if (bf < -1 && game < node->right->game) {
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}
	return node;
}
void GameTree::deleteNodeHelper(string game) {
	if (root == nullptr) {
		return;
	}
	else {
		search(game);
		NodeAVL* prev1 = nullptr; NodeAVL* curr1 = nullptr;
		if (curr == nullptr) {
			cout << "Game Is Not Found. Deletion Is Not Possible" << endl;
			return;
		}
		else if (curr->right != nullptr && curr->left != nullptr) {
			if (curr == root) {
				prev = root;
			}
			curr1 = curr;
			prev1 = prev;
			prev = curr1;
			curr = curr1->left;
			while (curr->right != nullptr) {
				prev = curr;
				curr = curr->right;
			}
		}
		if (curr->left != nullptr && curr->right == nullptr) {
			if (curr == root) {
				root = curr->left;
			}
			else if (prev->right == curr) {
				prev->right = curr->left;
			}
			else if (prev->left == curr) {
				prev->left = curr->left;
			}
		}
		else if (curr->right != nullptr && curr->left == nullptr) {
			if (curr == root) {
				root = curr->right;
			}
			else if (prev->right == curr) {
				prev->right = curr->right;
			}
			else if (prev->left == curr) {
				prev->left = curr->right;
			}
		}
		else if (curr->right == nullptr && curr->left == nullptr) {
			if (curr == root) {

			}
			else if (prev->right == curr) {
				prev->right = nullptr;
			}
			else if (prev->left == curr) {
				prev->left = nullptr;
			}
		}
		if (curr1 == nullptr) {
			curr->information->destroyList();
			curr->information = nullptr;
			curr->relatedGame = nullptr;
			if (curr == root) {
				root = nullptr;
			}
			delete curr;
		}
		else {
			if (prev1 == curr1 && curr1 == root) {
				curr->left = root->left;
				curr->right = root->right;
				root = curr;
			}
			else if (prev1->right == curr1) {
				curr->left = curr1->left;
				curr->right = curr1->right;
				prev1->right = curr;
			}
			else if (prev1->left == curr1) {
				curr->left = curr1->left;
				curr->right = curr1->right;
				prev1->left = curr;
			}
			curr1->information->destroyList();
			curr1->information = nullptr;
			curr1->relatedGame = nullptr;
			delete curr1;
		}
		cout << "Game Deleted Successfully" << endl;
	}
}
int GameTree::balanceFactor(NodeAVL* node) {
	if (node == nullptr) {
		return 0;
	}
	return height(node->left) - height(node->right);
}
NodeAVL* GameTree::leftRotation(NodeAVL* node) {
	NodeAVL* x, * y, * z;
	x = node;
	y = x->right;
	z = y->left;
	y->left = x;
	x->right = z;
	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));
	return y;
}
NodeAVL* GameTree::rightRotation(NodeAVL* node) {
	NodeAVL* x, * y, * z;
	x = node;
	y = x->left;
	z = y->right;
	y->right = x;
	x->left = z;
	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));
	return y;
}
void GameTree::inOrderTraversal(NodeAVL* node) {
	if (node == nullptr) {
		return;
	}
	inOrderTraversal(node->left);
	cout << node->game << endl;
	inOrderTraversal(node->right);
}
void GameTree::search(string game) {
	if (root == nullptr) {
		return;
	}
	prev = nullptr;
	curr = root;
	while (curr != nullptr && curr->game != game) {
		if (game < curr->game) {
			prev = curr;
			curr = curr->left;
		}
		else if (game > curr->game) {
			prev = curr;
			curr = curr->right;
		}
	}
}
void GameTree::searchGame(string game) {
	search(game);
	if (curr == nullptr) {
		cout << "Game Is Not Found" << endl;
	}
	else {
		cout << "Game Is Found" << endl;
	}
}
void GameTree::getGameNode(NodeAVL* node, string game) {
	if (node == nullptr) {
		return;
	}
	if (node->game == game) {
		gameNode = node;
		return;
	}
	getGameNode(node->left, game);
	getGameNode(node->right, game);
}
void GameTree::countNodes(NodeAVL* node) {
	if (node == nullptr) {
		return;
	}
	else {
		totalNodes++;
		countNodes(node->left);
		countNodes(node->right);
	}
}
int GameTree::generateRandom() {
	return (rand() % totalNodes) + 1;
}
NodeAVL* GameTree::searchForGraph(string** content, string genre1, string genre2, string genre3) {
	if (root == nullptr) {
		return root;
	}
	LLBQAV queue;
	queue.Enqueue(root);
	NodeAVL* temp;
	string* genres; string genre_1, genre_2, genre_3;
	while (!queue.isEmpty()) {
		temp = queue.frontElem();
		genres = temp->information->getGenres(content);
		genre_1 = genres[0];
		genre_2 = genres[1];
		genre_3 = genres[2];
		if ((genre1 == genre_1 && genre1 != "") || (genre2 == genre_2 && genre2 != "") || (genre3 == genre_3 && genre3 != "")) {
			return temp;
		}
		if (temp->left != nullptr) {
			queue.Enqueue(temp->left);
		}
		if (temp->right != nullptr) {
			queue.Enqueue(temp->right);
		}
		queue.Dequeue();
	}
	return nullptr;
}
LLBQAV* GameTree::storeAllGames() {
	if (root == nullptr) {
		return nullptr;
	}
	LLBQAV queue;
	LLBQAV* games = new LLBQAV;
	queue.Enqueue(root);
	games->Enqueue(root);
	NodeAVL* temp;
	while (!queue.isEmpty()) {
		temp = queue.frontElem();
		if (temp->left != nullptr) {
			queue.Enqueue(temp->left);
			games->Enqueue(temp->left);
		}
		if (temp->right != nullptr) {
			queue.Enqueue(temp->right);
			games->Enqueue(temp->right);
		}
		queue.Dequeue();
	}
	return games;
}
NodeGraph* GameTree::searchIfGraphExists() {
	if (root == nullptr) {
		return nullptr;
	}
	LLBQAV queue;
	queue.Enqueue(root);
	NodeAVL* temp;
	while (!queue.isEmpty()) {
		temp = queue.frontElem();
		if (temp->relatedGame != nullptr) {
			return temp->relatedGame;
		}
		if (temp->left != nullptr) {
			queue.Enqueue(temp->left);
		}
		if (temp->right != nullptr) {
			queue.Enqueue(temp->right);
		}
		queue.Dequeue();
	}
	return nullptr;
}
NodeAVL* GameTree::randomNode(int nodeNum) {
	if (root == nullptr || nodeNum == 1 || totalNodes == 1) {
		return root;
	}
	if (nodeNum > totalNodes) {
		return nullptr;
	}
	int count = 0;
	LLBQAV queue;
	queue.Enqueue(root);
	count++;
	NodeAVL* temp;
	while (!queue.isEmpty()) {
		temp = queue.frontElem();
		if (temp->left != nullptr) {
			queue.Enqueue(temp->left);
			count++;
			if (count == nodeNum) {
				return temp->left;
			}
		}
		if (temp->right != nullptr) {
			queue.Enqueue(temp->right);
			count++;
			if (count == nodeNum) {
				return temp->right;
			}
		}
		queue.Dequeue();
	}
	return nullptr;
}
void GameTree::destroyTree(NodeAVL* node) {
	if (node == nullptr || root == nullptr) {
		return;
	}
	destroyTree(node->left);
	destroyTree(node->right);
	if (node == root) {
		node->information->destroyList();
		node->gameGraph->destroyGraph(node, node->head, node->last);
		node->relatedGame = nullptr;
		delete node;
		root = nullptr;
		return;
	}
	node->information->destroyList();
	node->gameGraph->destroyGraph(node, node->head, node->last);
	node->relatedGame = nullptr;
	delete node;
}