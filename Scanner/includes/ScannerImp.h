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
#include "../../Automat/includes/AutomatManager.h"

class ScannerImp : public Scanner {
	Symboltable *symboltable;
	Buffer *buffer;
	AutomatManager *manager;
	char *tokenAnfang;
	char *current;
	int x, y;

	unsigned int runMachines();

public:

	ScannerImp(char *filepath);

	~ScannerImp();

	Token *nextToken() override;

    void skip_spaces();

    static char* toString(TType typ) {
        char* tmp;
        switch(typ) {
            case Integer: tmp = "Integer"; break;
            case Identifier: tmp = "Identifier"; break;
            case Sign: tmp = "Sign"; break;
            case If: tmp = "If"; break;
            case While: tmp = "While"; break;
            case Fehler: tmp = "Fehler"; break;
            case Error: tmp = "Error"; break;
            case Plus: tmp = "Plus"; break;
            case Minus: tmp = "Minus"; break;
            case Stern: tmp = "Stern"; break;
            case Division: tmp = "Division"; break;
            case Equal: tmp = "Equal"; break;
            case LessThan: tmp = "LessThan"; break;
            case GreaterThan: tmp = "GreatherThan"; break;
            case NotEqual: tmp = "NotEqual"; break;
            case Assign: tmp = "Assign"; break;
            case And: tmp = "And"; break;
            case Not: tmp = "Not"; break;
            case Semicolon: tmp = "Selicolon"; break;
            case OpeningRoundBracket: tmp = "OpeningRoundBracket"; break;
            case ClosingRoundBracket: tmp = "ClosingRoundBracket"; break;
            case OpeningSquareBracket: tmp = "OpeningSquareBracket"; break;
            case ClosingSquareBracket: tmp = "ClosingSquareBracket"; break;
            case OpeningBrace: tmp = "OpeningBrace"; break;
            case ClosingBrace: tmp = "ClosingBrace"; break;
            default: tmp = "NoType";
        }

        return tmp;
    }

};


#endif /* SCANNER_H_ */
