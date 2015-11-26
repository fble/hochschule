/*
 * Token.h
 *
 *  Created on: 13.11.2015
 *      Author: ubuntu-gnome
 */

#ifndef SCANNER_SRC_TOKEN_H_
#define SCANNER_SRC_TOKEN_H_
#include "TType.h"
#include "../../Symboltable/includes/Information.h"
#include "Token.h"
class TokenInt : public Token<long>
{
	int line;
	int column;
	TType tType;
	Information<long>* info;
public:

	TokenInt(TType typ, int x, int y, Information<long>* info);

	~TokenInt();

	int getLine()override;

	int getColumn()override;

	Information<long>* getInformation()override;

	TType getType() override;
};



#endif /* SCANNER_SRC_TOKEN_H_ */

