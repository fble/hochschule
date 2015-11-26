//
// Created by fble on 11/26/15.
//

#include "../includes/TokenChar.h"

TokenChar::TokenChar(TType typ, int x, int y, Information<char*> *info) {
    this->tType = typ;
    this->line = y;
    this->column = x;
    this->info = info;
}

TokenChar::~TokenChar() {

}

int TokenChar::getLine(){
    return line;
}

int TokenChar::getColumn(){
    return column;
}

Information<char *> *TokenChar::getInformation() {
    return info;
}

TType TokenChar::getType() {
    return tType;
}
