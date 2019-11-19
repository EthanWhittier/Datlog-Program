
#include "Token.h"
#include <string>
#include <iostream>
#include <cctype>
#include <fstream>
#include <vector>
#include "Scanner.h"

using namespace std;

Scanner::Scanner(string fileName) {

	this->fileName = fileName;
	ifstream inputFile;
	lineNum = 1;
	isString = false;
	newString = false;
	isComment = false;
	newComment = false;
	numTokens = 0;
}

void Scanner::ReadFromFile() {

	string inputLine;
	inputFile.open(fileName);

	if (!inputFile.is_open()) {
		cout << "Not open" << endl;
		return;
	}

	while (!inputFile.eof()) {

		getline(inputFile, inputLine);
		ProcessLine(inputLine);

		if (inputFile.peek() != EOF) {

			lineNum++;

		}
	}
	if (isComment && comment != "") {
		undefined = "#|" + comment;
		int number = lineNum;
		lineNum = commentStart;
		Tokenize(UNDEFINED);
		lineNum = number;
	}
	if (numTokens != 0) {
		lineNum++;
	}
	Tokenize(EF);
	inputFile.close();
}

void Scanner::ProcessLine(string line) {

	this->line = line;
	string tokenString;
	stringSize = line.size();
	isID = false;

	if (line.empty()) {
		if (isComment) {
			comment += '\n';
			return;
		}
		else {
			return;
		}
	}

	for (i = 0; i < line.size(); i++) {

		if (isString) {
			ProcessString();
		}
		else if (isComment) {
			ProcessComment();
		}


		else if (!isalpha(line.at(i))) {

			if (id != "")
			{
				Tokenize(ID);
			}

			ProcessSymbol(line.at(i));
		}
		else if (isalpha(line.at(i)))
		{
			ProcessLetter(line.at(i));
		}


	}

	if (id != "") {
		Tokenize(ID);
	}



	return;
}

void Scanner::Tokenize(TokenType tokenType) {

	this->tokenType = tokenType;
	numTokens += 1;

	switch (tokenType) {

	case COLON: {
		Token Colon(COLON, lineNum);
		tokens.push_back(Colon);
		break;
	}
	case COMMA: {
		Token Comma(COMMA, lineNum);
		tokens.push_back(Comma);
		break;
	}
	case PERIOD: {
		Token Period(PERIOD, lineNum);
		tokens.push_back(Period);
		break;
	}
	case Q_MARK: {
		Token Q_Mark(Q_MARK, lineNum);
		tokens.push_back(Q_Mark);
		break;
	}
	case LEFT_PAREN: {
		Token Left_Paren(LEFT_PAREN, lineNum);
		tokens.push_back(Left_Paren);
		break;
	}
	case RIGHT_PAREN: {
		Token Right_Paren(RIGHT_PAREN, lineNum);
		tokens.push_back(Right_Paren);
		break;
	}
	case ADD: {
		Token Add(ADD, lineNum);
		tokens.push_back(Add);
		break;
	}
	case MULTIPLY: {
		Token Multiply(MULTIPLY, lineNum);
		tokens.push_back(Multiply);
		break;
	}
	case UNDEFINED: {
		Token Undefined(UNDEFINED, lineNum, undefined);
		tokens.push_back(Undefined);
		break;
	}
	case FACTS: {
		Token Facts(FACTS, lineNum);
		tokens.push_back(Facts);
		break;
	}
	case RULES: {
		Token Rules(RULES, lineNum);
		tokens.push_back(Rules);
		break;
	}
	case ID: {
		Token Id(ID, lineNum, id);
		tokens.push_back(Id);
		id = "";
		break;
	}
	case QUERIES: {
		Token Queries(QUERIES, lineNum);
		tokens.push_back(Queries);
		break;
	}
	case SCHEMES: {
		Token Schemes(SCHEMES, lineNum);
		tokens.push_back(Schemes);
		break;
	}
	case STRING: {
		Token strng(STRING, stringStart, String);
		tokens.push_back(strng);
		String = "";
		break;
	}
	case COMMENT: {
		Token Comment(COMMENT, commentStart, comment);
		//tokens.push_back(Comment);
		comment = "";
		break;
	}
	case COLON_DASH: {
		Token ColonDash(COLON_DASH, lineNum);
		tokens.push_back(ColonDash);
		break;
	}
	case EF: {
		Token ef(EF, lineNum);
		tokens.push_back(ef);
	}


	}

}


void Scanner::ProcessSymbol(char character) {

	this->charater = character;

	if (isString) {
		ProcessString();
	}
	else if (isComment) {
		ProcessComment();
	}
	else if (isalpha(character)) {
		return;
	}

	if (charater == ':')
	{
		if (!CheckEndOfString(i + 1)) {
			if (line.at(i + 1) == '-') {
				Tokenize(COLON_DASH);
				i++;
				return;
			}
		}
		Tokenize(COLON);
		return;
	}
	else if (charater == ',') {

		Tokenize(COMMA);
		return;
	}
	else if (charater == '.') {

		Tokenize(PERIOD);
		return;
	}
	else if (charater == '?') {

		Tokenize(Q_MARK);
		return;
	}
	else if (charater == '(') {

		Tokenize(LEFT_PAREN);
		return;
	}
	else if (charater == ')') {

		Tokenize(RIGHT_PAREN);
		return;
	}
	else if (charater == '+') {

		Tokenize(ADD);
		return;
	}
	else if (charater == '*') {

		Tokenize(MULTIPLY);
		return;
	}
	else if (character == '\'') {

		ProcessString();
	}
	else if (character == '#') {
		ProcessComment();
	}
	else if (isdigit(character) && id != "") {
		id += character;
	}

	else {

		if (!isspace(line.at(i))) {
			undefined = line.at(i);
			Tokenize(UNDEFINED);
			return;
		}


	}


}

void Scanner::ProcessLetter(char character) {

	this->charater = character;

	while (!CheckEndOfString(i + 1)) {

		if (!isalpha(line.at(i)) && !isspace(line.at(i))) {

			if (isdigit(line.at(i))) {
				id += line.at(i);
				i++;
			}
			else {
				CheckKeyWordAndID();
				ProcessSymbol(line.at(i));
				return;
			}
		}

		else if (isspace(line.at(i))) {
			break;
		}

		else {
			id += line.at(i);
			i++;
		}

	}


	if (!isalpha(line.at(i)) && !isspace(line.at(i))) {

		if (isdigit(line.at(i))) {
			id += line.at(i);
			i++;
		}
		else {
			CheckKeyWordAndID();
			ProcessSymbol(line.at(i));
			return;
		}
	}

	else if (!isspace(line.at(i))) {
		id += line.at(i);
		CheckKeyWordAndID();
	}
	else {
		CheckKeyWordAndID();
	}



}


bool Scanner::CheckEndOfString(int nextIndex) {

	if (stringSize == nextIndex) {
		return true;
	}
	else {
		return false;
	}

}


void Scanner::ProcessString() {

	if (!isString) {
		stringStart = lineNum;
	}

	if (isString && stringSize == 1 && line.at(i) == '\'') {
		Tokenize(STRING);
		isString = false;
		newString = false;
		return;
	}

	while (!CheckEndOfString(i + 1)) {


		i++;
		//Keeps cursor on track with new line
		if (i == 1 && isString && newString) {
			i--;
			newString = false;
		}

		//Checks for adjacent '
		if (!CheckEndOfString(i + 1)) {
			if (line.at(i) == '\'' && line.at(i + 1) == '\'') {
				String += '\'';
				String += '\'';
				i++;
				continue;
			}
		}


		if (line.at(i) == '\'') {
			Tokenize(STRING);
			isString = false;
			newString = false;
			return;
		}

		String += line.at(i);
	}




	if (inputFile.peek() == EOF) {
		undefined = "'" + String;
		undefined += '\n';
		int num = lineNum;
		lineNum = stringStart;
		Tokenize(UNDEFINED);
		lineNum = num;
		return;
	}

	String += '\n';
	isString = true; //New line is still a string so this checks for that
	newString = true; //This helps keep the cursor on track when starting a new string
}

void Scanner::ProcessComment() {

	if (isComment && stringSize == 1) {

		if (inputFile.peek() == EOF) {
			comment += line.at(i);
			comment += '\n';
			undefined = "#|" + comment;
			int num = lineNum;
			lineNum = commentStart;
			Tokenize(UNDEFINED);
			lineNum = num;
			comment = "";
			return;
		}
		else {
			comment += line.at(i);
			comment += '\n';
			return;
		}

	}

	else if (line.at(i + 1) != '|' && !isComment) {
		while (!CheckEndOfString(i + 1)) {

			i++;
			if (line.at(i) == '\t') {
				comment += '\t';
			}
			else {
				comment += line.at(i);
			}

		}
		commentStart = lineNum;
		Tokenize(COMMENT);
		return;
	}



	//Block Comment

	else if (line.at(i + 1) == '|' && !isComment) {

		if (!isComment) {
			commentStart = lineNum;
		}


		i++; //Moves cursor to text part of comment
		i++;

		//Handles comment without text after and file ending
		if (CheckEndOfString(i)) {
			comment += '\n';
			isComment = true;
			return;
		}

		while (!CheckEndOfString(i + 1)) {


			if (line.at(i) == '|' && line.at(i + 1) == '#') {

				comment = '|' + comment;
				comment = comment + "|#";
				Tokenize(COMMENT);
				isComment = false;
				i++;
				return;
			}


			comment += line.at(i);
			i++;
		}

		comment += line.at(i);
		comment += '\n';
		isComment = true;


		if (inputFile.peek() == EOF) {
			comment += line.at(i);
			undefined = "#|" + comment;
			Tokenize(UNDEFINED);
		}
	}




	else if (isComment) {

		while (!CheckEndOfString(i + 1)) {

			if (line.at(i) == '|' && line.at(i + 1) == '#') {

				comment = '|' + comment;
				comment = comment + "|#";
				Tokenize(COMMENT);
				isComment = false;
				newComment = false;
				i++;
				return;
			}

			comment += line.at(i);
			i++;

		}

		comment += line.at(i);
		comment += '\n';
		i++;


		if (inputFile.peek() == EOF) {
			comment.insert(1, "|");
			undefined = comment;
			Tokenize(UNDEFINED);
		}

	}

}

void Scanner::CheckKeyWordAndID() {

	if (id == "Facts") {
		Tokenize(FACTS);
		id = "";
		return;
	}
	else if (id == "Rules") {
		Tokenize(RULES);
		id = "";
		return;
	}
	else if (id == "Queries") {
		Tokenize(QUERIES);
		id = "";
		return;
	}
	else if (id == "Schemes") {
		Tokenize(SCHEMES);
		id = "";
		return;
	}
	else {
		Tokenize(ID);
		id = "";
		return;
	}

}
