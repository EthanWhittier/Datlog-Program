#include "Interpreter.h"


Interpreter::Interpreter(DatalogProgram datalog) {

    this->datalog = datalog;


	for (unsigned int i = 0; i < datalog.predicateSchemes.size(); i++) {

		string name = datalog.predicateSchemes.at(i).name;
		Scheme scheme;


        for (unsigned int j = 0; j < datalog.predicateSchemes.at(i).paramList.size(); j++) {
            scheme.push_back( datalog.predicateSchemes.at(i).paramList.at(j));
        }

        Relation relation(name, scheme);
		    database.insert({ name, relation });
    }

    for (unsigned int i = 0; i < datalog.predicateFacts.size(); i++) {

        string name = datalog.predicateFacts.at(i).name;
        Tuple tuple;

        for (unsigned int j = 0; j < datalog.predicateFacts.at(i).paramList.size(); j++) {
            tuple.push_back(datalog.predicateFacts.at(i).paramList.at(j));
        }

        map<string, Relation>::iterator it;
        it = database.find(name);
        it->second.addTuple(tuple);
    }

    map<string, Relation>::iterator it;
    for (it = database.begin(); it != database.end(); it++) {

        //it->second.toString();

    }
}

bool Interpreter::isConstant(string parameter) {

	this->parameter = parameter;

    if(parameter.at(0) == '\'') {
        return true;
    }
    else {
        return false;
    }

}


void Interpreter::EvaluateQuery(string relationName, vector<string>paramList) {

    
    //Grab Relation from Database and setup Data
    ptr = database.find(relationName);
	Relation newRelation = ptr->second;
    unordered_map<string, int> queryMap;


    for (unsigned int i = 0; i < paramList.size(); i++) {
        queryParams.push_back(paramList.at(i));
    }
    this->relationName = relationName;

    //Index Query

    //Go through ParamList and Select

    for (unsigned int i = 0; i < queryParams.size(); i ++) {


        if(isConstant(queryParams.at(i))) {

			newRelation = newRelation.Select1(i, queryParams.at(i));
			//newRelation.toString();

        }

        else {

            auto search = queryMap.find(queryParams.at(i));

            if(search != queryMap.end()) {

				newRelation = newRelation.Select2(search->second, i);
				//newRelation.toString();

            }
            else {

                //queryMap.insert({queryParams.at(i), i});
				queryMap[queryParams.at(i)] = i;
            }

        }

    }

    //Project

    unordered_map<string, int>::iterator it;
    for (it = queryMap.begin(); it != queryMap.end(); it++) {

		columns.push_back(it->second);
    }


	if (!columns.empty()) {
		newRelation = newRelation.Project(columns);
	}



	//newRelation.Rename(queryMap);
	newRelation.Rename(queryParams, queryMap);

	queryAnswers.push_back(newRelation);

	queryParams.clear();
	columns.clear();

}


void Interpreter::EvaluateQueries() {

    for (unsigned int i = 0; i < datalog.predicateQueries.size(); i++) {

		EvaluateQuery(datalog.predicateQueries.at(i).name, datalog.predicateQueries.at(i).paramList);

    }

	toStringQuery();
}

void Interpreter::toStringQuery() {


	for (unsigned int i = 0; i < queryAnswers.size(); i++) {

		cout << datalog.predicateQueries.at(i).name << "(";

		for (unsigned int j = 0; j < datalog.predicateQueries.at(i).paramList.size(); j++) {

			if (j != datalog.predicateQueries.at(i).paramList.size() - 1) {
				cout << datalog.predicateQueries.at(i).paramList.at(j) << ",";
			}
			else {
				cout << datalog.predicateQueries.at(i).paramList.at(j);
			}

		}

		cout << ")? ";


		if (queryAnswers.at(i).Tuples.empty()) {

			cout << "No" << endl;

		}
		else {

			cout << "Yes(" << queryAnswers.at(i).Tuples.size() << ")" << endl;

			for (unsigned int j = 0; j < datalog.predicateQueries.at(i).paramList.size(); j++) {

				if (datalog.predicateQueries.at(i).paramList.at(j).at(0) != '\'') {
					queryAnswers.at(i).toString();
					break;
				}


			}

		}


	}

}


void Interpreter::EvaluateRulePred(string relationName, vector<string>paramList) {

    //Grab Relation from Database and setup Data
    ptr = database.find(relationName);
	Relation newRelation = ptr->second;
    unordered_map<string, int> ruleMap;


    for (unsigned int i = 0; i < paramList.size(); i++) {
        ruleParams.push_back(paramList.at(i));
    }
    this->relationName = relationName;

    //Index Query

    //Go through ParamList and Select

    for (unsigned int i = 0; i < ruleParams.size(); i ++) {


        if(isConstant(ruleParams.at(i))) {

			newRelation = newRelation.Select1(i, ruleParams.at(i));
			

        }

        else {

            auto search = ruleMap.find(ruleParams.at(i));

            if(search != ruleMap.end()) {

				newRelation = newRelation.Select2(search->second, i);
				

            }
            else {

				ruleMap[ruleParams.at(i)] = i;
            }

        }


    }

    //Project

    unordered_map<string, int>::iterator it;
    for (it = ruleMap.begin(); it != ruleMap.end(); it++) {

		columns.push_back(it->second);
    }

	if (!columns.empty()) {
		newRelation = newRelation.Project(columns);
	}

	//newRelation.Rename(queryMap);
	newRelation.Rename(ruleParams, ruleMap);

	ruleAnswers.push_back(newRelation);

	ruleParams.clear();
	columns.clear();

}


void Interpreter::EvaluateRules() {

    bool tuplesAdded = true;
    


    while(tuplesAdded) {

        tuplesBeforeRules = TupleCount();

        for(unsigned int i = 0; i < datalog.rules.size(); i++) {

           
           for(unsigned int j = 0; j < datalog.rules.at(i).rulePred.size(); j++) {

               EvaluateRulePred(datalog.rules.at(i).rulePred.at(j).name, datalog.rules.at(i).rulePred.at(j).paramList);

           }
            
            relationFromRule = JoinMultiple();
            
               
            //ProjectHeadPred
            for(unsigned int z = 0; z < datalog.rules.at(i).headPred.paramList.size(); z++) {
                   
                 for(unsigned int k = 0; k < relationFromRule.scheme.size(); k++) {

                    if(relationFromRule.scheme.at(k) == datalog.rules.at(i).headPred.paramList.at(z)) {
                        columns.push_back(k);
                        break;
                    }
//FIXME
                }
            }
            bool shouldSort = false;
            relationFromRule = relationFromRule.Project(columns, shouldSort);
            columns.clear();

            relationFromRule.relationName = datalog.rules.at(i).headPred.name;
            ptr = database.find(relationFromRule.relationName);
            relationFromRule.scheme = ptr->second.scheme;
            ptr->second = ptr->second.Unite(relationFromRule);
            ruleAnswers.clear();
            

        }

        tuplesAfterRules = TupleCount();

        if(tuplesBeforeRules == tuplesAfterRules) {
            tuplesAdded = false;
        }
    
    }

    
        
        

}


Relation Interpreter::JoinMultiple() {


    for(unsigned int i = 0; i < ruleAnswers.size() - 1; i++) {

        ruleAnswers.at(i + 1) = ruleAnswers.at(i).Join(ruleAnswers.at(i + 1));


    }
    
    return ruleAnswers.at(ruleAnswers.size() - 1);

}


int Interpreter::TupleCount() {


    int tup = 0;

    map<string, Relation>::iterator it;

    for(it = database.begin(); it != database.end(); it++) {

        tup += it->second.Tuples.size();

    }

    return tup;


}


