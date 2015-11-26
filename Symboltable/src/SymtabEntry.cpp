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

SymtabEntry::SymtabEntry(char* lexem, int x, int y)
{	
	int size = 0;
	char* tmp = lexem;
	while (*tmp != '\0') {
		size++;
		tmp++;
	}
	this->lexem = new char[size];
	memcpy(this->lexem, lexem, size);
	info = new InfoInd(lexem,x,y);
}

SymtabEntry::~SymtabEntry()
{
	delete[] lexem;
	delete info;
}

void SymtabEntry::memcpy(char* start, char* word, int size) {
	for (int i = 0; i <= size; i++) {
		start[i] = word[i];
	}
}