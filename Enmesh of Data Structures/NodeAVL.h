#ifndef NODEAVL_H
#define NODEAVL_H
class InformationList;
class GraphRelated;
#include "InformationList.h"
#include "GraphRelated.h"

class NodeAVL {
	public:
		NodeAVL* right;
		std::string game;
		InformationList* information;
		NodeGraph* relatedGame;
		NodeGraph* head;
		NodeGraph* last;
		GraphRelated* gameGraph;
		bool isDeleteGraph;
		int height;
		NodeAVL* left;
		NodeAVL(std::string key, int idx, std::string** content) {
			this->head = nullptr;
			this->last = nullptr;
			this->left = this->right = nullptr;
			this->height = 1;
			this->relatedGame = nullptr;
			this->gameGraph = nullptr;
			this->isDeleteGraph = false;
			this->information = new InformationList(content, idx);
			this->game = key;
		}
};

#endif
