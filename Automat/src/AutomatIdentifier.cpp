#include "../includes/AutomatIdentifier.h"

AutomatIdentifier::AutomatIdentifier() {
	setCurrentState(STATE_0);
}

AutomatIdentifier::~AutomatIdentifier() {}

void AutomatIdentifier::doTransition(State currState, char c) {
	bool tmp = false;
	for(int i = 0; i<5; i++) {
		if(matrix[i].currState == currState && ((int) c >= matrix[i].rangeMin && (int) c <= matrix[i].rangeMax)) {
			this->currState = matrix[i].nextState;
			tmp = true;
			back++;
		}
	}

	if(!tmp) setCurrentState(STATE_NULL);

	setFinal(this->currState == STATE_FINAL && tmp);
}

void AutomatIdentifier::readChar(char c) {
	doTransition(this->currState, c);
}

TType AutomatIdentifier::getType() {
	return Identifier;
}