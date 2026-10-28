#ifndef NODEBST_H
#define NODEBST_H
class NodeAVL;
#include "NodeAVL.h"

class NodeBST {
	public:
		NodeBST* left;
		NodeAVL* data;
		std::string game;
		std::string info;
		NodeBST* right;
};

#endif
