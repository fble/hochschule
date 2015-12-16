#include "../includes/AutomatIdentifier.h"
#include <iostream>

AutomatIdentifier::AutomatIdentifier() {
	setCurrentState(STATE_0);
}

AutomatIdentifier::~AutomatIdentifier() {}

void AutomatIdentifier::doTransition(State currState, char c) {
	bool matchFound = false;
	for(int i = 0; i<7; i++) {
		if (matrixKeyWords[i].currState == currState && (c == matrixKeyWords[i].cLow || c == matrixKeyWords[i].cHigh)) {
			this->currState = matrixKeyWords[i].nextState;
			matchFound = true;
			//charCtr++;
			break;
		}
	}

	if(!matchFound) {
		if (this->currState == STATE_0) {
			for (int i = 0; i < 2; i++) {
				if (((int) c >= matrixFirstChar[i].rangeMin && (int) c <= matrixFirstChar[i].rangeMax)) {
					this->currState = matrixFirstChar[i].nextState;
					matchFound = true;
					//charCtr++;
					break;
				}
			}
		}
	}

	if(!matchFound) {
		if(this->currState != STATE_0 && this->currState != STATE_NULL) {
			for(int i = 0; i<3; i++) {
				if(((int) c >= matrixIdentifier[i].rangeMin && (int) c <= matrixIdentifier[i].rangeMax)) {
					this->currState = matrixIdentifier[i].nextState;
					matchFound = true;

					break;
				}
			}
		}

	}
	charCtr++;


	this->lastState = this->currState;

	if(!matchFound) setCurrentState(STATE_NULL);

	setFinal((this->currState != STATE_0 && this->currState != STATE_NULL) && matchFound);

	if(isFinal())
		this->lexemLength = charCtr;
}

void AutomatIdentifier::readChar(char c) {
	doTransition(this->currState, c);
}

TType AutomatIdentifier::getType() {
	switch(this->lastState) {
		//case STATE_IF: return If;
		//case STATE_WHILE: return While;
		case STATE_FINAL: return Identifier;
		default: return Identifier; // Oder Fehler
	}
}

void AutomatIdentifier::reset() {
	this->setCurrentState(STATE_0);
	this->lastState = STATE_0;
	setFinal(false);
	charCtr =0;
	lexemLength = -1;
}