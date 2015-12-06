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
#include "InfoToken.h"
#include "Token.h"
#include "Scanner.h"
#include "IScanner.h"

class ScannerImp : public IScanner, Scanner {
	Token *token;
	Symboltable *symboltable;
	Buffer *buffer;
	char *tokenAnfang;
	char *current;
	int x, y;

	unsigned int runAutomats();

public:

	ScannerImp();

	~ScannerImp();

	Token *nextToken() override;

	Token *makeToken(TType typ) override;
};


#endif /* SCANNER_H_ */
