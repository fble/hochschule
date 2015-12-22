/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/ScannerImp.h"
#include "../includes/InfoInt.h"

Token *ScannerImp::nextToken() {
	bool ende;
	TType typ;
	ende = runMachines(&typ);
	while (typ == CommentBegin) {
		ende = skip_comment(&typ);
	}
	int wortlaenge = manager->getLexemLength();
	if(ende){
		return NULL;
	}
	return createToken(typ,wortlaenge,x,y);
}

Token *ScannerImp::createToken(TType typ,int wortlaenge,int X_Anfang,int Y_Anfang){
	x+=wortlaenge;
	char tmp[wortlaenge + 1];
	memcpy(tmp, tokenAnfang, (size_t) wortlaenge);
	tmp[wortlaenge] = '\0';
	Information <char*>* info;
	long value;
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
			errno = 0;
			value = strtol(tmp,NULL,10);
			if (errno == ERANGE){
				return new Token(Fehler, X_Anfang, Y_Anfang, new InfoError((char*)"Zahl zu lang"));
			}else{
				return new Token(typ, X_Anfang, Y_Anfang, new InfoInt(value));
			}
		case Fehler:
			buffer->getChar();
			return new Token(typ, X_Anfang, Y_Anfang, new InfoError(tmp));
		default:break;
	}
	return new Token(typ, X_Anfang, Y_Anfang, info);
}

bool ScannerImp::runMachines(TType *typ)
{
	manager->reset();
	if(skip_spaces()){
		return true;
	}
	this->tokenAnfang = buffer->getCharPointer();
	while(manager->readChar(*buffer->getChar()));
	auto back = manager->ungetCtr();
	buffer->ungetChar(back);
	*typ = manager->getType();
	return false;
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

bool ScannerImp::skip_comment(TType *typ) {
		while (*typ != CommentEnd) {
			if (runMachines(typ)){
				return true;
			}
		}
	return runMachines(typ);
}
