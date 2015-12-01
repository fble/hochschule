#include <string.h>
#include "../includes/SymtabEntry.h"

InfoInd * SymtabEntry::getInfo()
{
	return info;
}

SymtabEntry * SymtabEntry::getNext()
{
	return next;
}

void SymtabEntry::setNext(SymtabEntry * next)
{
	this->next = next;
}

SymtabEntry::SymtabEntry(char* lexem, int x, int y) {
	this->lexem = new char[strlen(lexem) + 1];
	strcpy(this->lexem, lexem);
	info = new InfoInd(this->lexem, x, y);
}

SymtabEntry::~SymtabEntry()
{
	delete[] lexem;
	delete info;
}

