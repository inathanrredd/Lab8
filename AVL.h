#pragma once

#include "NodeInterface.h"
#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL : public AVLInterface {
public:
	AVL() {
		root = NULL;
    }
	~AVL() {
		clear();
    }

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const;

	/*
	* Attempts to add the given int to the BST tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);


	/*
	* Attempts to remove the given int from the BST tree
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();


private:
	bool insert(int data, Node *&node);
	void removeAll(Node *&node);
	bool remove(int data, Node *&node);
	int rightmost(Node *&node);
    void rebalance(Node *&node);
    void rotateRight(Node *&n);
    void rotateLeft(Node *&n);

protected:
	Node *root;
};