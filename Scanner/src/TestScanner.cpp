
#include "../includes/ScannerImp.h"


int main(int argc, char **argv) {
    bool error = false;
    ScannerImp *scanner = new ScannerImp((char *) "/home/fble/Desktop/hochschule/test.txt");
    Token *token;
    FILE* file = fopen("/home/fble/Desktop/hochschule/out.txt","w");
    printf("processing...\n");

    while((token = scanner->nextToken())) {
        auto typ = token->getType();
        if(typ == Fehler){
            error = true;
            fprintf(stderr,"unkown Token: %s \n",token->getInformation<char*>()->getInfo());
        }else{
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

    }
        fclose(file);
    if(error){
        printf("stop errors: \n");
    }else{
        printf("complete \n");
    }
}




