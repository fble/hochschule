/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/ScannerImp.h"
#include "../includes/InfoInt.h"

Token *ScannerImp::nextToken() {
	if(skip_spaces())return NULL;
	runMachines();
	TType typ = manager->getType();
	skip_comment(&typ);
	int wortlaenge = manager->getLexemLength();
	int wrongChars = manager->ungetCtr();
	buffer->ungetChar(wrongChars);
	return createToken(typ,wortlaenge,x,y);
}

Token *ScannerImp::createToken(TType typ,int wortlaenge,int X_Anfang,int Y_Anfang){
	x+=wortlaenge;
	char tmp[wortlaenge + 1];
	memcpy(tmp, tokenAnfang, (size_t) wortlaenge);
	tmp[wortlaenge] = '\0';
	Information <char*>* info;
	switch(typ) {
		case Identifier:
			info = symboltable->insert(tmp, X_Anfang, Y_Anfang);
			switch (info->getX()) {
				case -1:
					typ = If;
					break;
				case -2:
					typ = While;
					break;
				default:break;
			}
			break;
		case Integer:
			return new Token(typ, X_Anfang, Y_Anfang, new InfoInt(tmp));
		case Fehler:
			buffer->getChar();
			return new Token(typ, X_Anfang, Y_Anfang, new InfoError(tmp));
		default:break;
	}
	return new Token(typ, X_Anfang, Y_Anfang, info);
}

void ScannerImp::runMachines()
{
	manager->reset();
	this->tokenAnfang = buffer->getCharPointer();
	while(manager->readChar(*buffer->getChar()));
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

void ScannerImp::skip_comment(TType *typ) {
	if(*typ == CommentBegin) {
		while (*typ != CommentEnd || skip_spaces()) {
			runMachines();
			*typ = manager->getType();
		}
		buffer->ungetChar(1);
		runMachines();
		*typ = manager->getType();
	}
}
