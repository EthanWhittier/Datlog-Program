#include <Graph.h>

Graph::Graph() {



}


void Graph::DepthFirstForest() {




}

void Graph::DepthFirstSearch(int i) {


    graph[i].isVisited = true;
    set<unsigned int>::iterator it;

    for(it = graph[i].dependencies.begin(); it != graph[i].dependencies.end(); it++) {

        if(graph[*it].isVisited == false) {
            DepthFirstSearch(*it);
        }

        
        

    }




}



void Graph::toString() {

    cout << "Dependancy Graph:" << endl;
    
    map<int, Node>::iterator it;
    set<unsigned int>::iterator ptr;
    unsigned int setSize = 0;

    for(it = graph.begin(); it != graph.end(); it++) {

        cout << "R" << it->first << ":";

        for(ptr = it->second.dependencies.begin(); ptr != it->second.dependencies.end(); ptr++) {
            
            setSize++;
            if(setSize == it->second.dependencies.size()) {
                cout << "R" << *ptr;
            }
            else {
                cout << "R" << *ptr << ",";
            }
            

        }
       
        cout << endl;
        setSize = 0;
        
    }



   

}