/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/ScannerImp.h"
#include"../../Automat/includes/AutomatIdentifier.h"
#include"../../Automat/includes/AutomatInteger.h"
#include"../../Automat/includes/AutomatSign.h"

#include <string.h>

Token *ScannerImp::nextToken() {
	this->identifier = false, sign = false, integer = false;
	this->tokenAnfang = buffer->getCharPointer();
	const unsigned int wortlaenge = runAutomats();
	char tmp[wortlaenge + 1];
	memcpy(tmp, tokenAnfang, wortlaenge);
	tmp[wortlaenge] = '\0';

	if (identifier) {
		auto *info = this->symboltable->insert(tmp, x, y);
		return new Token(info->getX() > 0 ? Identifier : wortlaenge == 2 ? If : While, x, y, info);
	}
	if (sign) {
		return new Token(Sign, x, y, new InfoToken(tmp));
	}
	if (integer) {
		return new Token(Integer, x, y, new InfoToken(tmp));
	}
	else {
		if (!(*tmp == ' ' || *tmp == '\n')) {
			return new Token(Fehler, x, y, new InfoToken(tmp));
		}

	}
	return NULL;
}

unsigned int ScannerImp::runAutomats()
{
	unsigned int wortlaenge = 0;
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

ScannerImp::ScannerImp() : tokenAnfang(nullptr), x(0), y(0)
{
    this->buffer = new Buffer();
    this->automatIdentifier = new AutomatIdentifier();
    this->automatSign = new AutomatSign();
    this->automatInteger = new AutomatInteger();
    this->symboltable = new Symboltable();
    symboltable->init();
}

ScannerImp::~ScannerImp() {
    delete buffer;
    delete automatIdentifier;
    delete automatSign;
    delete automatInteger;
    delete symboltable;
}

Token *ScannerImp::makeToken(TType typ) {
	return 0;
}
