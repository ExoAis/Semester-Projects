#include "Parser.h"
#include "EncapsulateAll.h"

//Out Of Count For Retrieval Node Total Count For AVL Tree ////ALSO DONE

int main() {
	Parse();
	EncapsulateAll* project = new EncapsulateAll(content);
	for (int i = 0; i < 15; i++) {
		delete[] content[i];
	}
	delete[] content;
	delete project;
	project = nullptr;

	return 0;
}