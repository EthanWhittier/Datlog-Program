#include "Relation.h"


Relation::Relation(std::string relationName, Scheme scheme) {

    this->relationName = relationName;
    this->scheme = scheme;
}

Relation::Relation() {

}


void Relation::addTuple(Tuple tuple) {
    Tuples.insert(tuple);
}

void Relation::toString() {


	set<Tuple>::iterator ptr;
   for (ptr = Tuples.begin(); ptr != Tuples.end(); ptr++) {

	   cout << "  ";

	   for (unsigned int i = 0; i < scheme.size(); i++) {
		   if (i != scheme.size() - 1) {

			   cout << scheme.at(i) << "=" << ptr->at(i) << ", ";
		   }
		   else {
			   cout << scheme.at(i) << "=" << ptr->at(i);
		   }
       }
	   cout << endl;
    }

}



Relation Relation::Select1(int position, string value) {
    unsigned int Position = position;
    Relation newRelation(relationName, scheme);

    for (unsigned int i = 0; i < scheme.size(); i++) {

        if(i == Position) {

            set<Tuple>::iterator it;
            for (it = Tuples.begin(); it != Tuples.end(); it++) {
                if(it->at(i)==value) {
                    newRelation.addTuple(*it);
                }
            }
        }
    }

    return newRelation;
}

Relation Relation::Select2(int position1, int position2) {

    Relation newRelation(relationName, scheme);

    set<Tuple>::iterator it;
    for (it = Tuples.begin(); it != Tuples.end(); it++) {

        if(it->at(position1) == it->at(position2)) {

            newRelation.addTuple(*it);
			//break;

        }
    }

    return newRelation;
}

Relation Relation::Project(vector<unsigned int> columns) {


	if (columns.empty()) {

	}

	sort(columns.begin(), columns.end());

    for (unsigned int i = 0; i < columns.size(); i++) {
        this->columns.push_back(columns.at(i));
    }

    Scheme newScheme;
	for (unsigned int i = 0; i < scheme.size(); i++) {

		for (unsigned int j = 0; j < columns.size(); j++) {
			if (i == columns.at(j)) {
				newScheme.push_back(scheme.at(i));
			}
		}
  }


	Relation newRelation(relationName, newScheme);
	set<Tuple>::iterator it;
	for (it = Tuples.begin(); it != Tuples.end(); it++) {
		Tuple tup;
		for (unsigned int i = 0; i < columns.size(); i++) {
			tup.push_back(it->at(columns.at(i)));
		}
		newRelation.addTuple(tup);
	}

	return newRelation;

}



void Relation::Rename(vector<string>queryP, unordered_map<string, int>newColumns) {

    if(newColumns.empty()) {
        return;
    }
		unordered_map<string, int>::iterator it;

		for (auto it = queryP.begin(); it != queryP.end();) {
				if(it->at(0) == '\'') {
					it = queryP.erase(it);
				}
				else {
					it++;
				}

		}

    queryP.erase(unique(queryP.begin(), queryP.end()), queryP.end());

		for (unsigned int i = 0; i < scheme.size(); i++) {
			scheme.at(i) = queryP.at(i);
		}



	 }
