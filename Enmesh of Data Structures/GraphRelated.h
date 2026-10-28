#ifndef GRAPHRELATED_H
#define GRAPHRELATED_H
class NodeGraph;
#include "NodeGraph.h"

class GraphRelated {
	private:
		NodeGraph* prev;
		NodeGraph* curr;
	public:
		NodeGraph* start = nullptr;
		NodeGraph* end = nullptr;
		GraphRelated(NodeHash** publisherTable, std::string** content);
		NodeGraph* getVertex(NodeAVL* game);
		void insertVertex(NodeAVL* game);
		void deleteVertex(std::string game);
		void deleteHelper(std::string game);
		void searchAdj(NodeGraph* node);
		void destroyGraph(NodeAVL* n, NodeGraph* start, NodeGraph* end);
};

#endif
