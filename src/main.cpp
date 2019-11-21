
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Predicate.h"
#include "Interpreter.h"
#include <iostream>
#include <string>

void testJoin() {


Scheme Scheme1;
Scheme1.push_back("s");
Scheme1.push_back("n");
Scheme1.push_back("a");
Scheme1.push_back("p");
Scheme Scheme2;
Scheme2.push_back("c");
Scheme2.push_back("s");
Scheme2.push_back("g");


Relation Relation1("alpha", Scheme1);
Relation Relation2("beta", Scheme2);

Tuple Tuple1;
Tuple1.push_back("12345");
Tuple1.push_back("C. Brown");
Tuple1.push_back("12 Apple St.");
Tuple1.push_back("555-1234");
Tuple Tuple2;
Tuple2.push_back("22222");
Tuple2.push_back("P. Patty");
Tuple2.push_back("56 Grape Blvd");
Tuple2.push_back("555-9999");
Tuple Tuple3;
Tuple3.push_back("33333");
Tuple3.push_back("Snoopy");
Tuple3.push_back("12 Apple St.");
Tuple3.push_back("555-1234");
/*Tuple Tuple4;
Tuple4.push_back("3");
Tuple4.push_back("3");
Tuple4.push_back("2");
Tuple Tuple5;
Tuple5.push_back("6");
Tuple5.push_back("7");
Tuple5.push_back("4");*/

Relation1.addTuple(Tuple1);
Relation1.addTuple(Tuple2);
Relation1.addTuple(Tuple3);
//Relation1.addTuple(Tuple4);
//Relation1.addTuple(Tuple5);


Tuple tuple1;
tuple1.push_back("CS101");
tuple1.push_back("12345");
tuple1.push_back("A");
//tuple1.push_back("4");
Tuple tuple2;
tuple2.push_back("CS101");
tuple2.push_back("22222");
tuple2.push_back("B");
//tuple2.push_back("2");
Tuple tuple3;
tuple3.push_back("CS101");
tuple3.push_back("33333");
tuple3.push_back("C");
//tuple3.push_back("7");
Tuple tuple4;
tuple4.push_back("EE200");
tuple4.push_back("12345");
tuple4.push_back("B+");
//uple4.push_back("4");
Tuple tuple5;
tuple5.push_back("EE200");
tuple5.push_back("22222");
tuple5.push_back("B");
//tuple5.push_back("3");


Relation2.addTuple(tuple1);
Relation2.addTuple(tuple2);
Relation2.addTuple(tuple3);
Relation2.addTuple(tuple4);
Relation2.addTuple(tuple5);


Relation1 = Relation1.Join(Relation2);

Relation1.toString();

}


int main(int argc, char* argv[]) {



	string fileName = argv[1];

	Scanner DataLogScanner(fileName);
	Token GroupedTokens;

	DataLogScanner.ReadFromFile();

	Parser parser(DataLogScanner.tokens);
	Predicate pred;

	parser.parse();

	Interpreter interperter(parser.datalog);

	interperter.EvaluateRules();

	interperter.EvaluateQueries();




	
   


	return 0;
}
