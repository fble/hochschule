#include "../includes/AutomatManager.h"

AutomatManager::AutomatManager() {
    this->automatIdentifier = new AutomatIdentifier();
    this->automatInteger = new AutomatInteger();
    this->automatSign = new AutomatSign();
}

AutomatManager::~AutomatManager() {
    delete automatIdentifier;
    delete automatInteger;
    delete automatSign;
}

TType AutomatManager::getType() {
    if(validType) {
        if(ctr == 1) {
            this->back = ctr;
            this->lexemLength = ctr;

            if(!this->automatIdentifier->hasRejected() && this->automatInteger->hasRejected() && this->automatSign->hasRejected()) {
                return automatIdentifier->getType();
            } else if(this->automatIdentifier->hasRejected() && !this->automatInteger->hasRejected() && this->automatSign->hasRejected()) {
                return automatInteger->getType();
            } else if(this->automatIdentifier->hasRejected() && this->automatInteger->hasRejected() && !this->automatSign->hasRejected()) {
                return automatSign->getType();
            }
        } else {
            if(!this->identifierRejected && this->integerRejected && this->signRejected) {
                this->back = ctr - automatIdentifier->lexemLength;
                this->lexemLength = automatIdentifier->getLexemLength();
                return automatIdentifier->getType();
            } else if(this->identifierRejected && !this->integerRejected && this->signRejected) {
                this->back = ctr - automatInteger->lexemLength;
                this->lexemLength = automatInteger->getLexemLength();
                return automatInteger->getType();
            } else if(this->identifierRejected && this->integerRejected && !this->signRejected){
                this->back = ctr - automatSign->lexemLength;
                this->lexemLength = automatSign->getLexemLength();
                return automatSign->getType();
            }
        }

    }

    this->back =1;
    this->lexemLength = 1;

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

void AutomatManager::reset() {
    signRejected = false;
    integerRejected = false;
    identifierRejected = false;
    ctr = 0;
    back = 0;
    validType = true;

    automatInteger->reset();
    automatSign->reset();
    automatIdentifier->reset();
}