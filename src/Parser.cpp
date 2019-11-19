#include "Parser.h"

using namespace std;


Parser::Parser(vector<Token> input) {

	cursor = 0;
	isExpress = false;
	finished = false;
	isRule = false;

	for (unsigned int i = 0; i < input.size(); i++) {
		inputStream.push_back(input.at(i));
	}
}


void Parser::match(TokenType input, TokenType program) {

	this->input = input;

	if (input == program) {
		cursor++;
		return;
	}
	else {

		throw(input);

	}

}

void Parser::parse() {

	try {

		datalogProgram();

	}
	catch (...)
	{
		cout << "Failure!" << endl;

		if (finished) {
			cout << "  " << inputStream.at(cursor).toString();
		}

		else {
			cout << "  " << inputStream.at(cursor).toString();
		}



	}



}

void Parser::datalogProgram() {

	match(inputStream.at(cursor).tType, SCHEMES);

	match(inputStream.at(cursor).tType, COLON);

	scheme();

	schemeList();

	match(inputStream.at(cursor).tType, FACTS);

	match(inputStream.at(cursor).tType, COLON);

	factList();

	match(inputStream.at(cursor).tType, RULES);

	match(inputStream.at(cursor).tType, COLON);

	ruleList();

	match(inputStream.at(cursor).tType, QUERIES);

	match(inputStream.at(cursor).tType, COLON);

	query();

	queryList();

	//cout << "Success!" << endl;

	//datalog.toString();

}

void Parser::scheme() {


	match(inputStream.at(cursor).tType, ID);
	currentPred.setName(inputStream.at(cursor - 1).variousStrings);


	match(inputStream.at(cursor).tType, LEFT_PAREN);

	match(inputStream.at(cursor).tType, ID);
	currentPred.setParam(inputStream.at(cursor - 1).variousStrings);

	idList();

	match(inputStream.at(cursor).tType, RIGHT_PAREN);

	Predicate scheme = currentPred;

	datalog.predicateSchemes.push_back(scheme);

	clearCurrentPred();

}


void Parser::schemeList() {

	if (inputStream.at(cursor).tType == ID) {  //First Set schemeList
		scheme();
		schemeList();
	}
	else if (inputStream.at(cursor).tType == FACTS) { //Follow Set schemeList
		return;
	}

}

void Parser::factList() {

	if (inputStream.at(cursor).tType == ID) {
		fact();
		factList();
	}
	else if (inputStream.at(cursor).tType == RULES) {
		return;
	}

}

void Parser::fact() {

	match(inputStream.at(cursor).tType, ID);
	currentPred.setName(inputStream.at(cursor - 1).variousStrings);

	match(inputStream.at(cursor).tType, LEFT_PAREN);

	match(inputStream.at(cursor).tType, STRING);
	currentPred.setParam("'" + inputStream.at(cursor - 1).variousStrings + "'");

	stringList();

	match(inputStream.at(cursor).tType, RIGHT_PAREN);

	match(inputStream.at(cursor).tType, PERIOD);

	Predicate facts = currentPred;

	datalog.predicateFacts.push_back(facts);

	clearCurrentPred();
}


void Parser::idList() {


	if (inputStream.at(cursor).tType == COMMA) {

		match(inputStream.at(cursor).tType, COMMA);
		match(inputStream.at(cursor).tType, ID);
		currentPred.setParam(inputStream.at(cursor - 1).variousStrings);
		idList();
	}
	else if (inputStream.at(cursor).tType == RIGHT_PAREN) {
		return;
	}


}


void Parser::rule() {

	isRule = true;

	headPredicate();

	match(inputStream.at(cursor).tType, COLON_DASH);

	predicate();

	predicateList();

	match(inputStream.at(cursor).tType, PERIOD);

	Rule rule = currentRule;

	datalog.rules.push_back(rule); 	//Add the Rule object to vector, containing head pred and body preds

	Rule Rule;

	currentRule = Rule;

	clearCurrentPred();
}

void Parser::ruleList() {

	if (inputStream.at(cursor).tType == ID) {
		rule();
		ruleList();
	}
	else if (inputStream.at(cursor).tType == QUERIES) {
		isRule = false;
		return;
	}

}

void Parser::query() {

	predicate();

	match(inputStream.at(cursor).tType, Q_MARK);

	Predicate query = currentPred;

	datalog.predicateQueries.push_back(query);

	clearCurrentPred();
}

void Parser::queryList() {

	if (inputStream.at(cursor).tType == ID) {
		query();
		queryList();
	}
	else if (inputStream.at(cursor).tType == EF) {
		return;
	}
	else {
		finished = true;
		throw(inputStream.at(cursor));
	}


}

void Parser::stringList() {

	if (inputStream.at(cursor).tType == COMMA) {
		match(inputStream.at(cursor).tType, COMMA);

		match(inputStream.at(cursor).tType, STRING);

		currentPred.setParam("'" + inputStream.at(cursor - 1).variousStrings + "'");

		stringList();
	}


}


void Parser::headPredicate() {

	match(inputStream.at(cursor).tType, ID);
	currentPred.setName(inputStream.at(cursor - 1).variousStrings);

	match(inputStream.at(cursor).tType, LEFT_PAREN);

	match(inputStream.at(cursor).tType, ID);
	currentPred.setParam(inputStream.at(cursor - 1).variousStrings);

	idList();

	match(inputStream.at(cursor).tType, RIGHT_PAREN);

	Predicate rule = currentPred;

	currentRule.setHeadPred(rule);


	clearCurrentPred();


}

void Parser::predicate() {

	match(inputStream.at(cursor).tType, ID);
	currentPred.setName(inputStream.at(cursor - 1).variousStrings);

	match(inputStream.at(cursor).tType, LEFT_PAREN);

	parameter();
	if(express != "") {
		currentPred.setParam(express);
	}
	express = "";
	isExpress = false;

	parameterList();

	match(inputStream.at(cursor).tType, RIGHT_PAREN);

	currentRule.setRulePred(currentPred);

	if(isRule) {
		clearCurrentPred();
	}


}

void Parser::predicateList() {

	if (inputStream.at(cursor).tType == COMMA) {

		match(inputStream.at(cursor).tType, COMMA);

		predicate();

		predicateList();

	}
	else if (inputStream.at(cursor).tType == PERIOD) {
		return;
	}

}


void Parser::parameterList() {

	if (inputStream.at(cursor).tType == COMMA) {

		match(inputStream.at(cursor).tType, COMMA);

		parameter();
		if(express != "") {
			currentPred.setParam(express);
		}
		express = "";
		isExpress = false;

		parameterList();
	}

	else if (inputStream.at(cursor).tType == RIGHT_PAREN) {
		return;
	}

}


void Parser::parameter() {

	if (inputStream.at(cursor).tType == STRING) {

		match(inputStream.at(cursor).tType, STRING);

		if (isExpress) {
			express.append("'" + inputStream.at(cursor - 1).variousStrings + "'");
		}
		else {
			currentPred.setParam("'" + inputStream.at(cursor - 1).variousStrings + "'");
		}

		return;

	}

	else if (inputStream.at(cursor).tType == ID) {

		match(inputStream.at(cursor).tType, ID);

		if (isExpress) {
			express.append(inputStream.at(cursor - 1).variousStrings);
		}
		else {
			currentPred.setParam(inputStream.at(cursor - 1).variousStrings);
		}

		return;

	}

	else if (inputStream.at(cursor).tType == LEFT_PAREN) {


		expression();

	}

	else {
		throw(inputStream.at(cursor).tType);
	}


}


void Parser::expression() {

	isExpress = true;

	match(inputStream.at(cursor).tType, LEFT_PAREN);
	express.append("(");

	parameter();

	operator_();

	parameter();

	match(inputStream.at(cursor).tType, RIGHT_PAREN);
	express.append(")");

	return;
}

void Parser::operator_() {

	if (inputStream.at(cursor).tType == ADD) {

		match(inputStream.at(cursor).tType, ADD);
		express.append("+");
		return;

	}

	else if (inputStream.at(cursor).tType == MULTIPLY) {

		match(inputStream.at(cursor).tType, MULTIPLY);
		express.append("*");
		return;

	}
	else {
		throw(inputStream.at(cursor).tType);
	}


}

void Parser::clearCurrentPred() {


	currentPred.setName("");
		for ( int i = currentPred.paramList.size(); i > 0; i--) {
			currentPred.paramList.pop_back();
		}

}

void Parser::clearCurrentRule() {

	currentRule.clearHeadPred();
	currentRule.clearRulePreds();

}
