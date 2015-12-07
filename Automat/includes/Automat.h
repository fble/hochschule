#ifndef Automat_H_
#define Automat_H_

#include "../../Scanner/includes/TType.h"

class Automat {
public:
	typedef enum {
			STATE_NULL,
			STATE_0,
			STATE_1,
			STATE_I,
			STATE_IF,
			STATE_W,
			STATE_WH,
			STATE_WHI,
			STATE_WHIL,
			STATE_WHILE,
			STATE_FINAL,
			STATE_PLUS,
			STATE_MINUS,
			STATE_STAR,
			STATE_DIVISION,
			STATE_EQUAL,
			STATE_LESSTHAN,
			STATE_GREATERTHAN,
			STATE_NOTEQUAL,
			STATE_ASSIGN,
			STATE_AND,
			STATE_NOT,
			STATE_SEMICOLON,
			STATE_OPENINGROUNDBRACKET,
			STATE_CLOSINGROUNDBRACKET,
			STATE_OPENINGSQUAREBRACKET,
			STATE_CLOSINGSQUAREBRACKET,
			STATE_OPENINGBRACE,
			STATE_CLOSINGBRACE
		} State;

	bool final;
	State currState;
	State lastState;


	/**
	 * In dem Zähler wird die Anzahl der gültigen durchlaufenen
	 * Zustände gespeichert.
	 */
	int charCtr = -1;

	/**
	 * Ist die "Endmarke" des gültigen Lexems.
	 */
	int charEnd = -1;
public:
	Automat();
	virtual ~Automat();
	virtual void readChar(char c) = 0;
	virtual void doTransition(State state, char c) = 0;
	virtual TType getType() = 0;
	virtual void reset() = 0;

	bool isFinal() {return this->final;};
	bool hasRejected() {return this->currState == STATE_NULL;};
	void setFinal(bool state) {this->final = state;};
	void setCurrentState(State newState) {this->currState = newState;};
};

#endif /* Automat_H_ */
