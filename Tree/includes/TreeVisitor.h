//
// Created by stefan on 02.12.17.
//

#ifndef TREE_INCLUDES_TREEVISITOR
#define TREE_INCLUDES_TREEVISITOR

#include "ParseTreeNode.h"

class ParseTreeNode;
class TreeVisitor {
public:
    virtual void visitNode(ParseTreeNode* node) = 0;
};


#endif TREE_INCLUDES_TREEVISITOR
