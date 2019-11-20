
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Predicate.h"
#include "Interpreter.h"
#include <iostream>
#include <string>

void testJoin() {


Scheme Scheme1;
Scheme1.push_back("A");
Scheme1.push_back("B");
//Scheme1.push_back("Fish");
Scheme Scheme2;
Scheme2.push_back("B");
Scheme2.push_back("C");
//Scheme2.push_back("Bird");
//Scheme2.push_back("Bunny");

Relation Relation1("alpha", Scheme1);
Relation Relation2("beta", Scheme2);

Tuple Tuple1;
Tuple1.push_back("1");
Tuple1.push_back("2");
//Tuple1.push_back("5");
Tuple Tuple2;
Tuple2.push_back("2");
Tuple2.push_back("2");
//Tuple2.push_back("1");
Tuple Tuple3;
Tuple3.push_back("2");
Tuple3.push_back("3");
//Tuple3.push_back("2");
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
tuple1.push_back("1");
tuple1.push_back("1");
//tuple1.push_back("2");
//tuple1.push_back("4");
Tuple tuple2;
tuple2.push_back("2");
tuple2.push_back("2");
//tuple2.push_back("9");
//tuple2.push_back("2");
/*Tuple tuple3;
tuple3.push_back("4");
tuple3.push_back("3");
tuple3.push_back("2");
tuple3.push_back("7");
Tuple tuple4;
tuple4.push_back("1");
tuple4.push_back("5");
tuple4.push_back("2");
tuple4.push_back("4");
Tuple tuple5;
tuple5.push_back("1");
tuple5.push_back("5");
tuple5.push_back("8");
tuple5.push_back("3");*/


Relation2.addTuple(tuple1);
Relation2.addTuple(tuple2);
/*Relation2.addTuple(tuple3);
Relation2.addTuple(tuple4);
Relation2.addTuple(tuple5);*/


Relation1 = Relation1.Join(Relation2);

Relation1.toString();

}


int main(int argc, char* argv[]) {



	/*string fileName = argv[1];

	Scanner DataLogScanner(fileName);
	Token GroupedTokens;

	DataLogScanner.ReadFromFile();

	Parser parser(DataLogScanner.tokens);
	Predicate pred;

	parser.parse();

	Interpreter interperter(parser.datalog);

	interperter.EvaluateQueries();*/


	testJoin();
   


	return 0;
}
