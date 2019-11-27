#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <Node.h>
#include <vector>
#include <string>
#include <map>



using namespace std;


class Graph {


    public:
    Graph();
    string toString();
    void DepthFirstSearch();
    void DepthFirstForest();
    map<int, Node> graph;



    private:





};


#endif 