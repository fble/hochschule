//
// Created by fble on 12/3/15.
//

#ifndef COMPILER_SCANNER_H_H
#define COMPILER_SCANNER_H_H

#include "Token.h"

class Scanner {
    virtual Token *nextToken() = 0;
};

#endif //COMPILER_SCANNER_H_H
