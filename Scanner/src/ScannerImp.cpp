/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/ScannerImp.h"

Token *ScannerImp::nextToken() {
	skip_spaces();
	int X_Anfang = x;
	int Y_Anfang = y;
	const unsigned int wortlaenge = runMachines();
	char tmp[wortlaenge + 1];
	memcpy(tmp, tokenAnfang, wortlaenge);
	tmp[wortlaenge] = '\0';
	TType typ = manager->getType();
	manager->reset();
	buffer->ungetChar();
	if (typ == Identifier) {
		auto info = symboltable->insert(tmp, X_Anfang, Y_Anfang);
		switch (info->getX()) {
			case -1:
				typ = If;
			case -2:
				typ = While;
			default:;
		}
		return new Token(typ, X_Anfang, Y_Anfang, info);
	}else if(typ == Fehler) {
		buffer->getChar();
		return new Token(typ, X_Anfang, Y_Anfang, new InfoToken(tmp));
	} else {
		return new Token(typ, X_Anfang, Y_Anfang, new InfoToken(tmp));
	}
}

unsigned int ScannerImp::runMachines()
{
	unsigned int wortlaenge = 0;
	this->tokenAnfang = buffer->getCharPointer();
	while(manager->readChar(*buffer->getChar())){
		wortlaenge++;
		x++;
	}
	return wortlaenge;
}

void ScannerImp::skip_spaces(){
	while(1){
		char tmp = *buffer->getChar();
		if(tmp == ' '){
			x++;
		}else if(tmp == '\n'){
			x = 0;
			y++;
		}else if(tmp == '\t') {
			x++;
		} else {
			buffer->ungetChar();
			break;
		}
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

