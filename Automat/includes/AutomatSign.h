#ifndef AUTOMAT_SRC_AUTOMATSIGN_H_
#define AUTOMAT_SRC_AUTOMATSIGN_H_

#include "Automat.h"

class AutomatSign : public Automat {
private:
	typedef struct {
		State currState;
		State nextState;
		char c;
	} TransitionElement;

	const TransitionElement matrix[19] = {
			{STATE_0, STATE_PLUS, '+'}, {STATE_0, STATE_MINUS, '-'}, {STATE_0, STATE_DIVISION, ':'}, {STATE_DIVISION, STATE_ASSIGN, '='},
			{STATE_0, STATE_STAR, '*'}, {STATE_0, STATE_LESSTHAN, '<'}, {STATE_LESSTHAN, STATE_1, ':'},
			{STATE_1, STATE_NOTEQUAL, '>'}, {STATE_0, STATE_GREATERTHAN, '>'}, {STATE_0, STATE_EQUAL, '='},
			{STATE_0, STATE_NOT, '!'}, {STATE_0, STATE_AND, '&'}, {STATE_0, STATE_SEMICOLON, ';'},
			{STATE_0, STATE_OPENINGROUNDBRACKET, '('}, {STATE_0, STATE_CLOSINGROUNDBRACKET, ')'}, {STATE_0, STATE_OPENINGBRACE, '{'},
			{STATE_0, STATE_CLOSINGBRACE, '}'}, {STATE_0, STATE_OPENINGSQUAREBRACKET, '['}, {STATE_0, STATE_CLOSINGSQUAREBRACKET, ']'}
	};
public:
	AutomatSign();
	virtual ~AutomatSign();
	virtual void readChar(char c);
	virtual void doTransition(State state, char c);
	virtual TType getType();
	virtual void reset();
};

#endif /* AUTOMAT_SRC_AUTOMATSIGN_H_ */
