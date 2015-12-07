#include "../includes/AutomatManager.h"
#include <iostream>

AutomatManager::AutomatManager() {
    this->automatIdentifier = new AutomatIdentifier();
    this->automatInteger = new AutomatInteger();
    this->automatSign = new AutomatSign();
}

AutomatManager::~AutomatManager() {}

TType AutomatManager::getType() {
    if(validType) {
        if(ctr == 1) {
            if(!this->automatIdentifier->hasRejected() && this->automatInteger->hasRejected() && this->automatSign->hasRejected()) {
                this->endOfChar = automatIdentifier->charEnd;
                return automatIdentifier->getType();
            } else if(this->automatIdentifier->hasRejected() && !this->automatInteger->hasRejected() && this->automatSign->hasRejected()) {
                this->endOfChar = automatInteger->charEnd;
                return automatInteger->getType();
            } else if(this->automatIdentifier->hasRejected() && this->automatInteger->hasRejected() && !this->automatSign->hasRejected()){
                this->endOfChar = automatSign->charEnd;
                return automatSign->getType();
            }
        } else {
            if(!this->identifierRejected && this->integerRejected && this->signRejected) {
                this->endOfChar = automatIdentifier->charEnd;
                return automatIdentifier->getType();
            } else if(this->identifierRejected && !this->integerRejected && this->signRejected) {
                this->endOfChar = automatInteger->charEnd;
                return automatInteger->getType();
            } else if(this->identifierRejected && this->integerRejected && !this->signRejected){
                this->endOfChar = automatSign->charEnd;
                return automatSign->getType();
            }
        }

    }

    return Fehler;
}

bool AutomatManager::readChar(char c) {
    this->identifierRejected = automatIdentifier->hasRejected(); // Speichert die einzelnen Zustände, ob Automat verworfen hat
    this->integerRejected = automatInteger->hasRejected();
    this->signRejected = automatSign->hasRejected();

    this->automatSign->readChar(c);
    this->automatIdentifier->readChar(c);
    this->automatInteger->readChar(c);

    ctr++;

    // Prüft, ob alle Automaten verworfen haben
    if(this->automatInteger->hasRejected() && this->automatSign->hasRejected() && automatIdentifier->hasRejected()) {
        // Wenn beim 1. Zeichen der Automat verwirft, dann ist das ein ungültiges Zeichen
        if(ctr == 1)
            validType = false;
        else
            validType = true;

        return false;
    }

    return true;
}

int AutomatManager::getEndOfChar() {
    return this->endOfChar;
}

void AutomatManager::reset() {
    signRejected = false;
    integerRejected = false;
    identifierRejected = false;
    ctr = 0;
    endOfChar = 0;
    validType = true;

    automatInteger->reset();
    automatSign->reset();
    automatIdentifier->reset();
}

