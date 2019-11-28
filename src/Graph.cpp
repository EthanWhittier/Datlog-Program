#include <Graph.h>

Graph::Graph() {



}


void Graph::DepthFirstForest(bool order) {

    for(unsigned int i = 0; i < graph.size(); i++) {
        graph[i].setVist(false);
    }

   if(order) { 
        for(unsigned int i = 0; i < graph.size(); i++) {
            if(!graph[i].isVisited()) {
               DepthFirstSearch(i, true);
            }
        }
   }
   else {
       int nodeToVisit = postOrderList.size();
       for(unsigned int i = 0; i < postOrderList.size(); i++) {
           for(unsigned int j = 0; j < postOrderList.size(); j++) {
               if(postOrderList.at(j) == nodeToVisit) {
                  if(!graph[j].isVisited()) {
                   scc.clear();
                   DepthFirstSearch(j, false);
                   SCC.push_back(scc);
                   nodeToVisit--;
                   break;
                  }
               }
           }

       }
   }


}

void Graph::DepthFirstSearch(int i, bool add) {

    scc.push_back(i);
    bool visit = true;
    graph[i].setVist(visit);
    set<unsigned int>::iterator it;

    for(it = graph[i].dependencies.begin(); it != graph[i].dependencies.end(); it++) {

        if(graph[*it].isVisited() == false) {
           
            DepthFirstSearch(*it, add);
            
        }

    }
    
    if(add) {
        postOrderList.push_back(i + 1);
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