#include "../includes/AutomatInteger.h"

AutomatInteger::AutomatInteger() {
	setCurrentState(STATE_0);
}

AutomatInteger::~AutomatInteger() {}

void AutomatInteger::doTransition(State currState, char c) {
	bool tmp = false;
	for(int i = 0; i<20; i++) {
		if(matrix[i].currState == currState && matrix[i].c == c) {
			this->currState = matrix[i].nextState;
			tmp = true;
			back++;
		}
	}

	if(!tmp) setCurrentState(STATE_NULL);

	setFinal(this->currState == STATE_FINAL && tmp);
}

void AutomatInteger::readChar(char c) {
	doTransition(this->currState, c);
}
