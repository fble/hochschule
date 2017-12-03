#include "../includes/Parser.h"

Parser::Parser(const char *inputfile) {
	this->symtab = new Symboltable(1000);
	this->scanner = new Scanner(inputfile, this->symtab);

	Output::init("scannerout.txt");
	this->scanner->init();
}

//TODO questions:
//Was wenn Error beim parsen?
void Parser::parse(const char *outputfile) {
	parseTree = new ParseTreeNode(Rules::PROG);


	std::ofstream codeFile;
	codeFile.open(outputfile);
	codeFile << std::left;

	std::cout << "parsing ..." << std::endl;
	Prog(parseTree);

	std::cout << "type checking ..." << std::endl;
	parseTree->accept(new TypeCheckVisitor(this->symtab));

	std::cout << "generate code ..." << std::endl;
	parseTree->accept(new MakeCodeVisitor(codeFile));
}

Token* Parser::retrieveToken() {

	//std::cout << " retrieve " << std::endl;


	if (scanner->isFileEnd()) {
		return 0;
	}

	//1. default, return token directly from scanner
	Token* token = scanner->nextToken();
	return token;

}



//TODO better  place for nextToken?
//TODO error if invalid token sequence found
void Parser::Prog(ParseTreeNode* n) {
	actualToken = retrieveToken();
	Decls(n);
	Statements(n);
}

void Parser::Decls(ParseTreeNode* n) {
	ParseTreeNode* declsNode = new ParseTreeNode(Rules::DECLS);
	n->addChild(declsNode);
	PR::ParseResult result = Decl(declsNode);
	if (result == PR::RULEFOUND
		&&  checkTokenType(actualToken,Semicolon)) {

		declsNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		Decls(declsNode);
	} else if (result == PR::RULENOTFOUND) {
		//error, only if a rule in Decl was found (?)
		declsNode->addChild(new ParseTreeNode(Rules::EPS));
	} else if (result == PR::RULEFOUND
			   &&  !checkTokenType(actualToken, Semicolon)) {
		error("Error in Decls");
	}
}

PR::ParseResult Parser::Decl(ParseTreeNode* n) {

	if ( checkTokenType(actualToken, Int)) {
		ParseTreeNode* declNode = new ParseTreeNode(Rules::DECL);
		n->addChild(declNode);
		declNode->addChild(new ParseTreeNode(actualToken));

		actualToken = retrieveToken();
		Array(declNode);
		if (checkTokenType(actualToken, Identifier)) {

			declNode->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();
			return PR::RULEFOUND;
		} else {
			error("decl");
			return PR::RULENOTFOUND;
		}
	} else {
		return PR::RULENOTFOUND;
	}
}



void Parser::Array(ParseTreeNode* n) {
	ParseTreeNode* arrayNode = new ParseTreeNode(Rules::ARRAY);
	n->addChild(arrayNode);
	if (checkTokenType(actualToken, OS_Bracket)) {
		arrayNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		if (checkTokenType(actualToken,  Int)) {
			arrayNode->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();
			if (checkTokenType(actualToken, CS_Bracket)) {
				arrayNode->addChild(new ParseTreeNode(actualToken));
				actualToken = retrieveToken();
			} else {
				error("array");
			}
		} else {
			//Error
			error("array");
		}
	} else {
		arrayNode->addChild(new ParseTreeNode(Rules::EPS));
	}
}

void Parser::Statements(ParseTreeNode* n) {
	ParseTreeNode* statementsNode = new ParseTreeNode(Rules::STATEMENTS);
	n->addChild(statementsNode);
	PR::ParseResult result = Statement(statementsNode);
	if (result == PR::RULEFOUND
		&& checkTokenType(actualToken,  Semicolon)) {
		statementsNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		Statements(statementsNode);
	} else if (result == PR::RULENOTFOUND) {
		statementsNode->addChild(new ParseTreeNode(Rules::EPS));
	} else if (result == PR::RULEFOUND
			   && !checkTokenType(actualToken,  Semicolon)) {
		error("statements");
	}
}

PR::ParseResult Parser::Statement(ParseTreeNode* n) {
	PR::ParseResult result = PR::RULENOTFOUND;
	ParseTreeNode* statementNode = new ParseTreeNode(Rules::STATEMENT);


	if (checkTokenType(actualToken,  Identifier)) {
		statementNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();

		Index(statementNode);
		if (checkTokenType(actualToken, Assign)) {
			statementNode->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();
			Exp(statementNode);
			result = PR::RULEFOUND;
		} else {
			error("statement");
			result =PR::ERROR;
		}
	} else if (checkTokenType(actualToken, Write)) {
		statementNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();

		if (checkTokenType(actualToken, OR_Bracket)) {
			statementNode->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();

			Exp(statementNode);
			if (checkTokenType(actualToken, CR_Bracket)) {

				statementNode->addChild(new ParseTreeNode(actualToken));
				actualToken = retrieveToken();
				result = PR::RULEFOUND;
			} else {
				error("statement");
				result =PR::ERROR;
			}
		} else {
			error("statement");
			result = PR::ERROR;
		}
	} else if (checkTokenType(actualToken,  Read)) {
		statementNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		if (checkTokenType(actualToken, OR_Bracket)) {
			statementNode->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();
			if (checkTokenType(actualToken,  Identifier)) {
				statementNode->addChild(new ParseTreeNode(actualToken));
				actualToken = retrieveToken();
				Index(statementNode);
				if (checkTokenType(actualToken, CR_Bracket)) {
					statementNode->addChild(new ParseTreeNode(actualToken));
					actualToken = retrieveToken();
					result = PR::RULEFOUND;
				} else {
					error("statement");
					result = PR::ERROR;
				}
			} else {
				error("statement");
				result = PR::ERROR;
			}
		} else {
			error("statement");
			result =PR::ERROR;
		}

	} else if (checkTokenType(actualToken,  OpeningBrace)) {
		statementNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		Statements(statementNode);
		if (checkTokenType(actualToken,  ClosingBrace)) {
			statementNode->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();
			result = PR::RULEFOUND;
		} else {
			error("statement");
			result = PR::ERROR;
		}
	} else if (checkTokenType(actualToken,  If)) {
		statementNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		if (checkTokenType(actualToken, OR_Bracket)) {
			statementNode->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();
			Exp(statementNode);
			if (checkTokenType(actualToken, CR_Bracket)) {
				statementNode->addChild(new ParseTreeNode(actualToken));
				actualToken = retrieveToken();
				result = Statement(statementNode);
				if (result == PR::RULEFOUND && checkTokenType(actualToken, Else)) {
					statementNode->addChild(new ParseTreeNode(actualToken));
					actualToken = retrieveToken();
					result = Statement(statementNode);
					//result = PR::RULEFOUND;
				} else {
					error("statement");
					result = PR::ERROR;
				}
			} else {
				error("statement");
				result = PR::ERROR;
			}
		} else {
			error("statement");
			result = PR::ERROR;
		}
	} else if (checkTokenType(actualToken, While)) {
		statementNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		if (checkTokenType(actualToken, OR_Bracket)) {
			statementNode->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();
			Exp(statementNode);
			if (checkTokenType(actualToken, CR_Bracket)) {
				statementNode->addChild(new ParseTreeNode(actualToken));
				actualToken = retrieveToken();
				result = Statement(statementNode);
				//result = PR::RULEFOUND;
			} else {
				error("statement");
				result = PR::ERROR;
			}
		} else {
			error("statement");
			result = PR::ERROR;
		}
	}

	else {
		result = PR::RULENOTFOUND;
	}
	if(result == PR::RULEFOUND){
		n->addChild(statementNode);
	}

	return result;
}

PR::ParseResult Parser::Index(ParseTreeNode* n) {
	ParseTreeNode* indexNode = new ParseTreeNode(Rules::INDEX);
	n->addChild(indexNode);

	if (checkTokenType(actualToken, OS_Bracket)) {
		indexNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		Exp(indexNode);
		if (checkTokenType(actualToken, CS_Bracket)) {
			indexNode->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();
			return PR::RULEFOUND;
		} else {
			error("index");
			return PR::ERROR;
		}
	} else {
		indexNode->addChild(new ParseTreeNode(Rules::EPS));
		return PR::RULENOTFOUND;
	}
}

void Parser::Exp(ParseTreeNode* n) {
	ParseTreeNode* expNode = new ParseTreeNode(Rules::EXP);
	n->addChild(expNode);

	Exp2(expNode);
	OpExp(expNode);
}

void Parser::Exp2(ParseTreeNode* n) {
	ParseTreeNode* exp2Node = new ParseTreeNode(Rules::EXP2);
	n->addChild(exp2Node);

	if (checkTokenType(actualToken, OR_Bracket)) {
		exp2Node->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		Exp(exp2Node);
		if (checkTokenType(actualToken, CR_Bracket)) {
			exp2Node->addChild(new ParseTreeNode(actualToken));
			actualToken = retrieveToken();
		} else {
			error("exp2");
		}
	} else if (checkTokenType(actualToken, Identifier)) {
		exp2Node->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		Index(exp2Node);
	} else if (checkTokenType(actualToken,  Int)) {
		exp2Node->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
	} else if (checkTokenType(actualToken, Minus)) {
		exp2Node->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		Exp2(exp2Node);
	} else if (checkTokenType(actualToken, Not)) {
		exp2Node->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		Exp2(exp2Node);
	} else {
		error("exp2");
	}
}

void Parser::OpExp(ParseTreeNode* n) {
	ParseTreeNode* opExpNode = new ParseTreeNode(Rules::OP_EXP);
	n->addChild(opExpNode);

	PR::ParseResult result = Op(opExpNode);
	if (result == PR::RULEFOUND) {
		Exp(opExpNode);
	} else {
		opExpNode->addChild(new ParseTreeNode(Rules::EPS));
	}
}

PR::ParseResult Parser::Op(ParseTreeNode* n) {

	if (checkTokenType(actualToken,  Plus)
		|| checkTokenType(actualToken, Minus)
		|| checkTokenType(actualToken,  Stern)
		|| checkTokenType(actualToken, Division)
		|| checkTokenType(actualToken,  GreaterThan)
		|| checkTokenType(actualToken,  LessThan)
		|| checkTokenType(actualToken, Equal)
		|| checkTokenType(actualToken, NotEqual)
		|| checkTokenType(actualToken, Tokens::S_AMP)) { // Wtf, was ist AMP??
		ParseTreeNode* opNode = new ParseTreeNode(Rules::OP);
		n->addChild(opNode);
		opNode->addChild(new ParseTreeNode(actualToken));
		actualToken = retrieveToken();
		//TODO valid
		return PR::RULEFOUND;
	} else {
		return PR::RULENOTFOUND;
	}
}

bool Parser::checkTokenType(Token* token, TType type) {
	if(token != 0 && token->getType() == type){
		return true;
	}
	return false;
}

void Parser::error(char* errorMsg) {
	std::cerr << errorMsg << " " << "not valid" << "\n" << *actualToken << std::endl;
	throw "Parse Error";
}

