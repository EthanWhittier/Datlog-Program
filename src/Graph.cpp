#include <Graph.h>

Graph::Graph() {



}

string Graph::toString() {

    cout << "Dependancy Graph:" << endl;
    map<int, Node>::iterator it;

    for(it = graph.begin(); it != graph.end(); it++) {

        cout << "R" << it->first << ":"
        


    }





}