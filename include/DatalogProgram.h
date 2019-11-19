#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_

#include "Rule.h"
#include "Predicate.h"
#include <vector>
#include <iostream>
#include <string>
#include <set>

using namespace std;

class DatalogProgram {


public:

	// DatalogProgram();
	void toString();
	void setDomain();
	vector<Predicate> predicateSchemes;
	vector<Predicate> predicateFacts;
	vector<Predicate> predicateQueries;
	vector<Rule> rules;
	set<string> domain;

private:


};

#endif