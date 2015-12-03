#ifndef AUTOMAT_SRC_AUTOMATINTEGER_H_
#define AUTOMAT_SRC_AUTOMATINTEGER_H_

#include "Automat.h"

class AutomatInteger : public Automat {
private:
	typedef struct {
		State currState;
		State nextState;
		char c;
	} TransitionElement;

	const TransitionElement matrix[20] = {
			{STATE_0, STATE_FINAL, '0'}, {STATE_0, STATE_FINAL, '1'}, {STATE_0, STATE_FINAL, '2'},
			{STATE_0, STATE_FINAL, '3'}, {STATE_0, STATE_FINAL, '4'}, {STATE_0, STATE_FINAL, '5'},
			{STATE_0, STATE_FINAL, '6'}, {STATE_0, STATE_FINAL, '7'}, {STATE_0, STATE_FINAL, '8'},
			{STATE_0, STATE_FINAL, '9'},
			{STATE_FINAL, STATE_FINAL, '0'}, {STATE_FINAL, STATE_FINAL, '1'}, {STATE_FINAL, STATE_FINAL, '2'},
			{STATE_FINAL, STATE_FINAL, '3'}, {STATE_FINAL, STATE_FINAL, '4'}, {STATE_FINAL, STATE_FINAL, '5'},
			{STATE_FINAL, STATE_FINAL, '6'}, {STATE_FINAL, STATE_FINAL, '7'}, {STATE_FINAL, STATE_FINAL, '8'},
			{STATE_FINAL, STATE_FINAL, '9'},

	};
public:
	AutomatInteger();
	virtual ~AutomatInteger();
	virtual void readChar(char c);
	virtual void doTransition(State state, char c);
	virtual TType getType();
};

#endif /* AUTOMAT_SRC_AUTOMATINTEGER_H_ */
