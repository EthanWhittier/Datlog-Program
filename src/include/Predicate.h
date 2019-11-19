#ifndef PREDICATE_H_
#define PREDICATE_H_


#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Predicate {


public:
	Predicate();
	void toString();
	void setName(string name);
	void setParam(string param);
	string name;
	vector<string> paramList;

private:

};



#endif