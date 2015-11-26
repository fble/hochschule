#include "../includes/AutomatSign.h"

AutomatSign::AutomatSign() {
	setCurrentState(STATE_0);
}

AutomatSign::~AutomatSign() {}

void AutomatSign::doTransition(State currState, char c) {
	bool tmp = false;
	for(int i = 0; i<20; i++) {
		if(matrix[i].currState == currState && matrix[i].c == c) {
			this->currState = matrix[i].nextState;
			tmp = true;
			back++;
		}
	}

	if(!tmp) setCurrentState(STATE_NULL);

	setFinal((this->currState == STATE_FINAL || this->currState == STATE_1 || this->currState == STATE_2) && tmp);
}

void AutomatSign::readChar(char c) {
	doTransition(this->currState, c);
}
