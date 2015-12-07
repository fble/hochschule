#include "../includes/AutomatSign.h"
#include <iostream>

AutomatSign::AutomatSign() {
	setCurrentState(STATE_0);
}

AutomatSign::~AutomatSign() {}

void AutomatSign::doTransition(State currState, char c) {
	bool matchFound = false;
	for(int i = 0; i<20; i++) {
		if(matrix[i].currState == currState && matrix[i].c == c) {
			this->currState = matrix[i].nextState;
			matchFound = true;
			charCtr++;
			break;
		}
	}
	this->lastState = this->currState;

	if(!matchFound) setCurrentState(STATE_NULL);

	setFinal((this->currState != STATE_0 && this->currState != STATE_1 && this->currState != STATE_NULL) && matchFound);

	if(isFinal())
		this->charEnd = charCtr;
}

void AutomatSign::readChar(char c) {
	doTransition(this->currState, c);
}

TType AutomatSign::getType() {
	switch(this->lastState) {
		case STATE_PLUS: 					return Plus;
		case STATE_MINUS: 					return Minus;
		case STATE_STAR: 					return Stern;
		case STATE_DIVISION: 				return Division;
		case STATE_EQUAL: 					return Equal;
		case STATE_LESSTHAN: 				return LessThan;
		case STATE_GREATERTHAN:				return GreaterThan;
		case STATE_NOTEQUAL: 				return NotEqual;
		case STATE_ASSIGN: 					return Assign;
		case STATE_AND: 					return And;
		case STATE_NOT: 					return Not;
		case STATE_SEMICOLON: 				return Semicolon;
		case STATE_OPENINGROUNDBRACKET: 	return OpeningRoundBracket;
		case STATE_CLOSINGROUNDBRACKET: 	return ClosingRoundBracket;
		case STATE_OPENINGSQUAREBRACKET: 	return OpeningSquareBracket;
		case STATE_CLOSINGSQUAREBRACKET: 	return ClosingSquareBracket;
		case STATE_OPENINGBRACE: 			return OpeningBrace;
		case STATE_CLOSINGBRACE: 			return ClosingBrace;
		default:							return Fehler;
	};
}

void AutomatSign::reset() {
	this->setCurrentState(STATE_0);
	this->lastState = STATE_0;
	setFinal(false);
	charCtr =-1;
	charEnd = -1;
}