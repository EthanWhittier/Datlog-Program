#ifndef PARSER_H_
#define PARSER_H_

#include "Rule.h"
#include "Token.h"
#include "Predicate.h"
#include "DatalogProgram.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Parser {


public:

	Parser(vector<Token> inputStream);

	//HelperFunctions

	void match(TokenType input, TokenType program);

	//NonTerminal Grammar
	void parse();

	void datalogProgram();

	void schemeList();
	void factList();
	void ruleList();
	void queryList();

	void scheme();
	void fact();
	void rule();
	void query();

	void headPredicate();
	void predicate();

	void predicateList();
	void parameterList();
	void stringList();
	void idList();

	void parameter();
	void expression();
	void operator_();

	void clearCurrentPred();
	void clearCurrentRule();
	DatalogProgram datalog;

private:
	unsigned int cursor;
	vector<Token> inputStream;
	TokenType input;
	TokenType program;
	string express;
	bool isExpress;
	bool finished;
	bool isRule;
	Predicate currentPred;
	Rule currentRule;
};


#endif
