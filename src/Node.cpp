#include <Node.h>



Node::Node(int ruleNumber) {

    nodeId = ruleNumber;
    visited = false;

}




int Node::getNodeID() {

    return nodeId;

}

bool Node::isVisited() {

    return visited;

}