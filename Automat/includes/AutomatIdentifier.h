#ifndef AUTOMAT_SRC_AUTOMATIDENTIFIER_H_
#define AUTOMAT_SRC_AUTOMATIDENTIFIER_H_

#include "Automat.h"

class AutomatIdentifier : public Automat {
private:
	typedef struct {
		State nextState;
		int rangeMin;
		int rangeMax;
	} TransitionElement;

	typedef struct {
		State currState;
		State nextState;
		char cLow;
		char cHigh;
	} TransitionElementKeyWords;

	const TransitionElementKeyWords matrixKeyWords[7] = {
			{STATE_0, STATE_I, 'i', 'I'}, {STATE_I, STATE_IF, 'f', 'F'},
			{STATE_0, STATE_W, 'w', 'W'}, {STATE_W, STATE_WH, 'h', 'H'},
			{STATE_WH, STATE_WHI, 'i', 'I'}, {STATE_WHI, STATE_WHIL, 'l', 'L'},
			{STATE_WHIL, STATE_WHILE, 'e', 'E'}
	};

	const TransitionElement matrixFirstChar[2] = {
			{STATE_FINAL, 65, 90}, {STATE_FINAL, 97, 122}
	};

	const TransitionElement matrixIdentifier[3] = {
			{STATE_FINAL, 65, 90}, {STATE_FINAL, 97, 122}, {STATE_FINAL, 48, 57},
	};
public:
	AutomatIdentifier();
	virtual ~AutomatIdentifier();
	virtual void readChar(char c);
	virtual void doTransition(State state, char c);
	virtual TType getType();

};

#endif /* AUTOMAT_SRC_AUTOMATIDENTIFIER_H_ */
