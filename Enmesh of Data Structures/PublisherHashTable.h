#ifndef PUBLISHERHASHTABLE_H
#define PUBLISHERHASHTABLE_H
class NodeHash;
#include "NodeHash.h"

class PublisherHashTable {
	private:
		int size = 19500;
		int inUse = 0;
		NodeHash** publisherTable = new NodeHash*[size];
	public:
		PublisherHashTable(std::string** content);
		void initializeHashTable();
		void insertPublisher(std::string** content, std::string publisher);
		void deletePublisher(std::string publisher);
		int searhHelper(std::string publisher);
		void search(std::string publisher, std::string game);
		NodeHash* getNewNode(std::string** content, std::string publisher);
		int hashFunction(std::string publisher);
		void collisionHandler(NodeHash* publisher, int index);
		int quadProbing(std::string publisher, int index);
		NodeHash** returnHashTable();
		void DestroyPublisherHashTable();
};

#endif
