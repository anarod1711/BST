
/*  BST312.h
 CS 312 Fall 2018

 a simple implementation of a binary search tree

* Student information for project:
*
* On my honor, Analaura Rodriguez, this programming project is my own work
* and I have not provided this code to any other student.
*
* Name:                Analaura Rodriguez
* email address:       rodrigueza934@gmail.com
* UTEID:               ar55665
* Section 5 digit ID:  16185
*
*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template <class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    //Destructor
    ~BST_312();


/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full. New item to be added is UNIQUE.
Postconditions: newItem is in the proper position for a BST.
input: data of unique new node to be added
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOrder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOdrer (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOdrer (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left = NULL;
        TreeNode *right = NULL;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);


};

/*******************************
//Function implementations
********************************/


/*******************************
Default constructor: points the
root to NULL.
Input/Output N/A
********************************/
template <class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}


/*******************************
 Copy constructor

 Function: Copies the argument tree to the newly declared tree
 Input: Already existing tree
 Output: New tree with same elements as input tree.
********************************/
template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root); // Calls another function to do copying
}


/*******************************
 Destructor

 Function: Deletes tree and gives back allocated memory
********************************/
template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty(); // calls other function to delete

}


/*******************************
 copyTree

 Function: Copies an existing tree to the newly declared tree
 Input: newly declared tree and existing tree
 Output: New tree with same elements as existing tree.
********************************/
template<class ItemType>
// Does *& mean passing a pointer by reference??
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;                        // new tree element
        copy->data = originalTree->data;            // copies o.g. data over (node)

        copyTree(copy->left, originalTree->left);   // copies left tree first
        copyTree(copy->right, originalTree->right); // then right tree
    }
}


/*******************************
  deleteNode
  Helper Function to deleteItem

 Function: Deletes a node, while taking into consideration the three cases:
            (1) The node is a leaf (no children)
                - just deletes the node, with no further tree alterations
            (2) The node has one child
                - connects the branch from target node parent to target node child
            (3) The node has two children
                - finds a predecessor (maximum of left sub tree)
                - replaces target node value with predecessor value
                - deletes extra predecessor node
 Input: Pointer to node to be deleted
 Output: none.
********************************/
template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;                  // holds predecessor data
    TreeNode *tempPtr;              // holds node to be deleted

    tempPtr = t;

    if (t->left == NULL)            // case (1) with no LC, and one RC *OR* case(2)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)      // case (1) with no RC and one LC
    {
        t = t->left;
        delete tempPtr;
    }
    else                            // case (3)
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



/*******************************
 getPredecessor

 Function: Finds the maximum node in the left subtree
 Input: pointer to left subtree and variable to store predecessor data
 Output: none
 PostConditions: input variable contains predecessor data
********************************/
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


/*******************************
 Helper Function to deleteItem

 Function: Deletes unique node from tree, if there.
 Input: pointer to tree and data of node to be deleted
 PostConditions: If found, element has been removed from BST.
********************************/
template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)                      // item not found
        return;
    else if (newItem < t->data)         // item in LST
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);  // item in RST
    else
        deleteNode(t);                  // item found, delete using (3) cases
}


/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}



/****************************
Helper Function to makeEmpty

Function: Removes all the items from the BST using PostOrder (L R N)
Preconditions: BST has been initialized
Postconditions: All the items have been removed
input: root of tree
*****************************/
template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    if (t != NULL){
        makeEmpty(t->left);        // delete LST
        makeEmpty(t->right);       // delete RST
        delete t;                  // delete root
    }

}


/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}



/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}


/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    // using exception handlers
    try
    {
        TreeNode *temp = new TreeNode; // tries allocating new memory for tree
        delete temp;
        return false;
    }
    catch (std::bad_alloc) // if allocation fails, full memory, full tree?
    {
        return true;
    }

}


/****************************
Helper Function to insertItem

Function: Adds newItem to the BST where appropriate
Preconditions: BST has been initialized and is not full. New item to be added is UNIQUE.
Postconditions: newItem is in the proper position for a BST.
input: Pointer to node of tree and data of unique new node to be added
*****************************/
template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL){                             // found right place for node

        if (!isFull()) {
            TreeNode *newNode = new TreeNode;
            newNode->data = newItem;
            t = newNode;
        }

    }
    else if (newItem < t->data){                 // goes in LST bc larger than root

        insertItem(t->left, newItem);
    }
    else{                                       // goes in RST bc smaller than root

        insertItem(t->right, newItem);
    }

}


/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full. New item to be added is UNIQUE.
Postconditions: newItem is in the proper position for a BST.
input: data of unique new node to be added
*****************************/
template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    insertItem(root, newItem);      // helper function
}


/****************************
Helper Function to countNodes

Function: calls inOrder to obtain a vector and count the size of tree
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
input: pointer to tree node
ouput: number of nodes in tree
*****************************/
template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    if (t != NULL){
        return(1 + countNodes(t->left) + countNodes(t->right));
    }
    return(0);

}


/****************************
countNodes
countNode

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    return(countNodes(root));


}


/****************************
Helper Function for preOrderTraversal

Function: populates in preOrder (Node, Left, Right) a vector of tree data
Preconditions: BST has been initialized.
Postconditions: none
input: pointer to tree node, and vector to populate
output: by reference, a preOrder populated vector
*****************************/
template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{   // N L R

    if (t != NULL){                             // while node is not empty
        result.push_back(t->data);              // add node data to vector (N)
        preOrderTraversal(t->left, result);     // traverse LST (L)
        preOrderTraversal(t->right, result);    // traverse RST (R)
    }
}


/****************************
preOrderTraversal

Function: Returns the preOrder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    vector<ItemType> result;            // vector to populate
    preOrderTraversal(root, result);
    return(result);

}


/****************************
Helper Function for inOrderTraversal

Function: populates inOrder (Left, Node, Right) a vector of tree data
Preconditions: BST has been initialized.
Postconditions: none
input: pointer to tree node, and vector to populate
output: by reference, an inOrder populated vector
*****************************/
template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{   // L N R
    if (t != NULL){                             // while node is not empty
        inOrderTraversal(t->left, result);      // traverse LST (L)
        result.push_back(t->data);              // add node data to vector (N)
        inOrderTraversal(t->right, result);     // traverse RST(R)
    }
}

/****************************
inOrderTraversal

Function: Returns the inOrder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    vector<ItemType> result;            // vector to populate
    inOrderTraversal(root, result);
    return(result);
}


/****************************
Helper Function for postOrderTraversal

Function: populates postOrder (Left, Right, Node) a vector of tree data
Preconditions: BST has been initialized.
Postconditions: none
input: pointer to tree node, and vector to populate
output: by reference, a postOrder populated vector
*****************************/
template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if (t != NULL){                             // while node is not empty
        postOrderTraversal(t->left, result);    // traverse LST (L)
        postOrderTraversal(t->right, result);   // traverse RST (R)
        result.push_back(t->data);              // add node data to vector (N)
    }

}


/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{   // L R N
    vector<ItemType> result;                // vector to be populated
    postOrderTraversal(root, result);
    return(result);
}


/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
input: item to look for
output: true, if item in tree, false otherwise
*****************************/
template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{

    bool found = false;
    TreeNode* head = root;              // preserve root

    while (!found && (head != NULL)){   // while item not found or node not being null

        if (head->data == item) {       // found item
            found = true;
        }
        else if (head->data > item){    // item in LST because smaller than root
            head = head->left;
        }
        else {                          // item in RST because larger than root
            head = head->right;         // OR just not there, in which case, would
        }                               // reach null at some point
    }

    return(found);                      // found or not

}
#endif

