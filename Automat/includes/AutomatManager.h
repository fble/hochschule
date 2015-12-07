//
// Created by ubuntu-gnome on 03.12.15.
//

#ifndef HOCHSCHULE_AUTOMATMANAGER_H
#define HOCHSCHULE_AUTOMATMANAGER_H

#include "../includes/AutomatIdentifier.h"
#include "../includes/AutomatSign.h"
#include "../includes/AutomatInteger.h"
#include "../../Scanner/includes/TType.h"


class AutomatManager {
private:
    Automat* automatSign;
    Automat* automatIdentifier;
    Automat* automatInteger;

    bool signRejected;
    bool identifierRejected;
    bool integerRejected;

    bool noType;

    int ctr;
public:
    AutomatManager();
    ~AutomatManager();
    TType getType();
    bool readChar(char c);
    int getCharLength();
    int getEndOfChar();
};


#endif //HOCHSCHULE_AUTOMATMANAGER_H
