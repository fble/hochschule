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

class Scanner {
	Automat *automatSign;
	Automat *automatIdentifier;
	Automat *automatInteger;
	Symboltable *symboltable;
	Buffer *buffer;
	char *tokenAnfang;
	char *current;
	bool identifier, integer, sign;
	int x, y;

	unsigned int runAutomats();

public:

	Scanner();

	~Scanner();

	Token *nextToken();
};


#endif /* SCANNER_H_ */
