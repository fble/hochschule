#include <iostream>

#include "../includes/ParseTreeNode.h"
#include "../includes/RuleTypes.h"
#include "../../Scanner/includes/TType.h"

int main(int argc, char **argv) {
    std::cout << "Test Tree" << std::endl;
    int i = 12;
    ParseTreeNode* test = new ParseTreeNode(Rules::PROG);
    test->addChild(new ParseTreeNode(Rules::DECLS, new Token(Tokens::TC_NOTOKEN, 0, 0)));
    test->addChild(new ParseTreeNode(Rules::STATEMENTS, new Token(Tokens::S_GREATER, 0,2)));

    for (int i = 0; i < test->getSize(); i++) {
        std::cout << *test->getChild(i)->getData() << std::endl;
    }
    std::cout << "Has children? " << test->hasChildren()<<"\n" << *test << "\n";
    test->printLeaves();

    /*
     * g++ -std=c++11 -g ../sysprog1objs/ScannerLib.o src/ParseTreeNode.cpp src/TestTree.cpp -o TestTree
     */
}