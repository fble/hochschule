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
			{STATE_0, STATE_FINAL, '+'}, {STATE_0, STATE_FINAL, '-'}, {STATE_0, STATE_1, ':'}, {STATE_1, STATE_FINAL, '='},
			{STATE_0, STATE_FINAL, '*'}, {STATE_0, STATE_2, '<'}, {STATE_2, STATE_3, ':'},
			{STATE_3, STATE_FINAL, '>'}, {STATE_0, STATE_FINAL, '>'}, {STATE_0, STATE_FINAL, '='},
			{STATE_0, STATE_FINAL, '!'}, {STATE_0, STATE_FINAL, '&'}, {STATE_0, STATE_FINAL, ';'},
			{STATE_0, STATE_FINAL, '('}, {STATE_0, STATE_FINAL, ')'}, {STATE_0, STATE_FINAL, '{'},
			{STATE_0, STATE_FINAL, '}'}, {STATE_0, STATE_FINAL, '['}, {STATE_0, STATE_FINAL, ']'}
	};
public:
	AutomatSign();
	virtual ~AutomatSign();
	virtual void readChar(char c);
	virtual void doTransition(State state, char c);
};

#endif /* AUTOMAT_SRC_AUTOMATSIGN_H_ */
