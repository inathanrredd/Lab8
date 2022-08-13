#pragma once

#include <iostream>
#include "NodeInterface.h"

using namespace std;

class Node : public NodeInterface {

public:
	int data;
    int height;
	Node* left;
	Node* right;


	Node(const int the_data,
         int the_height,
		 Node* left_val = NULL,
		 Node* right_val = NULL) :
		 data(the_data), height(the_height), left(left_val), right(right_val) {
            //cout << "In constructor" << endl;
    }
	~Node() {
	}

	/*
	* Returns the data that is stored in this node
	*
	* @return the data that is stored in this node.
	*/
	int getData() const;

	/*
	* Returns the left child of this node or null if it doesn't have one.
	*
	* @return the left child of this node or null if it doesn't have one.
	*/
	NodeInterface * getLeftChild() const;

	/*
	* Returns the right child of this node or null if it doesn't have one.
	*
	* @return the right child of this node or null if it doesn't have one.
	*/
	NodeInterface * getRightChild() const;
	Node *&getRight();
	Node *&getLeft();

    int getHeight();

};