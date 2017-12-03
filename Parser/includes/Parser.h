#ifndef PARSER_INCLUDES_PARSER
#define PARSER_INCLUDES_PARSER

#include <stdio.h>

#include "../../Scanner/includes/ScannerImp.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Scanner/includes/Token.h"
#include "../../Tree/includes/ParseTreeNode.h"
#include "../../Tree/includes/MakeCodeVisitor.h"
#include "../../Tree/includes/TypeCheckVisitor.h"

using namespace std;

namespace PR {
	enum ParseResult {
		RULEFOUND = 0,
		RULENOTFOUND = 1,
		ERROR = 2,
	};
}

class Parser {

public:

	Parser(char *inputfile);
	void parse(const char *outputfile);

private:
	ParseTreeNode* parseTree;

	Scanner* scanner;
	Symboltable* symtab;

	void Prog(ParseTreeNode* n);
	void Decls(ParseTreeNode* n);
	PR::ParseResult Decl(ParseTreeNode* n);

	void Array(ParseTreeNode* n);
	void Statements(ParseTreeNode* n);
	PR::ParseResult Statement(ParseTreeNode* n);
	PR::ParseResult Index(ParseTreeNode* n);
	void Exp(ParseTreeNode* n);
	void Exp2(ParseTreeNode* n);
	void OpExp(ParseTreeNode* n);
	PR::ParseResult Op(ParseTreeNode* n);
	Token* retrieveToken();
	bool checkTokenType(Token* token, TType type);
	void error(char* errorMsg);
	Token* actualToken;

};

#endif PARSER_INCLUDES_PARSER
