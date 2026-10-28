#ifndef FILTER_H
#define FILTER _H
#include "NodeBST.h"

class Filter {
	private:
		NodeBST* temp = nullptr;
		bool isDate = false;
	public:
		NodeBST* root = nullptr;
		Filter(NodeHash** publisherTable);
		NodeBST* getNode(std::string game, std::string info);
		void insert(NodeBST* node, std::string game, std::string info);
		void inOrderTraversal(NodeBST* node);
		void destroyTree(NodeBST* node);
		int DateComparator(std::string date1, std::string date2);
};

#endif
