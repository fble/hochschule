//
// Created by ubuntu-gnome on 03.12.15.
//

#ifndef HOCHSCHULE_AUTOMATMANAGER_H
#define HOCHSCHULE_AUTOMATMANAGER_H

#include "../includes/AutomatIdentifier.h"
#include "../includes/AutomatSign.h"
#include "../includes/AutomatInteger.h"
#include "../../Scanner/includes/TType.h"

/**
 * Der AutomatManager fasst die 3 Automaten zu einer Einheit zusammen.
 * Die Verwaltung der Unterautomaten wird über diese Klasse gesteurt.
 */
class AutomatManager {
private:
    /**
     * Referenz auf AutomatSign.
     */
    Automat* automatSign;


    /**
     * Referenz auf AutomatIdentifier.
     */
    Automat* automatIdentifier;


    /**
     * Referenz auf AutomatInteger.
     */
    Automat* automatInteger;


    /**
     * Hilfsvariablen zur Erfassung der aktuellen Zustände der einzelnen Automaten.
     */
    bool signRejected;
    bool identifierRejected;
    bool integerRejected;


    /**
     * Gibt an, ob ein Zeichen gelesen wurde, was nicht in der Sprache enthalten ist.
     */
    bool validType = true;


    /**
     * Dieser Wert gibt an, an welcher relativen Stelle das gültige Lexem endet.
     */
    int back;


    /**
     * Enthält die Länge des Lexems von dem Automat, der zuletzt kazeptiert hat.
     */
    int lexemLength;


    /**
     * Enthält die Anzahl aller gelesenen Zeichen.
     */
    int ctr;
public:
    AutomatManager();
    ~AutomatManager();


    /**
     * Diese Funktion ermittelt den Typ des eingelesenen Lexems.
     * Gibt ein Element aus TTyp zurück.
     */
    TType getType();


    /**
     * Über diese Funktion kann ein übergebenes Zeichen
     * vom Typ char vom Automaten verarbeitet werden.
     * true, wenn das Einlesen zu keinem Fehler geführt hat.
     * false, wenn der Automat keine weiteren Zeichen akzeptiert.
     */
    bool readChar(char c);


    /**
     * Diese Funktion gibt die Anzahl zurück, um die der Buffer später
     * wieder zurückgeschoben werden muss.
     */
    int ungetCtr() {return this->back;};


    /**
     * Setzt den Automaten auf den ursprünglichen Zustand zurück.
     */
    void reset();


    /**
     * Gibt die tatsächliche Länge des Lexems zurück.
     */
    int getLexemLength() {return this->lexemLength;};

    TType returnChar(int ctr, Automat *automat);
};


#endif //HOCHSCHULE_AUTOMATMANAGER_H
