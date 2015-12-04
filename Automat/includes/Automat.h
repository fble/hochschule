#ifndef Automat_H_
#define Automat_H_

#include "../../Scanner/includes/TType.h"

class Automat {
public:
	typedef enum {
			STATE_NULL,
			STATE_0,
			STATE_1,
			STATE_2,
			STATE_3,
			STATE_I,
			STATE_IF,
			STATE_W,
			STATE_WH,
			STATE_WHI,
			STATE_WHIL,
			STATE_WHILE,
			STATE_FINAL
		} State;

	bool final;
	State currState;
	int charCtr;
	int charEnd = -1;
public:
	Automat();
	virtual ~Automat();
	virtual void readChar(char c) = 0;
	virtual void doTransition(State state, char c) = 0;
	virtual TType getType() = 0;

	bool isFinal() {return this->final;};
	bool hasRejected() {return this->currState == STATE_NULL;};
	void setFinal(bool state) {this->final = state;};
	void setCurrentState(State newState) {this->currState = newState;};
	void reset() {this->setCurrentState(STATE_0); setFinal(false); charCtr =0;};

};

#endif /* Automat_H_ */
