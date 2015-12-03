#include "../includes/AutomatManager.h"
#include <iostream>

AutomatManager::AutomatManager() {
    this->automatIdentifier = new AutomatIdentifier();
    this->automatInteger = new AutomatInteger();
    this->automatSign = new AutomatSign();
}

AutomatManager::~AutomatManager() {}

TType AutomatManager::getType() {
    if(!noType) {
        if(!this->identifierRejected && this->integerRejected && this->signRejected) {
            return automatIdentifier->getType();
        } else if(this->identifierRejected && !this->integerRejected && this->signRejected) {
            return automatInteger->getType();
        } else if(this->identifierRejected && this->integerRejected && !this->signRejected){
            return automatSign->getType();
        }
    }


    return Fehler; // Muss einen anderen Wert bekommen
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
        if(ctr == 1) noType = true;
        return false;
    }

    return true;
}