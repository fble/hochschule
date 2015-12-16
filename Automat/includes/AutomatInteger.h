#ifndef AUTOMAT_SRC_AUTOMATINTEGER_H_
#define AUTOMAT_SRC_AUTOMATINTEGER_H_

#include "Automat.h"

/**
 * Der AutomatInteger soll die Teilsprache digit erkennen.
 */
class AutomatInteger : public Automat {
private:
	/**
	 * Diese Struktur definiert die benötigten Informationen, die bei einem
	 * Zustandsübergang benötigt werden.
	 * currState ist der aktuelle Zustand des Automaten.
	 * nextState ist der Zustand, der für eine gültige Transition eingenommen wird.
	 * rangeMin/rangeMax ist die Bedingung für eine Transition.
	 */
	typedef struct {
		State currState;
		State nextState;
		int rangeMin;
		int rangeMax;
	} TransitionElement;


	/**
	 * Definition der Menge aller gültigen Übergänge zur Erkennung der Teilsprache digit.
	 */
	const TransitionElement matrix[2] = {
			{STATE_0, STATE_FINAL, 48, 57}, {STATE_FINAL, STATE_FINAL, 48, 57},
	};

	virtual void doTransition(State state, char c);
public:
	AutomatInteger();
	virtual ~AutomatInteger();
	virtual void readChar(char c);
	virtual TType getType();
	virtual void reset();
};

#endif /* AUTOMAT_SRC_AUTOMATINTEGER_H_ */
