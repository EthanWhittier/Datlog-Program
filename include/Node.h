#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;


class Node {

    public:
    Node();
    Node(unsigned int ruleNumber);
    int getNodeID();
    bool isVisited();
    int getPostOrder();
    set<unsigned int> dependencies;


    private:
    int nodeId;
    bool visited;
    int postOrder;

};



#endif