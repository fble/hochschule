/*
* SymtabEntry.h
*
*  Created on: 28.10.2015
*      Author: fble
*/

#ifndef SYMBOLTABLE_INCLUDES_SYMTABENTRY_H_
#define SYMBOLTABLE_INCLUDES_SYMTABENTRY_H_
#include "InfoInd.h"
class SymtabEntry {
private:
	SymtabEntry* next;
	InfoInd* info;
	char* lexem;
public:
	InfoInd* getInfo();
	SymtabEntry* getNext();
	void setNext(SymtabEntry* next);
	SymtabEntry(char* lexem, int x, int y);
	~SymtabEntry();
};

#endif /* SYMBOLTABLE_INCLUDES_SYMTABENTRY_H_ */
