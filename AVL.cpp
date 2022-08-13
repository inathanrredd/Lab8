#include <iostream>
#include "AVL.h"

//Please note that the class that implements this interface must be made
//of objects which implement the NodeInterface

/*
* Returns the root node for this tree
*
* @return the root node for this tree.
*/
NodeInterface * AVL::getRootNode() const {
    return this->root;
}

/*
* Attempts to add the given int to the BST tree
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool AVL::add(int data) {
    cout << "Function Adding " << data << endl;
    return insert(data, this->root);
}

bool AVL::insert(int data, Node *&node) {
    if (node==NULL) {
        node = new Node(data,1);
        return true;
    }
    else if (node->getData() == data) {
        return false;
    }
    else if (data > node->getData()) {
        bool is_added = insert(data,node->getRight());
        if (is_added) {
            rebalance(node);
        }
        return is_added;
    }
    else {
        bool is_added = insert(data,node->getLeft());
        if (is_added) {
            rebalance(node);
        }
        return is_added;
    }
}

/*
* Attempts to remove the given int from the BST tree
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool AVL::remove(int data) {
    cout << "Removing " << data << endl;
    return remove(data, this->root);
}


bool AVL::remove(int data, Node *&node) {
    // cout << "Node->right = " << node->right << endl;
    // cout << "Node->left = " << node->left << endl;

    if (node==NULL) {
        cout << "The integer is not in the tree" << endl;
        return false;
    }
    else if (node->getData() == data) {
        if (node->left == NULL && node->right == NULL) { //it is a leaf node
            //cout << "It is a leaf node" << endl;
            delete node;
            node = NULL;
            return true;
        }
        else if (node->right == NULL) { // it has no right subtree
            //cout << "it has no right subtree" << endl;
            Node *left = node->left;
            delete node;
            node = left;
            return true;
        }
        else if (node->left == NULL) { // it has no left subtree
            //cout << "it has no left subtree" << endl;
            Node *right = node->right;
            delete node;
            node = right;
            return true;
        }
        else {
            cout << "It has subtrees on both sides" << endl;
            node->data = rightmost(node->left);
            rebalance(node);

            return true;
        }
    }
    else if (data > node->getData()) {
        bool is_removed = remove(data, node->getRight());
        if (is_removed) {
            rebalance(node);
        }
        return is_removed;
    }
    else {
        bool is_removed = remove(data, node->getLeft());
        if (is_removed) {
            rebalance(node);
        }
        return is_removed;
    }
}

int AVL::rightmost(Node *&node) {
    if (node->right == NULL) {
        int rightmost = node->getData();
        if (node->left != NULL) {
            Node *left = node->left;
            delete node;
            node = left;
            //rebalance(node);
        }
        else {
            delete node;
            node = NULL;
        }
        return rightmost;
    }
    else {
        int is_rightmost = rightmost(node->right);
        rebalance(node);
        return is_rightmost;
        
    }
}

void AVL::rebalance(Node *&node) {
    cout << "In rebalance for node " << node->getData() << endl;
    int lheight = 0;
    int rheight = 0;
    if (node->getLeft() != NULL) {
        lheight = node->getLeft()->height;
        cout << "lheight for node " << node->getLeft()->getData() << " = " << lheight << endl;
    }
    if (node->getRight() != NULL) {
        rheight = node->getRight()->height;
        cout << "rheight for node " << node->getRight()->getData() << " = " << rheight << endl;
    }
    if (lheight > rheight) {
        node->height = lheight + 1;
    }
    else {
        node->height = rheight + 1;
    }
    
    cout << "nheight = " << node->getHeight() << endl;
    int balance = rheight - lheight;
    cout << "balance = " << balance << endl;
    if (balance == -1 || balance == 0 || balance == 1) {
        return;
    }
    else if (balance < -1) {
        int llheight = 0;
        int lrheight = 0;
        if (node->getLeft()->getLeft() != NULL) {
            llheight = node->getLeft()->getLeft()->getHeight();
            cout << "llheight for node " << node->getLeft()->getLeft()->getData() << " = " << llheight << endl;

        }
        if (node->getLeft()->getRight() != NULL) {
            lrheight = node->getLeft()->getRight()->getHeight();
            cout << "lrheight for node " << node->getLeft()->getRight()->getData() << " = " << lrheight << endl;

        }

        int lbalance = lrheight - llheight;
        cout << "lbalance = " << lbalance << endl;

        if (lbalance <= 0) {
            rotateRight(node);
        }
        else {
            rotateLeft(node->getLeft());
            rotateRight(node);
        }
    }
    else {
        int rlheight = 0;
        int rrheight = 0;
        if (node->getRight()->getLeft() != NULL) {
            rlheight = node->getRight()->getLeft()->getHeight();
            cout << "rlheight for node " << node->getRight()->getLeft()->getData() << " = " << rlheight << endl;

        }
        if (node->getRight()->getRight() != NULL) {
            rrheight = node->getRight()->getRight()->getHeight();
            cout << "rrheight for node " << node->getRight()->getRight()->getData() << " = " << rrheight << endl;

        }
        int rbalance = rrheight - rlheight;

        if (rbalance >= 0) {
            rotateLeft(node);
        }
        else {
            rotateRight(node->getRight());
            rotateLeft(node);
        }
    }


    return;
}

void AVL::rotateRight(Node *&n) {
    cout << "In rotateRight" << endl;
    Node *temp = n;
    n = n->left;
    temp->left = n->right;
    n->right = temp;
    if (root == temp) {
        root = n;
    }
    // delete temp;
    // temp = NULL;

    int lheight = 0;
    int rheight = 0;
    if (n->right->getLeft() != NULL) {
        lheight = n->right->getLeft()->getHeight();
        //cout << "lheight for node " << node->getLeft()->getData() << " = " << lheight << endl;
    }
    if (n->right->getRight() != NULL) {
        rheight = n->right->getRight()->getHeight();
        //cout << "rheight for node " << node->getRight()->getData() << " = " << rheight << endl;
    }
    if (lheight > rheight) {
        n->right->height = lheight + 1;
    }
    else {
        n->right->height = rheight + 1;
    }

    //update node height
    lheight = 0;
    rheight = 0;
    if (n->getLeft() != NULL) {
        lheight = n->getLeft()->getHeight();
        //cout << "lheight for node " << node->getLeft()->getData() << " = " << lheight << endl;
    }
    if (n->getRight() != NULL) {
        rheight = n->getRight()->getHeight();
        //cout << "rheight for node " << node->getRight()->getData() << " = " << rheight << endl;
    }
    if (lheight > rheight) {
        n->height = lheight + 1;
    }
    else {
        n->height = rheight + 1;
    }
    return;
}

void AVL::rotateLeft(Node *&n) {
    cout << "In rotateLeft" << endl;
    Node *temp = n;
    n = n->right;
    temp->right = n->left;
    n->left = temp;
    if (root == temp) {
        root = n;
    }
    // delete temp;
    // temp = NULL;

    int lheight = 0;
    int rheight = 0;
    if (n->left->getLeft() != NULL) {
        lheight = n->left->getLeft()->getHeight();
        //cout << "lheight for node " << node->getLeft()->getData() << " = " << lheight << endl;
    }
    if (n->left->getRight() != NULL) {
        rheight = n->left->getRight()->getHeight();
        //cout << "rheight for node " << node->getRight()->getData() << " = " << rheight << endl;
    }
    if (lheight > rheight) {
        n->left->height = lheight + 1;
    }
    else {
        n->left->height = rheight + 1;
    }

    //update node height
    lheight = 0;
    rheight = 0;
    if (n->getLeft() != NULL) {
        lheight = n->getLeft()->getHeight();
        //cout << "lheight for node " << node->getLeft()->getData() << " = " << lheight << endl;
    }
    if (n->getRight() != NULL) {
        rheight = n->getRight()->getHeight();
        //cout << "rheight for node " << node->getRight()->getData() << " = " << rheight << endl;
    }
    if (lheight > rheight) {
        n->height = lheight + 1;
    }
    else {
        n->height = rheight + 1;
    }
    return;
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear() {
    removeAll(this->root);
}

void AVL::removeAll(Node *&node) {
    if (node == NULL) {
        return;
    }
    if (node->getLeft() != NULL) {
        removeAll(node->getLeft());
    }
    if (node->getRight() != NULL) {
        removeAll(node->getRight());
    }
    if (node != NULL) {
        delete node;
        node = NULL;
    }
}