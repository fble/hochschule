#include "../includes/ScannerImp.h"


int main(int argc, char **argv) {
    ScannerImp *scanner = new ScannerImp();
    cout<<scanner->nextToken()->getInformation()->getInfo();
}

