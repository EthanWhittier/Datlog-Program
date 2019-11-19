#include "Predicate.h"

using namespace std;


Predicate::Predicate() {



}

void Predicate::toString() {

	cout << "  " << name << "(";

	for (unsigned int i = 0; i < paramList.size() - 1; i++) {

		cout << paramList.at(i) << ",";
	}

	cout << paramList.at(paramList.size() - 1);

	cout << ")";
}


void Predicate::setName(string name) {
	this->name = name;
}

void Predicate::setParam(string param) {

	paramList.push_back(param);

}
