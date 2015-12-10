/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/ScannerImp.h"
#include "../includes/InfoInt.h"

Token *ScannerImp::nextToken() {
	if(skip_spaces()){
		return NULL;
	};
	int X_Anfang = x;
	int Y_Anfang = y;
	const unsigned int wortlsaenge = runMachines();
	TType typ = manager->getType();
	const unsigned int wortlaenge = manager->getLexemLength();
	x+=wortlaenge;
	char tmp[wortlaenge + 1];
	memcpy(tmp, tokenAnfang, wortlaenge);
	tmp[wortlaenge] = '\0';

	int a = manager->getEndOfChar();
	manager->reset();
	buffer->ungetChar(a);
	if (typ == Identifier) {
		auto info = symboltable->insert(tmp, X_Anfang, Y_Anfang);
		switch (info->getX()) {
			case -1:
				typ = If;break;
			case -2:
				typ = While;break;
			default:;
		}
		return new Token(typ, X_Anfang, Y_Anfang, info);
	}else if(typ == Fehler) {
		buffer->getChar();
	}else if(typ == Integer) {
		return new Token(typ,X_Anfang, Y_Anfang, new InfoInt(tmp));
	}
	return new Token(typ, X_Anfang, Y_Anfang, new InfoError(tmp));
}

unsigned int ScannerImp::runMachines()
{
	unsigned int wortlaenge = 0;
	this->tokenAnfang = buffer->getCharPointer();
	while(manager->readChar(*buffer->getChar())){
		//wortlaenge++;
		//x++;
	}
	//if (wortlaenge == 0)wortlaenge = 1;
	return manager->getLexemLength();
}

bool ScannerImp::skip_spaces(){
	bool end_of_file = false;
	while(1){
		char tmp = *buffer->getChar();
		if(tmp == ' '){
			x++;
		}else if(tmp == '\n'){
			x = 0;
			y++;
		}else if(tmp == '\t') {
			x++;
		}else if(tmp == '\0'){
			end_of_file = true;
		}else {
			buffer->ungetChar(1);
			break;
		}
	}
	return end_of_file;
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

