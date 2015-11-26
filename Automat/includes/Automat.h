#ifndef Automat_H_
#define Automat_H_

class Automat {
public:
	typedef enum {
			STATE_NULL,
			STATE_0,
			STATE_1,
			STATE_2,
			STATE_3,
			STATE_FINAL
		} State;

	bool final;
	State currState;
	int back;
public:
	Automat();
	virtual ~Automat();
	virtual void readChar(char c) = 0;
	virtual void doTransition(State state, char c) = 0;

	bool isFinal() {return this->final;};
	void setFinal(bool state) {this->final = state;};
	void setCurrentState(State newState) {this->currState = newState;};
	void reset() {this->setCurrentState(STATE_0); setFinal(false); back=0;};

};

#endif /* Automat_H_ */
