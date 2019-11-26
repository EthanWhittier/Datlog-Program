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
    int getNodeID();
    bool isVisited();
    int getPostOrder();
    set<int> dependencies;


    private:
    int nodeId;
    bool visited;
    int postOrder;







};



#endif