#include "../includes/AutomatInteger.h"

AutomatInteger::AutomatInteger() {
	setCurrentState(STATE_0);
}

AutomatInteger::~AutomatInteger() {}

void AutomatInteger::doTransition(State currState, char c) {
	bool matchFound = false; // Prüfvariable, ob eine passende Transition in der Schleife gefunden wird

	// Durchläuft die Menge gültiger Transitionen und prüft, ob es eine passende Transition gibt.
	for(int i = 0; i<2; i++) {
		if(matrix[i].currState == currState && (int) c >= matrix[i].rangeMin && (int) c <= matrix[i].rangeMax) {
			this->currState = matrix[i].nextState; // Zustand aktualisieren
			matchFound = true;

			break;
		}
	}
	charCtr++;
	this->lastState = this->currState;

	if(!matchFound) setCurrentState(STATE_NULL); // Wenn kein match existiert, dann verwirft Automat

	setFinal(this->currState == STATE_FINAL && matchFound); // Final-Zustand wird gesetzt

	// Wenn der Automat in einem Endzustand ist,
	// dann wird die "Endmarke" neu gesetzt mit dem aktuellen Zählerstand
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