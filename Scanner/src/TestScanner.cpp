#include "../includes/ScannerImp.h"


int main(int argc, char **argv) {
    ScannerImp *scanner = new ScannerImp((char *) "/home/fble/Desktop/hochschule/test.txt");
    auto test = scanner->nextToken()->getType();
    cout << ScannerImp::toString(test) << endl;
}


