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
	return NULL;
}

unsigned int ScannerImp::runAutomats()
{

    return 0;
}

ScannerImp::ScannerImp() : tokenAnfang(nullptr), x(0), y(0)
{
    this->buffer = new Buffer((char*)"/home/fble/Desktop/test.txt");
    this->symboltable = new Symboltable();
    symboltable->init();
}

ScannerImp::~ScannerImp() {
    delete buffer;
    delete symboltable;
}

Token *ScannerImp::makeToken(TType typ) {
	this->token = new Token(typ);
}
