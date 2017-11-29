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


    int wortlaenge = 0;

    if (typ == CommentEnd) {
        wortlaenge = 1;
        typ = Stern;
        buffer->ungetChar(1);
    } else {
        wortlaenge = manager->getLexemLength();
        if(ende){
            return NULL;
        }
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
	if(skip_spaces()){
		return true;
	}
	manager->reset();
	this->tokenAnfang = buffer->getCharPointer();
	while(manager->readChar(*buffer->getChar()));
	*typ = manager->getType();
	int back = manager->ungetCtr();
	buffer->ungetChar(back);
	return false;
}

bool ScannerImp::skip_spaces(){
	bool end_of_file = false;
	while(1){
		char tmp = *buffer->getChar();
		if(tmp == ' '){
			x++;
		}else if(tmp == '\n'){
			x = 1;
			y++;
		}else if(tmp == '\t') {
			x++;
		}else if(tmp == '\000'){
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
	x+=2;
	while (*typ != CommentEnd) {
		if (runMachines(typ)){
			return true;
		}
		x+= manager->getLexemLength();
		if (*typ == Fehler){
			buffer->getChar();
		}

	}
	return runMachines(typ);
}
