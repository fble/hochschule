/*
 * Token.cpp
 *
 *  Created on: 13.11.2015
 *      Author: ubuntu-gnome
 */
#include "../includes/TokenInt.h"

TokenInt::TokenInt(TType typ, int x, int y, Information<long>* info)
{
    this->tType = typ;
    this->line = y;
    this->column = x;
    this->info = info;
}

TokenInt::~TokenInt() {
}

int TokenInt::getLine()
{
    return line;
}

int TokenInt::getColumn()
{
    return column;
}


Information<long>* TokenInt::getInformation() {
    return info;
}

TType TokenInt::getType() {
    return tType;
}
