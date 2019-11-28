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


    //Create Nodes
    for(unsigned int i = 0; i < datalog.rules.size(); i++) {
        Node newNode(i);
        forwardGraph.graph.insert({i, newNode});
        reverseGraph.graph.insert({i, newNode});
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

    cout << "Query Evaluation" << endl;
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
    bool first = true;
    
    CreateDependancies();
    forwardGraph.toString();
    cout << endl;
    CreateReverseDependancies();
    
    reverseGraph.DepthFirstForest(first);
    first = false;
    
    forwardGraph.postOrderList = reverseGraph.postOrderList;

    forwardGraph.DepthFirstForest(false);
    
    
    cout << "Rule Evaluation" << endl;

    vector<vector<int>>::iterator it;
    for(it = forwardGraph.SCC.begin(); it != forwardGraph.SCC.end(); it++) {
        
        cout << "SCC: ";
        for(unsigned int i = 0; i < it->size(); i++) {
            if(i == it->size() - 1) {
                cout << "R" << it->at(i);
            }
            else {
                cout << "R" << it->at(i) << ",";
            }
        }
        cout << endl;

        while(tuplesAdded) {

            numberOfPasses++;
            tuplesBeforeRules = TupleCount();
            

            for(unsigned int i = 0; i < it->size(); i++) {
           
            oneLoop = false;
           
            if(forwardGraph.graph[it->at(i)].dependencies.empty() || forwardGraph.graph[it->at(i)].dependencies.size() == 1) {
                if(forwardGraph.graph[it->at(i)].dependencies.size() == 1) {
                    
                    set<unsigned int>::iterator iter;
                    iter = forwardGraph.graph[it->at(i)].dependencies.begin();
                    
                    const unsigned int id = forwardGraph.graph[it->at(i)].getNodeID();
                   
                    if(id != *iter) {
                        oneLoop = true;
                    }
                 }
                
                else {
                    oneLoop = true;
                }

            }
           
            for(unsigned int j = 0; j < datalog.rules.at(it->at(i)).rulePred.size(); j++) {

                EvaluateRulePred(datalog.rules.at(it->at(i)).rulePred.at(j).name, datalog.rules.at(it->at(i)).rulePred.at(j).paramList);

            }
            
                relationFromRule = JoinMultiple();
            
               
            //ProjectHeadPred
                for(unsigned int z = 0; z < datalog.rules.at(it->at(i)).headPred.paramList.size(); z++) {
                   
                    for(unsigned int k = 0; k < relationFromRule.scheme.size(); k++) {

                        if(relationFromRule.scheme.at(k) == datalog.rules.at(it->at(i)).headPred.paramList.at(z)) {
                            columns.push_back(k);
                            break;
                        }

                    }
                }
                bool shouldSort = false;
                relationFromRule = relationFromRule.Project(columns, shouldSort);
                columns.clear();

                relationFromRule.relationName = datalog.rules.at(it->at(i)).headPred.name;
                ptr = database.find(relationFromRule.relationName);
                relationFromRule.scheme = ptr->second.scheme;

                Relation temp;
                temp = checkTuples(it->at(i));
                
                toStringRuleEval(it->at(i));
                
                temp.toString();

                ptr->second = ptr->second.Unite(relationFromRule);
                ruleAnswers.clear();

                
        
            }

            if(oneLoop) {
                break;
            }

            tuplesAfterRules = TupleCount();

            if(tuplesBeforeRules == tuplesAfterRules) {
                tuplesAdded = false;
            }

            
            
            
        }
        
        cout << numberOfPasses << " passes: ";
        
        for(unsigned int i = 0; i < it->size(); i++) {
             if(i == it->size() - 1) {
                cout << "R" << it->at(i);
            }
            else {
                cout << "R" << it->at(i) << ",";
            }
        }

        cout << endl;
        numberOfPasses = 0;
        tuplesAdded = true;
        
    }

    cout << endl;
    
    
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

void Interpreter::toStringRuleEval(int i) {


        //Rule Head Predicate
        cout << datalog.rules.at(i).headPred.name << "(";
        for(unsigned int j = 0; j < datalog.rules.at(i).headPred.paramList.size() - 1 ; j++) {
            cout << datalog.rules.at(i).headPred.paramList.at(j) << ",";

        }
        cout << datalog.rules.at(i).headPred.paramList.at(datalog.rules.at(i).headPred.paramList.size() - 1);
        cout << ")";

        cout << " :- ";

        
        for(unsigned int j = 0; j < datalog.rules.at(i).rulePred.size() - 1; j++) {
            cout << datalog.rules.at(i).rulePred.at(j).name;
            cout << "(";
            for(unsigned int z = 0; z < datalog.rules.at(i).rulePred.at(j).paramList.size() - 1; z++) {

                cout << datalog.rules.at(i).rulePred.at(j).paramList.at(z) << ",";
            }
            cout << datalog.rules.at(i).rulePred.at(j).paramList.at(datalog.rules.at(i).rulePred.at(j).paramList.size() - 1);
            cout << "),";
        }

        cout << datalog.rules.at(i).rulePred.at(datalog.rules.at(i).rulePred.size() - 1).name;
        cout << "(";
        for(unsigned int z = 0; z < datalog.rules.at(i).rulePred.at(datalog.rules.at(i).rulePred.size() - 1).paramList.size() - 1; z++) {

             cout << datalog.rules.at(i).rulePred.at(datalog.rules.at(i).rulePred.size() - 1).paramList.at(z) << ",";
         }
        cout << datalog.rules.at(i).rulePred.at(datalog.rules.at(i).rulePred.size() - 1).paramList.at(datalog.rules.at(i).rulePred.at(datalog.rules.at(i).rulePred.size() - 1).paramList.size() - 1);
        cout << ").";   
        cout << endl;
        
    

}

Relation Interpreter::checkTuples(int i) {

    Relation newRel;
    newRel.scheme = relationFromRule.scheme;
    ptr = database.find(datalog.rules.at(i).headPred.name);

    set<Tuple>::iterator it;
    set<Tuple>::iterator tup;
    bool add = true;
    for (it = relationFromRule.Tuples.begin(); it != relationFromRule.Tuples.end(); it++) {
       
        for(tup = ptr->second.Tuples.begin(); tup != ptr->second.Tuples.end(); tup++) {

            if(*it == *tup) {
                add = false;
                break;
            }
            
        }

        if(add) {
            newRel.addTuple(*it);
        }

        add = true;

    }

    return newRel;

}

//Graph Functions

void Interpreter::CreateDependancies() {

    for(unsigned int i = 0; i < datalog.rules.size(); i++) {

        for(unsigned int j = 0; j < datalog.rules.at(i).rulePred.size(); j++) {

           for(unsigned int z = 0; z < datalog.rules.size(); z++) {

               if(datalog.rules.at(i).rulePred.at(j).name == datalog.rules.at(z).headPred.name) {

                   forwardGraph.graph[i].dependencies.insert(z);

               }

           }

        }

    }


}

void Interpreter::CreateReverseDependancies() {

    set<unsigned int>::iterator it;

    for(unsigned int i = 0; i < forwardGraph.graph.size(); i++) {

        for(it = forwardGraph.graph[i].dependencies.begin(); it != forwardGraph.graph[i].dependencies.end(); it++) {

            reverseGraph.graph[*it].dependencies.insert(i);

        }
    }


}










