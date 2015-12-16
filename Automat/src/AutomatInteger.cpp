#include "../includes/AutomatInteger.h"
#include <iostream>

AutomatInteger::AutomatInteger() {
	setCurrentState(STATE_0);
}

AutomatInteger::~AutomatInteger() {}

void AutomatInteger::doTransition(State currState, char c) {
	bool matchFound = false;
	for(int i = 0; i<20; i++) {
		if(matrix[i].currState == currState && matrix[i].c == c) {
			this->currState = matrix[i].nextState;
			matchFound = true;

			break;
		}
	}
	charCtr++;
	this->lastState = this->currState;

	if(!matchFound) setCurrentState(STATE_NULL);

	setFinal(this->currState == STATE_FINAL && matchFound);

	// Wenn der Automat in einem Endzustand ist,
	// dann wird die "Endmarke" neu gesetzt mit dem
	// aktuellen Zählerstand
	if(isFinal())
		this->lexemLength = charCtr;
}

void AutomatInteger::readChar(char c) {
	doTransition(this->currState, c);
}

TType AutomatInteger::getType() {
	switch(this->lastState) {
		case STATE_FINAL: return Integer;
		default: return Fehler;
	}
}

void AutomatInteger::reset() {
	this->setCurrentState(STATE_0);
	this->lastState = STATE_0;
	setFinal(false);
	charCtr =0;
	lexemLength = -1;
}