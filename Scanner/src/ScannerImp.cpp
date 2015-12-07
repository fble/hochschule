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
	this->tokenAnfang = buffer->getCharPointer();
	const unsigned int wortlaenge = runAutomats();
	char tmp[wortlaenge + 1];
	memcpy(tmp, tokenAnfang, wortlaenge);
	tmp[wortlaenge] = '\0';
	TType typ = manager->getType();
	if (typ == Identifier) {
		auto info = symboltable->insert(tmp, x, y);
		switch (info->getX()) {
			case -1:
				typ = If;
			case -2:
				typ = While;
			default:;
		}
		return new Token(typ, x, y, info);
	}
	return new Token(typ, x, y, new InfoToken(tmp));
}

unsigned int ScannerImp::runAutomats()
{
	unsigned int wortlaenge = 0;
	while(manager->readChar(*buffer->getChar())){
		wortlaenge++;
	}
}

ScannerImp::ScannerImp(char *filepath)
{
    this->buffer = new Buffer(filepath);
	this->manager = new AutomatManager();
    this->symboltable = new Symboltable();
    symboltable->init();
}

ScannerImp::~ScannerImp() {
    delete buffer;
    delete symboltable;
	delete manager;
}
