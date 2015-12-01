#include "../includes/Symboltable.h"
#include <iostream>
#include "../includes/InfoInd.h"
using namespace std;

int main(int argc, char **argv) {
	Symboltable* symboltable = new Symboltable();
	symboltable->init();
	const int size = 30;
	struct TestType {
		char* string;
		int size;
		int x;
		int y;
	};
	TestType test[size] = {
		{ "hallo",5,1,1 },
		{ "hallo",10,0,0 },
		{ "",0 },
		{ "",2 },
		{ "hallosigfhfuesfhoi213",20 },
		{ "ahllo",5 },
		{ "aba",5 },
		{ "baa",5 },
		{ "aab",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
		{ "hallo",5 },
	};
	for (int i = 0; i < size; i++) {
		auto info = symboltable->insert(test[i].string, test[i].x, test[i].y);
		if (info != 0) {
			cout << info ->getInfo() << " " << info->getX() << " " << info->getY() << endl;
		}	
	};


	while (1);
}
