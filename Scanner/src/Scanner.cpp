/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Scanner.h"
#include"../../Automat/includes/AutomatIdentifier.h"
#include"../../Automat/includes/AutomatInteger.h"
#include"../../Automat/includes/AutomatSign.h"
#include "../includes/InfoInt.h"
#include "../includes/InfoSign.h"
#include "../includes/TokenChar.h"
#include <string.h>


int Scanner::runAutomats()
{
	int wortlaenge = 0;
	while (!(!automatIdentifier->isFinal() && !automatSign->isFinal() && !automatInteger->isFinal())) {

		current = buffer->getChar();
		x++;
		identifier = automatIdentifier->isFinal();
		sign = automatSign->isFinal();
		integer = automatInteger->isFinal();
		wortlaenge++;
		if (*current == '\n') {
			y++;
			x = -1;
		}
		automatIdentifier->readChar(*current);
		automatInteger->readChar(*current);
		automatSign->readChar(*current);
	}
    return wortlaenge;
}

Scanner::Scanner(): tokenAnfang(nullptr), x(0), y(0)
{
    this->buffer = new Buffer();
    this->automatIdentifier = new AutomatIdentifier();
    this->automatSign = new AutomatSign();
    this->automatInteger = new AutomatInteger();
    this->symboltable = new Symboltable();
    symboltable->init();
}

Scanner::~Scanner() {
    delete buffer;
    delete automatIdentifier;
    delete automatSign;
    delete automatInteger;
    delete symboltable;
}
template<typename T>
Token<T>* Scanner::nextToken() {
	this->identifier = false, sign = false, integer = false;
    this->tokenAnfang = buffer->getCharPointer();
	const int wortlaenge = runAutomats();
    char tmp [wortlaenge+1];
	memcpy(tmp, tokenAnfang, wortlaenge);
    tmp[wortlaenge] = '\0';

    if (identifier) {
        auto *info = this->symboltable->insert(tmp, x, y);
        return new TokenChar(info->getX() > 0 ? Identifier : wortlaenge == 2 ? If : While, x, y,info);
    }
	if (sign) {
        return new TokenChar(Sign, x, y, new InfoSign(tmp));
    }
	if (integer) {
       return new TokenInt(Integer, x, y, new InfoInt(strtol(tmp, nullptr, 10)));
    } 
	else {
        if (!(*tmp == ' ' || *tmp == '\n')) {
           return new TokenChar(Fehler, x, y, new InfoSign(tmp));
        }

    }
}
