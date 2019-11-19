
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Predicate.h"
#include "Interpreter.h"
#include <iostream>
#include <string>




int main(int argc, char* argv[]) {



	string fileName = argv[1];

	Scanner DataLogScanner(fileName);
	Token GroupedTokens;

	DataLogScanner.ReadFromFile();

	Parser parser(DataLogScanner.tokens);
	Predicate pred;

	parser.parse();

	Interpreter interperter(parser.datalog);

	interperter.EvaluateQueries();


	
   


	return 0;
}
