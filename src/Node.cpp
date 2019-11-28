#include <Node.h>


Node::Node() {

}

Node::Node(unsigned int ruleNumber) {

    nodeId = ruleNumber;
    visited = false;

}

void Node::setVist(bool visit) {
    visited = visit;
}

int Node::getPostOrder() {
    return postOrder;
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