//
// Created by fble on 11/26/15.
//

#ifndef SCANNER_INCLUDES_TOKEN_H
#define SCANNER_INCLUDES_TOKEN_H

#include "TType.h"
#include "../../Information/Information.h"

class Token {
    int line;
    int column;
    TType tType;
    Information *info;
    public:
    Token(TType typ,int x, int y, Information *info) {
        this->tType = typ;
        this->column = x;
        this->line = y;
        this->info = info;

    };

    ~Token() { };

    int getLine() { return line; };

    int getColumn() { return column; };

    Information *getInformation() { return info; };

    TType getType() {return tType;};

};

#endif //COMPILER_TOKEN_H
