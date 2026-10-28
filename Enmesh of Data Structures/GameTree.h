#ifndef GAMETREE_H
#define GAMETREE_H
class NodeAVL;
class LLBQAV;
#include "NodeAVL.h"
#include "LLBQAV.h"

class GameTree {
	private:
		NodeAVL* prev = nullptr;
		NodeAVL* curr = nullptr;
	public:
		int random = 0;
		int totalNodes = 0;
		NodeAVL* root = nullptr;
		NodeAVL* gameNode = nullptr;
		GameTree(std::string** content, std::string devName);
		int height(NodeAVL* node);
		int max(int h1, int h2);
		int balanceFactor(NodeAVL* node);
		NodeAVL* leftRotation(NodeAVL* node);
		NodeAVL* rightRotation(NodeAVL* node);
		NodeAVL* insert(NodeAVL* node, std::string game, int idx, std::string** content);
		NodeAVL* deleteNode(NodeAVL* node, std::string game);
		void deleteNodeHelper(std::string game);
		void inOrderTraversal(NodeAVL* node);
		void getGameNode(NodeAVL* node, std::string game);
		void search(std::string game);
		LLBQAV* storeAllGames();
		void searchGame(std::string game);
		NodeGraph* searchIfGraphExists();
		void countNodes(NodeAVL* root);
		int generateRandom();
		NodeAVL* searchForGraph(std::string** content, std::string genre1, std::string genre2, std::string genre3);
		NodeAVL* randomNode(int nodeNum);
		void destroyTree(NodeAVL* node);
};

#endif
