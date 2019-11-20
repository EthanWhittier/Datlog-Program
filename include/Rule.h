#ifndef RULE_H_
#define RULE_H_

#include "Predicate.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;


class Rule
{

public:
	Rule();
	void toString();
	void predToString(Predicate pred);
	void predToStringDone(Predicate pred);
	void setHeadPred(Predicate headPred);
	void setRulePred(Predicate rulePred);
	void clearHeadPred();
	void clearRulePreds();
	void headPredToString(Predicate pred);
	Predicate headPred;
	vector<Predicate> rulePred;


private:



};



#endif

