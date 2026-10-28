#ifndef InformationList_H
#define InformationList_H
#include "NodeLL.h"

class InformationList {
	private:
		NodeLL* head = nullptr;
		NodeLL* end = nullptr;
		int idx = 0;
	public:
		InformationList(std::string** content, int idx);
		NodeLL* getNewNode(std::string k);
		void insertHead(std::string k);
		void insertTail(std::string k);
		void insertNth(int pos, std::string k);
		std::string getInfo(int pos);
		void printForward();
		void printBackward();
		std::string* getGenres(std::string** content);
		bool searchVal(std::string n);
		void deleteNode(int pos);
		void destroyList();
		std::string deleteFront();
		std::string deleteBack();
};

#endif
