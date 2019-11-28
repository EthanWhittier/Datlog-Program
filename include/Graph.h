#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <algorithm>
#include <Node.h>
#include <vector>
#include <string>
#include <map>



using namespace std;


class Graph {


    public:
    Graph();
    void toString();
    void DepthFirstSearch(int i, bool add);
    void DepthFirstForest(bool order);
    vector<int> postOrderList;
    vector<vector<int>> SCC;
    vector<int>scc;
    map<int, Node> graph;



    private:





};


#endif 