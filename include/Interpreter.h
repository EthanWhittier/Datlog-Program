#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "DatalogProgram.h"
#include "Relation.h"
#include "Database.h"
#include "Node.h"
#include "Graph.h"
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
        void EvaluateRulePred(string relationName, vector<string>paramList);
        Relation JoinMultiple();
        bool isConstant(string parameter);
        int TupleCount();
        Relation checkTuples(int i);
        void CreateDependancies();
        void CreateReverseDependancies();
        int tuplesBeforeRules = 0;
        int tuplesAfterRules = 0;
        int numberOfPasses = 0;
        string relationName;
        string parameter;
        map<string, Relation>::iterator ptr;
        vector<string> queryParams;
        vector<string> ruleParams;
        vector<Relation> queryAnswers;
        vector<Relation> ruleAnswers;
        vector<unsigned int> columns;
		void toStringQuery();
        void toStringRuleEval(int i);
        void toStringNewTuples();
        vector<Relation> evaluatedRules;
        Relation relationFromRule;
        Graph forwardGraph;
        Graph reverseGraph;
        

};






#endif
