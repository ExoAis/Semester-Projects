#ifndef NODEHASH_H
#define NODEHASH_H
class GameTree;
#include "GameTree.h"

class NodeHash {
	public:
		std::string publisher;
		GameTree* games = nullptr;
		int collisionCounter = 0;
};

#endif
