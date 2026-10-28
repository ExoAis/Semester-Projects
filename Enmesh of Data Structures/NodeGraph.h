#ifndef NODEGRAPH_H
#define NODEGRAPH_H
class GameTree;
class NodeHash;
class RelatedBST;
class NodeAVL;
#include "GameTree.h"
#include "NodeHash.h"
#include "RelatedBST.h"
#include "NodeAVL.h"

class NodeGraph {
	public:
		int weight;
		NodeGraph* bottom;
		NodeAVL* held;
		NodeGraph* pred;
		RelatedBST* adjGames;
};

#endif
