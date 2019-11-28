#include <Node.h>


Node::Node() {

}

Node::Node(unsigned int ruleNumber) {

    nodeId = ruleNumber;
    visited = false;

}

void Node::setPostOrder(int post) {
    postOrder = post;
}


int Node::getNodeID() {

    return nodeId;

}

bool Node::isVisited() {

    return visited;

}