#include "Token.h"
#include <string>
#include <iostream>



Token::Token() {

}

Token::Token(TokenType tType, int lineNum) {

	this->tType = tType;
	this->lineNum = lineNum;
	string undef = "";

}

Token::Token(TokenType tType, int lineNum, string variousStrings) {

	this->tType = tType;
	this->lineNum = lineNum;
	this->variousStrings = variousStrings;

}



string Token::toString() {

	switch (tType) {

	case COMMA:
		return "(COMMA,\",\"," + to_string(lineNum) + ")";
		break;
	case PERIOD:
		return "(PERIOD,\".\"," + to_string(lineNum) + ")";
		break;
	case Q_MARK:
		return "(Q_MARK,\"?\"," + to_string(lineNum) + ")";
		break;
	case LEFT_PAREN:
		return "(LEFT_PAREN,\"(\"," + to_string(lineNum) + ")";
		break;
	case RIGHT_PAREN:
		return "(RIGHT_PAREN,\")\"," + to_string(lineNum) + ")";
		break;
	case COLON:
		return "(COLON,\":\"," + to_string(lineNum) + ")";
		break;
	case COLON_DASH:
		return "(COLON_DASH,\":-\"," + to_string(lineNum) + ")";
		break;
	case MULTIPLY:
		return "(MULTIPLY,\"*\"," + to_string(lineNum) + ")";
		break;
	case ADD:
		return "(ADD,\"+\"," + to_string(lineNum) + ")";
		break;
	case SCHEMES:
		return "(SCHEMES,\"Schemes\"," + to_string(lineNum) + ")";
		break;
	case FACTS:
		return "(FACTS,\"Facts\"," + to_string(lineNum) + ")";
		break;
	case RULES:
		return "(RULES,\"Rules\"," + to_string(lineNum) + ")";
		break;
	case QUERIES:
		return "(QUERIES,\"Queries\"," + to_string(lineNum) + ")";
		break;
	case ID:
		return "(ID,\"" + variousStrings + "\"," + to_string(lineNum) + ")";
		break;
	case STRING:
		return "(STRING,\"'" + variousStrings + "'\"," + to_string(lineNum) + ")";
		break;
	case  COMMENT:
		return "(COMMENT,\"#" + variousStrings + "\"," + to_string(lineNum) + ")";
		break;
	case UNDEFINED:
		return "(UNDEFINED,\"" + variousStrings + "\"," + to_string(lineNum) + ")";
		break;
	case EF:
		return "(EOF,\"\"," + to_string(lineNum) + ")";
		break;
	default:
		break;
	}
	return "";

}
