//
// Created by stefan on 02.12.17.
//

#ifndef TREE_INCLUDES_MAKECODEVISITOR
#define TREE_INCLUDES_MAKECODEVISITOR

#include "TreeVisitor.h"
#include "ParseTreeNode.h"
class MakeCodeVisitor : public TreeVisitor {
    class TreeVisitor;
public:
    MakeCodeVisitor(std::ostream &code);
    virtual void visitNode(ParseTreeNode* node) override;



private:
    std::ostream& code;
    unsigned int labelNumber;
    unsigned int getLabelNumber();
};


#endif TREE_INCLUDES_MAKECODEVISITOR
