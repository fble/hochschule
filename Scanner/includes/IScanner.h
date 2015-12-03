//
// Created by fble on 12/3/15.
//

#ifndef COMPILER_ISCANNER_H_H
#define COMPILER_ISCANNER_H_H

#include "TType.h"
#include "Token.h"

class IScanner {
    virtual Token *makeToken(TType typ);
};

#endif //COMPILER_ISCANNER_H_H
