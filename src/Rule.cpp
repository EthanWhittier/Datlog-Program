#include "Rule.h"

using namespace std;

Rule::Rule()
{

}


void Rule::toString() {


    headPredToString(headPred);
    cout << " :- ";
    for (unsigned int i = 0; i < rulePred.size() - 1; i++) {

        predToString(rulePred.at(i));

    }

    predToStringDone(rulePred.at(rulePred.size() - 1));

    cout << ".";

    cout << endl;
}

void Rule::headPredToString(Predicate pred)  {


    cout << "  " << pred.name << "(";

	for (unsigned int i = 0; i < pred.paramList.size() - 1; i++) {

		cout << pred.paramList.at(i) << ",";
	}

	cout << pred.paramList.at(pred.paramList.size() - 1);

    cout << ")";


}


void Rule::predToString(Predicate pred) {

    cout << pred.name << "(";

	for (unsigned int i = 0; i < pred.paramList.size() - 1; i++) {

		cout << pred.paramList.at(i) << ",";
	}

	cout << pred.paramList.at(pred.paramList.size() - 1);

    cout << "),";


}


void Rule::predToStringDone(Predicate pred) {

    cout << pred.name << "(";

	for (unsigned int i = 0; i < pred.paramList.size() - 1; i++) {

		cout << pred.paramList.at(i) << ",";
	}

	cout << pred.paramList.at(pred.paramList.size() - 1);

    cout << ")";

}



void Rule::setHeadPred(Predicate headPred) {

    this->headPred = headPred;
}

void Rule::setRulePred(Predicate rulePred) {

    this->rulePred.push_back(rulePred);

}

void Rule::clearHeadPred() {

    headPred.setName("");
    for ( int i = headPred.paramList.size(); i > 0; i--) {
			headPred.paramList.pop_back();
		}

}


void Rule::clearRulePreds() {


}
