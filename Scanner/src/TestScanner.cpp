#include "../includes/ScannerImp.h"


int main(int argc, char **argv) {
    ScannerImp *scanner = new ScannerImp((char *) "/home/stefan/test.txt");

    for(int i = 0; i<20; i++) {
        auto token = scanner->nextToken();
        cout << "Token " << token->getInformation()->getInfo() << " " <<
                ScannerImp::toString(token->getType()) << " X: " << token->getColumn() << " Y: " <<
                token->getLine() << endl;
        //cout << test;
    }
}


