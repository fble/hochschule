#include "../includes/MakeCodeVisitor.h"


MakeCodeVisitor::MakeCodeVisitor(std::ostream& c) :code(c){
    this->labelNumber = 0;
}

unsigned int MakeCodeVisitor::getLabelNumber(){
    this->labelNumber++;
    return this->labelNumber;
}

void MakeCodeVisitor::visitNode(ParseTreeNode* node) {

    // PROG
    if (node->getType() == Rules::PROG){
        node->getChild(0)->accept(this);
        node->getChild(1)->accept(this);

        code << "STP";
    }
        // DECLS
    else if (node->getType() == Rules::DECLS){
        for (unsigned int i = 0; i < node->getSize(); i++){
            node->getChild(i)->accept(this);
        }
    }
        // DECL (int ARRAY identifier)
    else if (node->getType() == Rules::DECL){
        code << "DS" << " " << "$" << node->getChild(2)->getData()->getIdentifier();
        node->getChild(1)->accept(this);
    }
        // ARRAY
    else if (node->getType() == Rules::ARRAY){
        // ARRAY (EPS))
        if (node->getChild(0)->getType() == Rules::EPS){
            code << " 1" << std::endl;
        }
            // ARRAY ([INTEGER])
        else{
            code << " " << node->getChild(1)->getData()->getIntegerValue() << std::endl;
        }
    }
        // STATEMENTS
    else if (node->getType() == Rules::STATEMENTS){
        // STATEMENTS (EPS))
        if (node->getChild(0)->getType() == Rules::EPS){
            code << "NOP" << std::endl;
        }
        else{
            for (unsigned int i = 0; i < node->getSize(); i++){
                node->getChild(i)->accept(this);
            }
        }
    }
        // STATEMENT
    else if (node->getType() == Rules::STATEMENT){
        // STATEMENT (STATEMENTS)
        if (node->getSize() == 1 && node->getChild(0)->getType() == Rules::STATEMENTS){
            node->getChild(0)->accept(this);
        }
            // STATEMENT (identifier INDEX := EXP)
        else if (node->getSize() == 4 &&
                 node->getChild(0)->getType() == Rules::NRT &&
                 node->getChild(1)->getType() == Rules::INDEX &&
                 node->getChild(3)->getType() == Rules::EXP){

            node->getChild(3)->accept(this); //EXP
            code << "LA" << " " << "$" << node->getChild(0)->getData()->getIdentifier() << std::endl;
            node->getChild(1)->accept(this); // INDEX
            code << "STR" << std::endl;
        }
            // STATEMENT (write(EXP))
        else if (node->getSize() == 4 &&
                 node->getChild(0)->getType() == Rules::NRT &&
                 node->getChild(1)->getType() == Rules::NRT &&
                 node->getChild(2)->getType() == Rules::EXP &&
                 node->getChild(3)->getType() == Rules::NRT){

            node->getChild(2)->accept(this);
            code << "PRI" << std::endl;
        }
            // STATEMENT (read(identifier INDEX))
        else if (node->getSize() == 5 &&
                 node->getChild(0)->getType() == Rules::NRT &&
                 node->getChild(1)->getType() == Rules::NRT &&
                 node->getChild(2)->getType() == Rules::NRT &&
                 node->getChild(3)->getType() == Rules::INDEX &&
                 node->getChild(4)->getType() == Rules::NRT){

            code << "REA" << std::endl;
            code << "LA" << " " << "$" << node->getChild(2)->getData()->getIdentifier() << std::endl;
            node->getChild(3)->accept(this);
            code << "STR" << std::endl;
        }
            // STATEMENT ({STAEMENTS})
        else if (node->getSize() == 3 &&
                 node->getChild(0)->getType() == Rules::NRT &&
                 node->getChild(1)->getType() == Rules::STATEMENTS &&
                 node->getChild(2)->getType() == Rules::NRT){

            node->getChild(1)->accept(this);
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

            unsigned int label1Number = this->getLabelNumber();
            unsigned int label2Number = this->getLabelNumber();

            node->getChild(2)->accept(this);
            code << "JIN" << " " << "#" << "label" << label1Number << std::endl; // TODO: label1?!
            node->getChild(4)->accept(this);
            code << "JMP" << " " << "#" << "label" << label2Number << std::endl; // TODO: label2?!
            code << "#" << "label" << label1Number << " " << "NOP" << std::endl; // TODO: label1?!
            node->getChild(6)->accept(this);
            code << "#" << "label" << label2Number << " " << "NOP" << std::endl; // TODO: label2?!
        }
            // STATEMENT while(EXP) STATEMENT
        else if (node->getSize() == 5 &&
                 node->getChild(0)->getType() == Rules::NRT &&       // while
                 node->getChild(1)->getType() == Rules::NRT &&       // (
                 node->getChild(2)->getType() == Rules::EXP &&       // EXP
                 node->getChild(3)->getType() == Rules::NRT &&       // )
                 node->getChild(4)->getType() == Rules::STATEMENT){  // STATEMENT

            unsigned int label1Number = this->getLabelNumber();
            unsigned int label2Number = this->getLabelNumber();

            code << "#" << "label" << label1Number << " " << "NOP" << std::endl; // TODO: label1?!
            node->getChild(2)->accept(this);
            code << "JIN" << " " << "#" << "label" << label2Number << std::endl; // TODO: label2?!
            node->getChild(4)->accept(this);
            code << "JMP" << " " << "#" << "label" << label1Number << std::endl; // TODO: label1?!
            code << "#" << "label" << label2Number << " " << "NOP" << std::endl; // TODO: label2?!
        }
    }
        // EXP
    else if (node->getType() == Rules::EXP){
        ParseTreeNode* EXP2      = node->getChild(0);
        ParseTreeNode* OP_EXP    = node->getChild(1);
        ParseTreeNode* OP_EXP_OP = OP_EXP->getChild(0);

        // only child is EPS
        if (OP_EXP->getInfoType() == InformationType::noType){
            EXP2->accept(this);
        }
            // first child is NRT >
        else if (OP_EXP_OP->getInfoType() == InformationType::opGreater){
            OP_EXP->accept(this);
            EXP2->accept(this);
            code << "LES" << std::endl;
        }
            // first child is NRT <:>
        else if (OP_EXP_OP->getInfoType() == InformationType::opUnequal){
            EXP2->accept(this);
            OP_EXP->accept(this);
            code << "NOT" << std::endl;
        }
        else{
            EXP2->accept(this);
            OP_EXP->accept(this);
        }
    }
        // INDEX
    else if (node->getType() == Rules::INDEX){
        if (node->getSize() == 3 &&
            node->getChild(0)->getType() == Rules::NRT &&   // [
            node->getChild(1)->getType() == Rules::EXP &&   // EXP
            node->getChild(2)->getType() == Rules::NRT){    // ]

            node->getChild(1)->accept(this);
            code << "ADD" << std::endl;
        }
    }
        // EXP2
    else if (node->getType() == Rules::EXP2){
        if (node->getSize() == 3 &&
            node->getChild(0)->getType() == Rules::NRT &&   // (
            node->getChild(1)->getType() == Rules::EXP &&   // EXP
            node->getChild(2)->getType() == Rules::NRT){    // )

            node->getChild(1)->accept(this);
        }
        else if (node->getSize() == 2 &&
                 node->getChild(0)->getType() == Rules::NRT &&  // identifier
                 node->getChild(1)->getType() == Rules::INDEX){ // INDEX

            code << "LA" << " " << "$" << node->getChild(0)->getData()->getIdentifier() << std::endl;
            node->getChild(1)->accept(this);
            code << "LV" << std::endl;
        }
        else if (node->getSize() == 1 &&
                 node->getChild(0)->getType() == Rules::NRT){
            code << "LC" << " " << node->getChild(0)->getData()->getIntegerValue() << std::endl;
        }
        else if (node->getSize() == 2 &&
                 node->getChild(0)->getType() == Rules::NRT &&
                 node->getChild(1)->getType() == Rules::EXP2){
            if (node->getChild(0)->getData()->getType() == Tokens::S_MINUS){
                code << "LC" << " 0" << std::endl;
                node->getChild(1)->accept(this);
                code << "SUB" << std::endl;
            }
            else if (node->getChild(0)->getData()->getType() == Tokens::S_EXCLAMATION){
                node->getChild(1)->accept(this);
                code << "NOT" << std::endl;
            }
        }
    }
        // OP_EXP
    else if (node->getType() == Rules::OP_EXP){
        if (node->getSize() == 2 &&
            node->getChild(0)->getType() == Rules::OP &&
            node->getChild(1)->getType() == Rules::EXP){

            node->getChild(1)->accept(this);
            node->getChild(0)->accept(this);
        }
    }
        // OP
    else if (node->getType() == Rules::OP){
        InformationType::InfoType OP_TYPE = node->getInfoType();

        if (OP_TYPE == InformationType::opPlus){
            code << "ADD" << std::endl;
        }
        else if (OP_TYPE == InformationType::opMinus){
            code << "SUB" << std::endl;
        }
        else if (OP_TYPE == InformationType::opMult){
            code << "MUL" << std::endl;
        }
        else if (OP_TYPE == InformationType::opDiv){
            code << "DIV" << std::endl;
        }
        else if (OP_TYPE == InformationType::opLess){
            code << "LES" << std::endl;
        }
        else if (OP_TYPE == InformationType::opEqual){
            code << "EQU" << std::endl;
        }
        else if (OP_TYPE == InformationType::opUnequal){
            code << "EQU" << std::endl;
        }
        else if (OP_TYPE == InformationType::opAnd){
            code << "AND" << std::endl;
        }
    }
}
