#ifndef Automat_H_
#define Automat_H_

#include "../../Scanner/includes/TType.h"

class Automat {
public:
	/**
	 * Ist die Menge aller Zustände, die von Automaten eingenommen werden können.
	 */
	typedef enum {
			STATE_NULL,
			STATE_0,
			STATE_1,
			STATE_I,
			STATE_IF,
			STATE_W,
			STATE_WH,
			STATE_WHI,
			STATE_WHIL,
			STATE_WHILE,
			STATE_FINAL,
			STATE_PLUS,
			STATE_MINUS,
			STATE_STAR,
			STATE_DIVISION,
			STATE_EQUAL,
			STATE_LESSTHAN,
			STATE_GREATERTHAN,
			STATE_NOTEQUAL,
			STATE_ASSIGN,
			STATE_AND,
			STATE_NOT,
			STATE_SEMICOLON,
			STATE_OPENINGROUNDBRACKET,
			STATE_CLOSINGROUNDBRACKET,
			STATE_OPENINGSQUAREBRACKET,
			STATE_CLOSINGSQUAREBRACKET,
			STATE_OPENINGBRACE,
			STATE_CLOSINGBRACE,
			STATE_COMMENT_BEGIN,
			STATE_COMMENT_END
		} State;


	/**
	 * Speichert den Wert, ob der Automat in einem Final-Zustand ist, oder nicht.
	 * true, wenn der Automat in einem Final-Zustand ist.
	 */
	bool final;


	/**
	 * Speichert den aktuellen Zustand des Automaten.
	 */
	State currState;


	/**
	 * Speichert den zuletzt erreichten Zustand des Automaten ab.
	 */
	State lastState;


	/**
	 * Zählt alle eingelesenen Zeichen.
	 */
	int charCtr = 0;


	/**
	 * Ist die "Endmarke" des gültigen Lexems.
	 * Wird bei jedem Final-Zustand mit charCtr aktualisiert.
	 */
	int lexemLength = -1;


	/**
	 * Verarbeitet das übergebene Zeichen von readChar(...) mit dem aktuellen Zustand
	 * des Automaten.
	 */
	virtual void doTransition(State state, char c) = 0;
public:
	Automat();
	virtual ~Automat();


	/**
	 * Diese Funktion ließt ein übergebenes Zeichen vom Typ char ein.
	 */
	virtual void readChar(char c) = 0;


	/**
	 * Gibt den Typ des jeweils eingelesenen Lexems als TType zurück.
	 */
	virtual TType getType() = 0;


	/**
	 * Setzt den Automaten in seinen ursprünglichen Zustand zurück.
	 */
	virtual void reset() = 0;


	/**
	 * Gibt true zurück, wenn der Automat in einem Endzustand ist.
	 */
	bool isFinal() {return this->final;};


	/**
	 * Gibt true zurück, wenn der Automat verworfen hat und keine weiteren Zeichen akzeptiert.
	 * Gibt false zurück, wenn der Automat weitere Zeichen verarbeiten kann.
	 */
	bool hasRejected() {return this->currState == STATE_NULL;};


	/**
	 * Final-Zustand kann mit übergebenem Wert gesetzt werden.
	 */
	void setFinal(bool state) {this->final = state;};


	/**
	 * Der übergebene Wert wird als aktuellen Zustand verwendet.
	 */
	void setCurrentState(State newState) {this->currState = newState;};


	/**
	 * Gibt die tatsächliche Länge des gelesenen Lexems zurück.
	 */
	int getLexemLength() {return this->lexemLength;};
};

#endif /* Automat_H_ */
