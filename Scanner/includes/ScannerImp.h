/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include <string.h>
#include "../../Automat/includes/Automat.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Buffer/includes/Buffer.h"
#include "InfoError.h"
#include "Token.h"
#include "Scanner.h"
#include "../../Automat/includes/AutomatManager.h"

class ScannerImp: public Scanner{
	Symboltable *symboltable;
	Buffer *buffer;
	AutomatManager *manager;
	char *tokenAnfang;
	int x=1, y=1;
	bool endOfFile;

	bool runMachines(TType *typ);
    bool skip_spaces();
    bool skip_comment(TType *typ);

public:

	ScannerImp(char *filepath);

	~ScannerImp();

	Token *nextToken()override;

    Token *createToken(TType typ,int wortlaenge,int X_Anfang,int Y_Anfang);

	bool isFileEnd() override;

};


#endif /* SCANNER_H_ */
