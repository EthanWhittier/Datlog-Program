#ifndef RELATION_H_
#define RELATION_H_


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "Tuple.h"
#include "Scheme.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


using namespace std;

class Relation {


    public:
        Relation(std::string relationName, Scheme scheme);
        Relation();
        void addTuple(Tuple tuple);
        void toString();
		Relation Select1(int posistion, string value);
        Relation Select2(int position1, int posistion2);
        Relation Project(vector<unsigned int> columns);
        Relation Join(Relation relation2);
        void Rename(vector<string>queryP, unordered_map<string, int> newColumns);
		std::string relationName;
		set<Tuple> Tuples;
        

    private:

        Scheme scheme;
        vector<unsigned int> columns;
        map<string, int> newColumns;
        bool isJoinable(Relation relation2);
        Scheme CombineSchemes(Relation relation2);

};



#endif
