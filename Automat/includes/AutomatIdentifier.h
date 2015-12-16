#ifndef AUTOMAT_SRC_AUTOMATIDENTIFIER_H_
#define AUTOMAT_SRC_AUTOMATIDENTIFIER_H_

#include "Automat.h"

/**
 * Der AutomatInteger soll die Teilsprache Identifier erkennen.
 */
class AutomatIdentifier : public Automat {
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
	 * Definition der Menge aller gültigen Übergänge zur Erkennung der Teilsprache Identifier.
	 */
	const TransitionElement matrix[5]  {
			{STATE_0, STATE_FINAL, 65, 90}, {STATE_0, STATE_FINAL, 97, 122},
			{STATE_FINAL, STATE_FINAL, 65, 90}, {STATE_FINAL, STATE_FINAL, 97, 122},
			{STATE_FINAL, STATE_FINAL, 48, 57},
	};
public:
	AutomatIdentifier();
	virtual ~AutomatIdentifier();
	virtual void readChar(char c);
	virtual void doTransition(State state, char c);
	virtual TType getType();
	virtual void reset();
};

#endif /* AUTOMAT_SRC_AUTOMATIDENTIFIER_H_ */
