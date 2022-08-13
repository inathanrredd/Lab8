#include <iostream>
#include "Node.h"

using namespace std;

/*
* Returns the data that is stored in this node
*
* @return the data that is stored in this node.
*/
int Node::getData() const {
    return data;
}

/*
* Returns the left child of this node or null if it doesn't have one.
*
* @return the left child of this node or null if it doesn't have one.
*/
NodeInterface * Node::getLeftChild() const {
    return(left);
}

/*
* Returns the right child of this node or null if it doesn't have one.
*
* @return the right child of this node or null if it doesn't have one.
*/
NodeInterface * Node::getRightChild() const {
    return(right);
}

Node *&Node::getRight() {
    return(right);
}

Node *&Node::getLeft() {
    return(left);
}

int Node::getHeight() {
    return(height);
}