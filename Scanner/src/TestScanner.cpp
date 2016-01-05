
#include "../includes/ScannerImp.h"


int main(int argc, char **argv) {
    ScannerImp *scanner = new ScannerImp((char *) "/home/stefan/test.txt");
    Token *token;
    FILE* file = fopen("/home/stefan/out.txt","w");
    while((token = scanner->nextToken())) {
        auto typ = token->getType();
        if(typ == Fehler){
        }
        fprintf(file,"Token %s\tLine: %d Column: %d",Scanner::toString(typ),token->getLine(),token->getColumn());
        switch(typ){
            case Integer:
                fprintf(file,"\tValue: %d \n",token->getInformation<int>()->getInfo());
                break;
            case Identifier:
                fprintf(file,"\tLexem: %s \n",token->getInformation<char*>()->getInfo());
                break;
            default:
                fprintf(file,"\n");
                break;
        }
    }
    fclose(file);
}



