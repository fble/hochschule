#include "../includes/Scanner.h"
#include "../includes/InfoInt.h"
#include "../includes/TokenChar.h"
#include "../includes/InfoSign.h"
#include "../includes/TType.h"


int main(int argc, char **argv) {

    Scanner *scanner = new Scanner();
    Symboltable* test =  new Symboltable();
    auto *info2 = new InfoInt(2);
    cout << info2->getX() << endl;
    auto info = new InfoInt(5);
    test->insert("hallo",11,5);
    auto token = new TokenChar(Identifier,10,5,new InfoSign("hallo"));
    cout<<token->getInformation()->getInfo()<<endl;
    cout<<token->getInformation()->getX()<<endl;
    cout<<token->getInformation()->getY()<<endl;
    auto token2 = new TokenChar(Identifier,10,5,test->insert("hallo",10,5));
    cout<<token2->getInformation()->getInfo()<<endl;
    cout<<token2->getInformation()->getX()<<endl;
    cout<<token2->getInformation()->getY()<<endl;

    // cout<<scanner->nextToken()->getInformation()->getInfo();
}

