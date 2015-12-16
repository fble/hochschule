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


    /**
     * Hilfsvariablen zur Erfassung der aktuellen Zustände der einzelnen Automaten.
     */
    bool signRejected;
    bool identifierRejected;
    bool integerRejected;


    /**
     * Gibt an, ob ein Zeichen gelesen wurde, was nicht in der Sprache enthalten ist.
     */
    bool validType = true;


    /**
     * Dieser Wert gibt an, an welcher relativen Stelle das gültige Lexem
     * endet.
     */
    int endOfChar;

    int lexemLength;

    int ctr;
public:
    AutomatManager();
    ~AutomatManager();
    TType getType();
    bool readChar(char c);
    int getEndOfChar();
    void reset();
    int getLexemLength() {return this->lexemLength;};
};


#endif //HOCHSCHULE_AUTOMATMANAGER_H
