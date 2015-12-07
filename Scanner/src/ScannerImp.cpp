/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/ScannerImp.h"

Token *ScannerImp::nextToken() {
	this->tokenAnfang = buffer->getCharPointer();
	const unsigned int wortlaenge = runMachines();
	char tmp[wortlaenge + 1];
	memcpy(tmp, tokenAnfang, wortlaenge);
	tmp[wortlaenge] = '\0';
	TType typ = manager->getType();
	manager->reset();
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
	}else{
		return new Token(typ, x, y, new InfoToken(tmp));
	}
}

unsigned int ScannerImp::runMachines()
{
	unsigned int wortlaenge = 0;
	skip_spaces();
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
		}else{
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

