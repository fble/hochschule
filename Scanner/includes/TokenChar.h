//
// Created by fble on 11/26/15.
//

#ifndef COMPILER_TOKENCHAR_H
#define COMPILER_TOKENCHAR_H
#include "TType.h"
#include "../../Symboltable/includes/Information.h"
#include "Token.h"
class TokenChar : public Token<char*>
{
    int line;
    int column;
    TType tType;
    Information<char*>* info;
public:

    TokenChar(TType typ, int x, int y, Information<char*> *info);

    ~TokenChar();

    int getLine()override;

    int getColumn()override;

    Information<char*>* getInformation()override;

    TType getType() override;
};
#endif //COMPILER_TOKENCHAR_H


