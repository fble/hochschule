#include "../includes/Scanner.h"


int main(int argc, char **argv) {
    Symboltable *symboltable = new Symboltable;
    symboltable->insert("hallo", 10, 10);
    Token *token = new Token(Identifier, 10, 10, symboltable->insert("hallo", 5, 5));
    cout<<token->getInformation()->getInfo()<<endl;
    cout<<token->getInformation()->getX()<<endl;
    cout << token->getInformation()->getY();
}

