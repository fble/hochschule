#ifndef AUTOMAT_SRC_AUTOMATSIGN_H_
#define AUTOMAT_SRC_AUTOMATSIGN_H_

#include "Automat.h"


/**
 * Der AutomatInteger soll die Teilsprache Sign erkennen.
 */
class AutomatSign : public Automat {
private:
	/**
	 * Diese Struktur definiert die benötigten Informationen, die bei einem
	 * Zustandsübergang benötigt werden.
	 * currState ist der aktuelle Zustand des Automaten.
	 * nextState ist der Zustand, der für eine gültige Transition eingenommen wird.
	 * c ist das Zeichen, mit dem eine Transition stattfinden soll.
	 */
	typedef struct {
		State currState;
		State nextState;
		char c;
	} TransitionElement;


	/**
	 * Definition der Menge aller gültigen Übergänge zur Erkennung der Teilsprache Sign.
	 */
	const TransitionElement matrix[21] = {
			{STATE_0, STATE_PLUS, '+'}, {STATE_0, STATE_MINUS, '-'}, {STATE_0, STATE_DIVISION, ':'}, {STATE_DIVISION, STATE_ASSIGN, '='},
			{STATE_0, STATE_STAR, '*'}, {STATE_0, STATE_LESSTHAN, '<'}, {STATE_LESSTHAN, STATE_1, ':'},
			{STATE_1, STATE_NOTEQUAL, '>'}, {STATE_0, STATE_GREATERTHAN, '>'}, {STATE_0, STATE_EQUAL, '='},
			{STATE_0, STATE_NOT, '!'}, {STATE_0, STATE_AND, '&'}, {STATE_0, STATE_SEMICOLON, ';'},
			{STATE_0, STATE_OPENINGROUNDBRACKET, '('}, {STATE_0, STATE_CLOSINGROUNDBRACKET, ')'}, {STATE_0, STATE_OPENINGBRACE, '{'},
			{STATE_0, STATE_CLOSINGBRACE, '}'}, {STATE_0, STATE_OPENINGSQUAREBRACKET, '['}, {STATE_0, STATE_CLOSINGSQUAREBRACKET, ']'},
			{STATE_DIVISION, STATE_COMMENT_BEGIN, '*'}, {STATE_STAR, STATE_COMMENT_END, ':'}
	};


	/**
	 * Speichert den zuletzt erreichten Final-Zustand ab.
	 */
	State lastAcceptingState;
public:
	AutomatSign();
	virtual ~AutomatSign();
	virtual void readChar(char c);
	virtual void doTransition(State state, char c);
	virtual TType getType();
	virtual void reset();
};

#endif /* AUTOMAT_SRC_AUTOMATSIGN_H_ */
