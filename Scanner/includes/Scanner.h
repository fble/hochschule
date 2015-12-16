//
// Created by fble on 12/3/15.
//

#ifndef COMPILER_SCANNER_H_H
#define COMPILER_SCANNER_H_H

#include "Token.h"

class Scanner {
public:
    virtual Token *nextToken() = 0;

    static char* toString(TType typ) {
        char* tmp;
        switch(typ) {
            case Integer: tmp = "Integer\t"; break;
            case Identifier: tmp = "Identifier"; break;
            case Sign: tmp = "Sign\t\t"; break;
            case If: tmp = "If\t\t"; break;
            case While: tmp = "While\t\t"; break;
            case Fehler: tmp = "Fehler\t"; break;
            case Error: tmp = "Error\t\t"; break;
            case Plus: tmp = "Plus\t\t"; break;
            case Minus: tmp = "Minus\t\t"; break;
            case Stern: tmp = "Stern\t\t"; break;
            case Division: tmp = "Division\t"; break;
            case Equal: tmp = "Equal\t\t"; break;
            case LessThan: tmp = "LessThan\t"; break;
            case GreaterThan: tmp = "GreatherThan"; break;
            case NotEqual: tmp = "NotEqual\t"; break;
            case Assign: tmp = "Assign\t"; break;
            case And: tmp = "And\t\t"; break;
            case Not: tmp = "Not\t\t"; break;
            case Semicolon: tmp = "Selicolon\t"; break;
            case OR_Bracket: tmp = "OR_Bracket"; break;
            case CR_Bracket: tmp = "CR_Bracket"; break;
            case OS_Bracket: tmp = "OS_Bracket"; break;
            case CS_Bracket: tmp = "CS_Bracket"; break;
            case OpeningBrace: tmp = "OpeningBrace"; break;
            case ClosingBrace: tmp = "ClosingBrace"; break;
            case CommentBegin: tmp = "CommentBegin"; break;
            case CommentEnd: tmp = "CommentEnd"; break;
            default: tmp = "NoType";
        }

        return tmp;
    }

};

#endif //COMPILER_SCANNER_H_H
