
#include "../includes/Symboltable.h"

Symboltable::Symboltable() {
	size = 397;
	symboltable = new SymtabEntry*[size];
	for (int i = 0; i < size; i++) {
		symboltable[i] = 0;
	}
}

Symboltable::~Symboltable() {
	delete[] symboltable;
}

Information <char*>*Symboltable::insert(char *lexem, int x, int y) {
	bool isEmpty = true;
	if (lexem != 0 && (*lexem != '\0')) {
		SymtabEntry* lastEntry = symboltable[hash(lexem)];	
		if (lastEntry != 0) {
			isEmpty = false;
			SymtabEntry* tmp = lastEntry;
			while (tmp != 0) {
				lastEntry = tmp;
				if (lastEntry->getInfo()->compareLex(lexem)) {
					return lastEntry->getInfo();
				}
				tmp = lastEntry->getNext();
			}
		}		
		SymtabEntry* newEntry = new SymtabEntry(lexem, x, y);
		if (isEmpty) {
			symboltable[hash(lexem)] = newEntry;
		}
		else {
			lastEntry->setNext(newEntry);
		}
		return newEntry->getInfo();
	}
	else {
		return 0;
	}
}

void Symboltable::init()
{
	insert((char *) "if", -1, -1);
	insert((char *) "IF", -1, -1);
	insert((char *) "while", -2, -2);
	insert((char *) "WHILE", -2, -2);
}

Information <char*>*Symboltable::lookup(char *lexem)
{
	SymtabEntry* entry = symboltable[hash(lexem)];
	if (entry != 0) {
		SymtabEntry* tmp = entry;
		while (tmp != 0) {
			entry = tmp;
			if (entry->getInfo()->compareLex(lexem)) {
				return entry->getInfo();
			}
			tmp = entry->getNext();
		}
	}
	return 0;
}

int Symboltable::hash(char * lexem)
{
	unsigned int tmp = 0;
	while (*lexem != '\0') {
		tmp = 31* tmp + *lexem;
		lexem++;
	}
	return tmp % this->size;
}
