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

char* AutomatManager::toString() {
    char* tmp;
    switch(getType()) {
        case Integer: tmp = "Integer"; break;
        case Identifier: tmp = "Identifier"; break;
        case Sign: tmp = "Sign"; break;
        case If: tmp = "If"; break;
        case While: tmp = "While"; break;
        case Fehler: tmp = "Fehler"; break;
        case Error: tmp = "Error"; break;
        case Plus: tmp = "Plus"; break;
        case Minus: tmp = "Minus"; break;
        case Stern: tmp = "Stern"; break;
        case Division: tmp = "Division"; break;
        case Equal: tmp = "Equal"; break;
        case LessThan: tmp = "LessThan"; break;
        case GreaterThan: tmp = "GreatherThan"; break;
        case NotEqual: tmp = "NotEqual"; break;
        case Assign: tmp = "Assign"; break;
        case And: tmp = "And"; break;
        case Not: tmp = "Not"; break;
        case Semicolon: tmp = "Selicolon"; break;
        case OpeningRoundBracket: tmp = "OpeningRoundBracket"; break;
        case ClosingRoundBracket: tmp = "ClosingRoundBracket"; break;
        case OpeningSquareBracket: tmp = "OpeningSquareBracket"; break;
        case ClosingSquareBracket: tmp = "ClosingSquareBracket"; break;
        case OpeningBrace: tmp = "OpeningBrace"; break;
        case ClosingBrace: tmp = "ClosingBrace"; break;
        default: tmp = "NoType";
    }

    return tmp;
}