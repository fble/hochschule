#include "../includes/TypeCheckVisitor.h"

TypeCheckVisitor::TypeCheckVisitor(Symboltable* symtab){
    this->symtab = symtab;
}

void TypeCheckVisitor::store(const char* identifier, InformationType::InfoType infoType){
    if (this->symtab->contains(identifier)){
        Token* token = this->symtab->lookup(identifier);
        token->setInfoType(infoType);
    }
}

InformationType::InfoType TypeCheckVisitor::getType(const char* identifier){
    if (this->symtab->contains(identifier)){
        Token* token = this->symtab->lookup(identifier);
        return token->getInfoType();
    }
    else{
        return InformationType::noType;
    }
}

void TypeCheckVisitor::visitNode(ParseTreeNode* node) {
    // PROG
    if (node->getType() == Rules::PROG){
        node->getChild(0)->accept(this);
        node->getChild(1)->accept(this);

        node->setInfoType(InformationType::noType);
    }
        // DECLS
    else if (node->getType() == Rules::DECLS){
        for (unsigned int i = 0; i < node->getSize(); i++){
            node->getChild(i)->accept(this);
        }
        node->setInfoType(InformationType::noType);
    }
        // DECL
    else if (node->getType() == Rules::DECL){
        ParseTreeNode* INT        = node->getChild(0);
        ParseTreeNode* ARRAY      = node->getChild(1);
        ParseTreeNode* IDENTIFIER = node->getChild(2);

        ARRAY->accept(this);

        if (getType(IDENTIFIER->getData()->getIdentifier()) != InformationType::noType){
            error("identifier already defined", IDENTIFIER);
        }
        else if (ARRAY->getInfoType() == InformationType::errorType){
            node->setInfoType(InformationType::errorType);
        }
        else{
            node->setInfoType(InformationType::noType);
            if (ARRAY->getInfoType() == InformationType::arrayType){
                store(IDENTIFIER->getData()->getIdentifier(), InformationType::intArrayType);
            }
            else{
                store(IDENTIFIER->getData()->getIdentifier(), InformationType::intType);
            }
        }
    }
        // ARRAY
    else if (node->getType() == Rules::ARRAY){
        if (node->getSize() == 3){
            ParseTreeNode* INT = node->getChild(1);
            if (INT->getData()->getIntegerValue() > 0){
                node->setInfoType(InformationType::arrayType);
            }
            else{
                error("no valid dimension", INT);
            }
        }
        else{
            node->setInfoType(InformationType::noType);
        }
    }
        // STATEMENTS
    else if (node->getType() == Rules::STATEMENTS){
        for (unsigned int i = 0; i < node->getSize(); i++){
            node->getChild(i)->accept(this);
        }
    }
        // STATEMENT
    else if (node->getType() == Rules::STATEMENT){
        // STATEMENT (identifier INDEX := EXP)
        if (node->getSize() == 4 &&
            node->getChild(0)->getType() == Rules::NRT &&
            node->getChild(1)->getType() == Rules::INDEX &&
            node->getChild(3)->getType() == Rules::EXP){

            ParseTreeNode*   IDENTIFIER         = node->getChild(0);
            ParseTreeNode*   INDEX              = node->getChild(1);
            ParseTreeNode*   ASSIGN             = node->getChild(2);
            ParseTreeNode*   EXP                = node->getChild(3);
            InformationType::InfoType IDENTIFIERTYPE = getType(IDENTIFIER->getData()->getIdentifier());

            EXP->accept(this);
            INDEX->accept(this);

            if (IDENTIFIERTYPE == InformationType::noType){
                error("identifier not defined", IDENTIFIER);
            }
            else if (EXP->getInfoType() == InformationType::intType &&
                     ( (IDENTIFIERTYPE == InformationType::intType      && INDEX->getInfoType() == InformationType::noType) ||
                       (IDENTIFIERTYPE == InformationType::intArrayType && INDEX->getInfoType() == InformationType::arrayType)
                     )){
                node->setInfoType(InformationType::noType);
            }
            else{
                error("incompatible types", IDENTIFIER);
            }
        }
            // STATEMENT (write(EXP))
        else if (node->getSize() == 4 &&
                 node->getChild(0)->getType() == Rules::NRT &&
                 node->getChild(1)->getType() == Rules::NRT &&
                 node->getChild(2)->getType() == Rules::EXP &&
                 node->getChild(3)->getType() == Rules::NRT){

            node->getChild(2)->accept(this);
            node->setInfoType(InformationType::noType);
        }
            // STATEMENT (read(identifier INDEX))
        else if (node->getSize() == 5 &&
                 node->getChild(0)->getType() == Rules::NRT &&
                 node->getChild(1)->getType() == Rules::NRT &&
                 node->getChild(2)->getType() == Rules::NRT &&
                 node->getChild(3)->getType() == Rules::INDEX &&
                 node->getChild(4)->getType() == Rules::NRT){

            ParseTreeNode* INDEX = node->getChild(3);
            ParseTreeNode* IDENTIFIER = node->getChild(2);
            InformationType::InfoType IDENTIFIERTYPE = getType(IDENTIFIER->getData()->getIdentifier());

            INDEX->accept(this);

            if (IDENTIFIERTYPE == InformationType::noType){
                error("identifier not defined", IDENTIFIER);
            }
            else if ((IDENTIFIERTYPE == InformationType::intType      && INDEX->getInfoType() == InformationType::noType) ||
                     (IDENTIFIERTYPE == InformationType::intArrayType && INDEX->getInfoType() == InformationType::arrayType)){
                node->setInfoType(InformationType::noType);
            }
            else{
                error("incompatible types", IDENTIFIER);
            }
        }
            // STATEMENT ({STAEMENTS})
        else if (node->getSize() == 3 &&
                 node->getChild(0)->getType() == Rules::NRT &&
                 node->getChild(1)->getType() == Rules::STATEMENTS &&
                 node->getChild(2)->getType() == Rules::NRT){

            node->getChild(1)->accept(this);
            node->setInfoType(InformationType::noType);
        }
            // STATEMENT if(EXP) STATEMENT ELSE STATEMENT
        else if (node->getSize() == 7 &&
                 node->getChild(0)->getType() == Rules::NRT &&       // if
                 node->getChild(1)->getType() == Rules::NRT &&       // (
                 node->getChild(2)->getType() == Rules::EXP &&       // EXP
                 node->getChild(3)->getType() == Rules::NRT &&       // )
                 node->getChild(4)->getType() == Rules::STATEMENT && // STATEMENT
                 node->getChild(5)->getType() == Rules::NRT &&       // else
                 node->getChild(6)->getType() == Rules::STATEMENT){  // STATEMENT

            node->getChild(2)->accept(this); //EXP
            node->getChild(4)->accept(this); //STATEMENT
            node->getChild(6)->accept(this); //STATEMENT

            if ( node->getChild(2)->getInfoType() == InformationType::errorType){
                node->setInfoType(InformationType::errorType);
            }
            else{
                node->setInfoType(InformationType::noType);
            }
        }
            // STATEMENT while(EXP) STATEMENT
        else if (node->getSize() == 5 &&
                 node->getChild(0)->getType() == Rules::NRT &&       // while
                 node->getChild(1)->getType() == Rules::NRT &&       // (
                 node->getChild(2)->getType() == Rules::EXP &&       // EXP
                 node->getChild(3)->getType() == Rules::NRT &&       // )
                 node->getChild(4)->getType() == Rules::STATEMENT){  // STATEMENT

            node->getChild(2)->accept(this); //EXP
            node->getChild(4)->accept(this); //STATEMENT

            if (node->getChild(2)->getInfoType() == InformationType::errorType){
                node->setInfoType(InformationType::errorType);
            }
            else{
                node->setInfoType(InformationType::noType);
            }
        }
    }
        // INDEX
    else if (node->getType() == Rules::INDEX){
        if (node->getSize() == 3 &&
            node->getChild(0)->getType() == Rules::NRT &&   // [
            node->getChild(1)->getType() == Rules::EXP &&   // EXP
            node->getChild(2)->getType() == Rules::NRT){    // ]

            node->getChild(1)->accept(this);

            if (node->getChild(1)->getInfoType() == InformationType::errorType){
                node->setInfoType(InformationType::errorType);
            }
            else{
                node->setInfoType(InformationType::arrayType);
            }
        }
    }
        // EXP
    else if (node->getType() == Rules::EXP){
        if (node->getSize() == 2){
            ParseTreeNode* EXP2   = node->getChild(0);
            ParseTreeNode* OP_EXP = node->getChild(1);

            EXP2->accept(this);
            OP_EXP->accept(this);

            if (OP_EXP->getInfoType() == InformationType::noType){
                node->setInfoType(EXP2->getInfoType());
            }
            else if (EXP2->getInfoType() != OP_EXP->getInfoType()){
                node->setInfoType(InformationType::errorType);
            }
            else{
                node->setInfoType(EXP2->getInfoType());
            }
        }
    }
        // EXP2
    else if (node->getType() == Rules::EXP2){
        if (node->getSize() == 3 &&
            node->getChild(0)->getType() == Rules::NRT &&   // (
            node->getChild(1)->getType() == Rules::EXP &&   // EXP
            node->getChild(2)->getType() == Rules::NRT){    // )

            node->getChild(1)->accept(this);
            node->setInfoType(node->getChild(1)->getInfoType());
        }
        else if (node->getSize() == 2 &&
                 node->getChild(0)->getType() == Rules::NRT &&  // identifier
                 node->getChild(1)->getType() == Rules::INDEX){ // INDEX

            ParseTreeNode* INDEX = node->getChild(1);
            ParseTreeNode* IDENTIFIER = node->getChild(0);
            InformationType::InfoType IDENTIFIERTYPE = getType(IDENTIFIER->getData()->getIdentifier());

            INDEX->accept(this);

            if (IDENTIFIERTYPE == InformationType::noType){
                error("identifier not defined", IDENTIFIER);
            }
            else if (IDENTIFIERTYPE == InformationType::intType && INDEX->getInfoType() == InformationType::noType){
                node->setInfoType(IDENTIFIERTYPE);
            }
            else if (IDENTIFIERTYPE == InformationType::intArrayType && INDEX->getInfoType() == InformationType::arrayType){
                node->setInfoType(InformationType::intType);
            }
            else{
                error("no primitive Type", IDENTIFIER);
            }
        }
        else if (node->getSize() == 1 &&
                 node->getChild(0)->getType() == Rules::NRT){ // identifier
            node->setInfoType(InformationType::intType);
        }
        else if (node->getSize() == 2 &&
                 node->getChild(0)->getType() == Rules::NRT &&
                 node->getChild(1)->getType() == Rules::EXP2){

            if (node->getChild(0)->getData()->getType() == Tokens::S_MINUS){ // - EXP2
                node->getChild(1)->accept(this);
                node->setInfoType(node->getChild(1)->getInfoType());
            }
            else if (node->getChild(0)->getData()->getType() == Tokens::S_EXCLAMATION){ // ! EXP2
                node->getChild(1)->accept(this);
                if (node->getChild(1)->getInfoType() != InformationType::intType){
                    node->setInfoType(InformationType::errorType);
                }
                else {
                    node->setInfoType(InformationType::intType);
                }
            }
        }
    }
        // OP_EXP
    else if (node->getType() == Rules::OP_EXP){

        if (node->getSize() == 2 &&
            node->getChild(0)->getType() == Rules::OP &&
            node->getChild(1)->getType() == Rules::EXP){



            node->getChild(0)->accept(this); // OP
            node->getChild(1)->accept(this); // EXP

            node->setInfoType(node->getChild(1)->getInfoType());
        }
    }
        // OP
    else if (node->getType() == Rules::OP){
        Token* OP = node->getChild(0)->getData();
        unsigned int OP_TYPE = OP->getType();

        if (OP_TYPE == Tokens::S_PLUS){
            node->setInfoType(InformationType::opPlus);
        }
        else if (OP_TYPE == Tokens::S_MINUS){
            node->setInfoType(InformationType::opMinus);
        }
        else if (OP_TYPE == Tokens::S_STAR){
            node->setInfoType(InformationType::opMult);
        }
        else if (OP_TYPE == Tokens::S_COLON){
            node->setInfoType(InformationType::opDiv);
        }
        else if (OP_TYPE == Tokens::S_LESS){
            node->setInfoType(InformationType::opLess);
        }
        else if (OP_TYPE == Tokens::S_GREATER){
            node->setInfoType(InformationType::opGreater);
        }
        else if (OP_TYPE == Tokens::S_EQUAL){
            node->setInfoType(InformationType::opEqual);
        }
        else if (OP_TYPE == Tokens::S_LESSCOLONGREATER){
            node->setInfoType(InformationType::opUnequal);
        }
        else if (OP_TYPE == Tokens::S_AMP){
            node->setInfoType(InformationType::opAnd);
        }
    }
}

void TypeCheckVisitor::error(char* message, ParseTreeNode* node){
    Token* token = node->getData();
    std::cerr << message << std::endl;
    std::cerr << *token << std::endl;
    throw "TypeCheck Error";
}
