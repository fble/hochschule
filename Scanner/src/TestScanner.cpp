
#include "../includes/ScannerImp.h"


int main(int argc, char **argv) {
    bool error = false;
    ScannerImp *scanner = new ScannerImp((char*)"/home/stefan/Dokumente/compiler/test.txt");
    Token *token;
    FILE* file = fopen("/home/stefan/Dokumente/compiler/out.txt","w");
    printf("processing...\n");

    while((token = scanner->nextToken())) {
        auto typ = token->getType();

        int line = token->getLine();
        int column = token->getColumn();

        if (typ == Fehler) {
            error = true;
            fprintf(stderr,"unkown Token: Line: %d Column: %d: %s \n", line, column, token->getInformation<char*>()->getInfo());

            continue;
        }

        fprintf(file,"Token %s\tLine: %d Column: %d", Scanner::toString(typ), line, column);
        switch (typ) {
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

    if (error) {
        printf("stop errors: \n");
    } else {
        printf("complete \n");
    }
}




