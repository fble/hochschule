#include "../includes/ScannerImp.h"


int main(int argc, char **argv) {
    ScannerImp *scanner = new ScannerImp((char *) "/home/fble/Desktop/hochschule/test.txt");
    Token *token;
    while((token = scanner->nextToken())) {
        auto typ = token->getType();
        cout << "Token " << Scanner::toString(typ) << "\t"
        << "Line: " << token->getLine() <<"\t"
        << "Column: " << token->getColumn() << "\t";
        Scanner::printValue(token);
        cout << endl;
    }
}


