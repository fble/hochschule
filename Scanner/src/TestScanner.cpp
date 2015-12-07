#include "../includes/ScannerImp.h"


int main(int argc, char **argv) {
    ScannerImp *scanner = new ScannerImp((char*)"/home/fble/Desktop/hochschule/test.txt");
    cout << scanner->nextToken()->getType();
}


