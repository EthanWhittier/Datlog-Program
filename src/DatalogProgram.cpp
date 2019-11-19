#include "DatalogProgram.h"


using namespace std;



void DatalogProgram::toString() {

	cout << "Schemes(" << predicateSchemes.size() << "):" << endl;
	for (unsigned int i = 0; i < predicateSchemes.size(); i++) {
		predicateSchemes.at(i).toString();
		cout << endl;
	}

	cout << "Facts(" << predicateFacts.size() << "):" << endl;
	for (unsigned int i = 0; i < predicateFacts.size(); i++)  {
		predicateFacts.at(i).toString();
		cout << "." << endl;
		}

	cout << "Rules(" << rules.size() << "):" << endl;
	for (unsigned int i = 0; i < rules.size(); i++) {
		rules.at(i).toString();
	}

	cout << "Queries(" << predicateQueries.size() << "):" << endl;
	for (unsigned int i = 0; i < predicateQueries.size(); i++) {
		predicateQueries.at(i).toString();
		cout << "?" << endl;
		}

	setDomain();
	cout << "Domain(" << domain.size() << "):" << endl;
	for (auto it = domain.begin(); it != domain.end(); it++) {
		cout << *it << endl;
	}
}

void DatalogProgram::setDomain() {

	for (unsigned int i = 0; i < predicateFacts.size(); i++) {

		for (unsigned int j = 0; j < predicateFacts.at(i).paramList.size(); j++) {

			domain.insert(predicateFacts.at(i).paramList.at(j));

		}

	}
}
