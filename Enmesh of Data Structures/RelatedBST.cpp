#include "RelatedBST.h"
#include "LLBQBS.h"
#include <iostream>
using namespace std;

NodeBST* RelatedBST::getNode(NodeAVL* r_game) {
	NodeBST* node = new NodeBST;
	node->data = r_game;
	node->left = node->right = nullptr;
	return node;
}
NodeAVL* RelatedBST::minElement(NodeBST* node) {
	if (node->left == nullptr) {
		return node->data;
	}
	minElement(node->left);
}
NodeAVL* RelatedBST::maxElement(NodeBST* node) {
	if (node->right == nullptr) {
		return node->data;
	}
	maxElement(node->right);
}
void RelatedBST::insertNode(NodeBST* node, NodeAVL* r_game) {
	if (root == nullptr) {
		NodeBST* n = getNode(r_game);
		root = n;
	}
	else if (node != nullptr) {
		if (r_game->game <= node->data->game) {
			temp = node;
			insertNode(node->left, r_game);
		}
		else if (r_game->game > node->data->game) {
			temp = node;
			insertNode(node->right, r_game);
		}
	}
	else {
		NodeBST* n = getNode(r_game);
		if (r_game->game <= temp->data->game) {
			temp->left = n;
		}
		else {
			temp->right = n;
		}
	}
	return;
}
void RelatedBST::levelOrderTraversal(NodeBST* node) {
	if (root == nullptr) {
		return;
	}
	LLBQBS queue;
	queue.Enqueue(root);
	NodeBST* temp;
	while (!queue.isEmpty()) {
		temp = queue.frontElem();
		cout << temp->data->game << " ";
		if (temp->left != nullptr) {
			queue.Enqueue(temp->left);
		}
		if (temp->right != nullptr) {
			queue.Enqueue(temp->right);
		}
		queue.Dequeue();
	}
}
void RelatedBST::inOrderTraversal(NodeBST* node) {
	if (root == nullptr) {
		return;
	}
	else {
		if (node->left != nullptr) {
			inOrderTraversal(node->left);
		}
		cout << node->data->game << endl;
		if (node->right != nullptr) {
			inOrderTraversal(node->right);
		}
	}
}
bool RelatedBST::searchTree(NodeBST* node, NodeAVL* r_game) {
	if (node == nullptr) {
		return false;
	}
	if (r_game->game == node->data->game) {
		return true;
	}
	else if (r_game->game <= node->data->game) {
		searchTree(node->left, r_game);
	}
	else {
		searchTree(node->right, r_game);
	}
}
void RelatedBST::search(NodeAVL* r_game) {
	prev = nullptr;
	curr = root;
	while (curr != nullptr && curr->data->game != r_game->game) {
		prev = curr;
		if (r_game->game > curr->data->game) {
			curr = curr->right;
		}
		else if (r_game->game <= curr->data->game) {
			curr = curr->left;
		}
	}
}
void RelatedBST::deleteNode(NodeAVL* r_game) {
	if (root == nullptr) {
		return;
	}
	else {
		search(r_game);
		NodeBST* prev1 = nullptr; NodeBST* curr1 = nullptr;
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
			curr->data = nullptr;
			delete curr;
			if (curr == root) {
				root = nullptr;
			}
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
			curr1->data = nullptr;
			delete curr1;
		}
	}
	cout << "Game Is Deleted From BST Attached With Graph Successfully" << endl;
}
void RelatedBST::destroyTree(NodeBST* node) {
	if (root == nullptr) {
		return;
	}
	if (node == nullptr) {
		return;
	}
	destroyTree(node->left);
	destroyTree(node->right);
	if (node == root) {
		node->data = nullptr;
		delete node;
		root = nullptr;
		return;
	}
	node->data = nullptr;
	delete node;
}
