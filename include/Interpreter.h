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
        void EvaluateRules();

    private:
        DatalogProgram datalog;
		Database database;
        void EvaluateQuery(string relationName, vector<string>paramList);
        void EvaluateRule();
        bool isConstant(string parameter);
        int TupleCount();
        int tuplesBeforeRules = 0;
        int tuplesAfterRules = 0;
        string relationName;
        string parameter;
        map<string, Relation>::iterator ptr;
        vector<string> queryParams;
        vector<Relation> queryAnswers;
        vector<unsigned int> columns;
		void toStringQuery();

};






#endif
