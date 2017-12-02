//
// Created by stefan on 02.12.17.
//

#ifndef TREE_INCLUDES_PARSETREENODE
#define TREE_INCLUDES_PARSETREENODE

#include "../../Scanner/includes/Token.h"
#include "DoubleLinkedList.h"
#include "RuleTypes.h"
#include "TreeVisitor.h"
//#include "InformationType.h"

class TreeVisitor;
class ParseTreeNode {
public:
    /**
     * Constructs a new ParseTreeNode with the given expected type.
     * @param expectedType expected Rule Type for this Node
     */
    ParseTreeNode(Rules::RuleType expectedType);
    /**
     * Constructs a new ParseTreeNode with the given expected type and holding data.
     * @param expectedType expected Rule Type for this node
     * @param data the Token to be stored in this node
     */
    ParseTreeNode(Rules::RuleType expectedType, Token* data);
    /**
     * Constructs a new ParseTreeNode holding the given data.
     * @param data the Token to be stored in this node
     */
    ParseTreeNode(Token* data);
    /**
     * deletes this node.
     */
    virtual ~ParseTreeNode();

    void accept(TreeVisitor* visitor);
    //   void check(TreeVisitor* visitor);

    /**
	 * returns the child at the given index (nr).
	 * @return the child at index nr
     */
    ParseTreeNode* getChild(unsigned int nr);

    /**
     * returns the data (Token) stored in this node.
     * @return Token stored in this ParseTreeNode
     */
    Token* getData();

    /**
     * returns the number of childs.
     * @return number of childs of this node
     */
    unsigned int getSize();

    /**
     * returns the expected type of this node.
     * @return expected type of this node
     */
    Rules::RuleType getType();

    /**
     * returns true if this node has one or more childs.
     * @return true if this node has one or more childs
     */
    bool hasChildren();

    /**
     * adds the given ParseTreeNode as new last child of this node.
     * @param child new child to be added as new last child
     */
    void addChild(ParseTreeNode* child);

    /**
     * returns all childs in a DoublyLinkedList in correct order.
     * @return all childs in a DoublyLinkedList in correct order.
     */
    DoublyLinkedList<ParseTreeNode>* getChildren();

    /**
     * overwrites existing eventually existing data with the given new data.
     * @param new data Token for this node
     */
    void setData(Token* data);
    //  void makeCode(std::ostream &code);

    friend std::ostream& operator<< (std::ostream &out, ParseTreeNode &node);

    /**
     * prints all leaves of this tree node to cout
     */
    void printLeaves();

    /**
     * prints the tree formatted to cout
     */
    void print(unsigned int level);

    void setInfoType(Information infoType);
    Information getInfoType();
private:
    static const char* const ruleTypeNames[] ;

    Rules::RuleType expectedType;
    Information infoType;
    ParseTreeNode* parent;
    DoublyLinkedList<ParseTreeNode>* children;
    Token* data;
};

#endif TREE_INCLUDES_PARSETREENODE
