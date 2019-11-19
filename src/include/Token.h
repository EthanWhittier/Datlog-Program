
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

using namespace std;

enum TokenType
{
	COMMA,
	PERIOD,
	Q_MARK,
	LEFT_PAREN,
	RIGHT_PAREN,
	COLON,
	COLON_DASH,
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
	UNDEFINED,
	EF

};

class Token {

public:

	Token();
	Token(TokenType tType, int lineNum);
	Token(TokenType tType, int lineNum, string variousStrings);
	Token(TokenType tType, int lineNum, string variousStrings, int index);
	string toString();
	vector<Token> Tokens;
	TokenType tType;
	string variousStrings;

private:
	int lineNum;
	int index;

};


#endif






