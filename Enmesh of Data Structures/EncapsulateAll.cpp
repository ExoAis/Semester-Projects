#include "EncapsulateAll.h"
#include "Filter.h"
#include <iostream>
#include "string"
using namespace std;

EncapsulateAll::EncapsulateAll(string** content) {
	string publisher; string game; int num = 0;
	PublisherHashTable* publishers = new PublisherHashTable(content);
	NodeHash** publisherHash = publishers->returnHashTable();
	GraphRelated* graphs = new GraphRelated(publisherHash, content);
	cout << "Press -1 To Exit" << endl;
	cin >> num;
	while (num != -1) {
		cin.ignore(256, '\n');
		cout << "Enter The Publisher Name" << endl;
		getline(cin, publisher);
		cout << "Enter The Game Name" << endl;
		getline(cin, game);
		cout << "Entered Publisher: " << publisher << " ---- " << "Entered Game: " << game << endl;
		publishers->search(publisher, game);
		cout << endl << endl;
		Filter* filterBy = new Filter(publisherHash);
		filterBy->destroyTree(filterBy->root);
		cout << "Press -1 To Exit" << endl;
		cin >> num;
	}
	publishers->DestroyPublisherHashTable();
}