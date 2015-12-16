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
            bool identifier = this->automatIdentifier->hasRejected();
            bool integer = this->automatInteger->hasRejected();
            bool sign = this->automatSign->hasRejected();

            if(!identifier && integer && sign) {
                return automatIdentifier->getType();
            } else if(identifier && !integer && sign) {
                return automatInteger->getType();
            } else if(identifier && integer && !sign) {
                return automatSign->getType();
            }
        } else {
            if(!this->identifierRejected && this->integerRejected && this->signRejected) {
                return returnChar(automatIdentifier);
            } else if(this->identifierRejected && !this->integerRejected && this->signRejected) {
                return returnChar(automatInteger);
            } else if(this->identifierRejected && this->integerRejected && !this->signRejected){
                return returnChar(automatSign);
            }
        }
    }
    this->back =1;
    this->lexemLength = 1;

    return Fehler;
}

TType AutomatManager::returnChar(Automat *automat){
    this->back = ctr - automat->lexemLength;
    this->lexemLength = automat->getLexemLength();
    return automat->getType();
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