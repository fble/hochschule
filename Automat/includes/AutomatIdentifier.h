#ifndef AUTOMAT_SRC_AUTOMATIDENTIFIER_H_
#define AUTOMAT_SRC_AUTOMATIDENTIFIER_H_

#include "Automat.h"

class AutomatIdentifier : public Automat {
private:
	typedef struct {
		State currState;
		State nextState;
		int rangeMin;
		int rangeMax;
	} TransitionElement;

	const TransitionElement matrix[5] = {
			{STATE_0, STATE_FINAL, 65, 90}, {STATE_0, STATE_FINAL, 97, 122},
			{STATE_FINAL, STATE_FINAL, 65, 90}, {STATE_FINAL, STATE_FINAL, 97, 122},
			{STATE_FINAL, STATE_FINAL, 48, 57}
	};
public:
	AutomatIdentifier();
	virtual ~AutomatIdentifier();
	virtual void readChar(char c);
	virtual void doTransition(State state, char c);
	virtual TType getType();

};

#endif /* AUTOMAT_SRC_AUTOMATIDENTIFIER_H_ */
