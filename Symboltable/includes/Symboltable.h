/*
* Symboltable.h
*
*  Created on: Sep 26, 2012
*      Author: knad0001
*/

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "SymtabEntry.h"
class Symboltable {
private:
	int size;
	SymtabEntry** symboltable;
	int hash(char* lexem);
public:
	Symboltable();
	~Symboltable();

	Information *insert(char *lexem, int x, int y);

	Information *lookup(char *lexem);
	void init();
};

#endif /* SYMBOLTABLE_H_ */
