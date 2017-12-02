//
// Created by stefan on 02.12.17.
//

#ifndef TREE_INCLUDES_TYPECHECKVISITOR
#define TREE_INCLUDES_TYPECHECKVISITOR

#include "TreeVisitor.h"
#include "ParseTreeNode.h"
#include "../../Information/Information.h"
#include "../../Symboltable/includes/Symboltable.h

class TypeCheckVisitor : public TreeVisitor {
    class TreeVisitor;
public:
    TypeCheckVisitor(Symboltable* symtab);
    virtual void visitNode(ParseTreeNode* node) override;
private:
    void error(char* message, ParseTreeNode* node);
    void store(const char* identifier, Information infoType);
    Information getType(const char* identifier);
    Symboltable* symtab;
};


#endif TREE_INCLUDES_TYPECHECKVISITOR
