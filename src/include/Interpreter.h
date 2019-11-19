#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "DatalogProgram.h"
#include "Relation.h"
#include "Database.h"
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Interpreter {

    public:
        Interpreter(DatalogProgram datalog);
		void EvaluateQueries();

    private:
        DatalogProgram datalog;
		Database database;
        void EvaluateQuery(string relationName, vector<string>paramList);
        bool isConstant(string parameter);
        string relationName;
        string parameter;
        map<string, Relation>::iterator ptr;
        vector<string> queryParams;
        vector<Relation> queryAnswers;
        vector<unsigned int> columns;
		void toStringQuery();

};






#endif
