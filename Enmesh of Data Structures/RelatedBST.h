#ifndef RELATEDBST_H
#define RELATEDBST_H
class NodeBST;
#include "NodeBST.h"

class RelatedBST {
	private:
		NodeBST* temp = nullptr;
		NodeBST* prev;
		NodeBST* curr;
	public:
		NodeBST* root = nullptr;
		NodeBST* getNode(NodeAVL* r_game);
		NodeAVL* minElement(NodeBST* node);
		NodeAVL* maxElement(NodeBST* node);
		void insertNode(NodeBST* node, NodeAVL* r_game);
		void levelOrderTraversal(NodeBST* node);
		void inOrderTraversal(NodeBST* node);
		bool searchTree(NodeBST* node, NodeAVL* r_game);
		void search(NodeAVL* r_game);
		void deleteNode(NodeAVL* r_game);
		void destroyTree(NodeBST* node);
};

#endif
