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
#include <utility>


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
        Relation Project(vector<unsigned int> columns, bool shouldSort);
        Relation Join(Relation relation2);
        Relation Unite(Relation relation2);
        void Rename(vector<string>queryP, unordered_map<string, int> newColumns);
		std::string relationName;
		set<Tuple> Tuples;
        Scheme scheme;
        

    private:

        
        vector<unsigned int> columns;
        map<string, int> newColumns;
        bool isJoinable(Relation relation2);
        Scheme CombineSchemes(Relation relation2);
        void GetAttributeInBoth(Relation relation2);
        Relation CrossProduct(Relation relation2);
        Tuple CombineTuples(Relation relation2);

        vector<pair<int, int>> equalColumns;
        set<Tuple>::iterator it;
		set<Tuple>::iterator ptr;


};



#endif
