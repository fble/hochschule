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
    void *info;
    public:
    template <typename T>
    Token(TType typ,int x, int y, Information <T> *info) {
        this->tType = typ;
        this->column = x;
        this->line = y;
        this->info = info;

    };

    ~Token() { delete info; };

    int getLine() { return line; };

    int getColumn() { return column; };
    template <typename T>
    Information <T> *getInformation() { return (Information <T> *)info; };

    TType getType() {return tType;};



};

#endif //COMPILER_TOKEN_H
