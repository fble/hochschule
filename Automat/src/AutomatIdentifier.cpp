#include "../includes/AutomatIdentifier.h"

AutomatIdentifier::AutomatIdentifier() {
	setCurrentState(STATE_0);
}

AutomatIdentifier::~AutomatIdentifier() {}

void AutomatIdentifier::doTransition(State currState, char c) {
	bool matchFound = false;
	for(int i = 0; i<5; i++) {
		if (matrix[i].currState == currState && (int) c >= matrix[i].rangeMin && (int) c <= matrix[i].rangeMax) {
			this->currState = matrix[i].nextState;
			matchFound = true;

			break;
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
		case STATE_FINAL: return Identifier;
		default: return Fehler;
	}
}

void AutomatIdentifier::reset() {
	this->setCurrentState(STATE_0);
	this->lastState = STATE_0;
	setFinal(false);
	charCtr =0;
	lexemLength = -1;
}