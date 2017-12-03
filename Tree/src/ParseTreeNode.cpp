#include "../includes/ParseTreeNode.h"

const char* const ParseTreeNode::ruleTypeNames[] = {"PROG", "DECLS", "DECL", "ARRAY",
                                                    "STATEMENTS", "STATEMENT", "EXP", "EXP2", "INDEX", "OP_EXP", "OP","NRT","EPS"};

ParseTreeNode::ParseTreeNode(Rules::RuleType expectedType) : data() {
    children = new DoublyLinkedList<ParseTreeNode>();
    this->expectedType = expectedType;
    this->infoType = InformationType::noType;
}

ParseTreeNode::ParseTreeNode(Rules::RuleType expectedType, Token* data) {
    children = new DoublyLinkedList<ParseTreeNode>();
    this->data = data;
    this->expectedType = expectedType;
    this->infoType = InformationType::noType;
}


ParseTreeNode::ParseTreeNode(Token* data) {
    children = new DoublyLinkedList<ParseTreeNode>();
    this->data = data;
    this->expectedType = Rules::NRT;
    this->infoType = InformationType::noType;
}

ParseTreeNode::~ParseTreeNode() {
    delete children;
    //TODO do I have to do this?
    if (data != 0) {
        delete data;
    }
}

void ParseTreeNode::accept(TreeVisitor* visitor) {
    visitor->visitNode(this);
}
/*
void ParseTreeNode::check(TreeVisitor* visitor){
    visitor->visitNode(this);
}*/

DoublyLinkedList<ParseTreeNode> *ParseTreeNode::getChildren() {
    return children;
}

ParseTreeNode* ParseTreeNode::getChild(unsigned int nr) {
    return children->get(nr);
}

Token* ParseTreeNode::getData() {
    return data;
}

Rules::RuleType ParseTreeNode::getType(){
    return this->expectedType;
}

unsigned int ParseTreeNode::getSize() {
    return children->getSize();
}

bool ParseTreeNode::hasChildren() {
    return children->getSize();
}

void ParseTreeNode::addChild(ParseTreeNode* child) {
    child->parent = this;
    children->addLast(child);
}

void ParseTreeNode::setData(Token* data) {
    this->data = data;
}

void ParseTreeNode::setInfoType(InformationType::InfoType infoType){
    //std::cout << "setInfoType: " << infoType << std::endl;
    this->infoType = infoType;
}

InformationType::InfoType ParseTreeNode::getInfoType(){
    return this->infoType;
}

void ParseTreeNode::printLeaves() {
    if (hasChildren()) {
        for (unsigned int i = 0; i < getSize(); i++) {
            getChild(i)->printLeaves();
        }
    } else {
        if (data != 0) {
            //std::cout <<  Token::tokenTypeNames[data->getType()] << " ";
            data->printSimple();
            std::cout <<  "\n";
        } else {
            //std::cout <<  "EMPTY NODE of type " << ParseTreeNode::ruleTypeNames[expectedType] << "\n";
        }
    }
}

void ParseTreeNode::print(unsigned int level) {
    std::cout << std::setw(level * 2) << "" << ParseTreeNode::ruleTypeNames[expectedType];
    if (data != 0) {
        std::cout << " ";
        data->printSimple();
    }
    if (hasChildren()) {
        std::cout << " (\n";

        for (unsigned int i = 0; i<getSize(); i++) {
            getChild(i)->print(level + 1);
        }
        std::cout << std::setw(level * 2) << "" << ")\n";
    } else {
        std::cout << "\n";
    }
}

std::ostream &operator<<(std::ostream &out, ParseTreeNode &node) {
    /*out << "(" << ParseTreeNode::ruleTypeNames[node.expectedType] << " ";
    if (node.data != 0) {
        node.data->printSimple();
        if (node.hasChildren()) {
            out  << " ";
        }
    }

    for (unsigned int i = 0; i<node.getSize(); i++) {
        out << *node.getChild(i);
    }
    out << ")";
    return out;*/

    if(node.parent != 0){
        out	<< ParseTreeNode::ruleTypeNames[node.parent->getType()] << " -";
    }
    if(node.expectedType == Rules::NRT){
        if (node.data != 0) {
            out << "content: ";
            node.data->printSimple();
            if (node.hasChildren()) {
                out  << " ";
            }
        }
    } else {
        out << ParseTreeNode::ruleTypeNames[node.expectedType] ;
    }



    out << "\n";

    for (unsigned int i = 0; i<node.getSize(); i++) {
        out <<*node.getChild(i);
    }
    return out;
}
