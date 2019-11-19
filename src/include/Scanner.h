
#ifndef SCANNER_H_
#define SCANNER_H_
#include<string>
#include<fstream>
#include "Token.h"

using namespace std;

class Scanner {

public:
	vector<Token> tokens;
	Scanner(string fileName);
	void ReadFromFile();
	int numTokens;

private:

	// Variables

	string fileName;
	ifstream inputFile;
	string line;
	TokenType tokenType;
	string undefined;
	string id;
	string String;
	string comment;
	int stringStart;
	int commentStart;
	int numSingleQuote;
	char charater;
	int stringSize;
	unsigned int i;
	int currentIndex;
	bool resetID;
	bool isString;
	bool newString;
	bool newComment;
	bool isComment;
	bool isID;
	int lineNum;


	//Functions



	void Tokenize(TokenType token);
	void ProcessLine(string line);
	bool CheckEndOfString(int nextIndex);
	void ProcessSymbol(char character);
	void ProcessLetter(char character);
	void ProcessString();
	void ProcessComment();
	void CheckKeyWordAndID();



















};



#endif