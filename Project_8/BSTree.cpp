/** @file BSTree.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will implement an Binary Search Tree ADT using a linked tree structure. 
@details The specifications of the program are instructed and documented on Lab 9 Binary Search Tree ADT of C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Thursday, October 26, 2017
*/

/**

This program contains the necessary functions to implement
-the Expression Tree ADT using a linked tree structure. 

While doing this project, I used various helper functions on top of the functions that were already given 
and called them recursively, both indirect and direct. In this project, we will learn about preorder, inorder
and post order traversals to perform and implement the necessary functions needed for the binary search tree 
ADT using a linked tree structure.

*/

/*
Author self-assessment statement:
This program is complete and working according to specifications,
according to the best of my knowledge.
*/


//
// Header Files ///////////////////////////////////////////////////
//

#include "BSTree.h"
using namespace std;

//
// Supporting Function Implementations ///////////////////////////////////////////////////
//



/**
 * This function is the BSTreeNode param constructoror the BSTree class
 *
 *This function will initialize the BSTreeNode to hold a certain dataItem, and point to the left and right of its branch/leaf, depending on if they exist.
 *
 * @param const DataType &nodeDataItem, which will be the dataItem that the node holds. 
 * @param BSTreeNode *leftPtr, which will be the node's left branch/leaf
 * @param BSTreeNode *rightPtr, which will be the node's right branch/leaf
 *
 * @return This function does not return anything.
 *
 * @pre none
 * @post modifies the TreeNode to hold a dataitem and point to the left and right based on the parameters passed. 
 *
 */
template <typename DataType, class KeyType> 
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr)
{
	
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;

}


/**
 * This function is the default constructor for the BSTree class
 *
 *This function will set the root of the BSTreeNode Class of the BSTree Class to NULL.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre The BSTree is empty and was just created or needs to be modified.
 * @post The BSTree will not have the BSTreeNode root set to NULL
 *
 */

template <typename DataType, class KeyType> 
BSTree<DataType, KeyType>::BSTree()
{
	root = NULL;
}


/**
 * This function is the copy constructor for the BSTree class.
 *
 *This function will first set the root to NULL and then call the recursive function insert, with the parameters as root of the class and source.root.
 *
 * @param const BSTree <DataType, KeyType> &other, which takes a BSTree by reference so that it can be used to copy the expression tree from the source to this object.
 * @return This function does not return anything.
 *
 * @pre none
 * @post This function will create a copy of the parameter of BSTree& other and make the copy to this object.
 *
 */
template <typename DataType, class KeyType> 
BSTree<DataType, KeyType>::BSTree(const BSTree<DataType, KeyType>& other)
{
	root = NULL;
	copyHelper(root, other.root);
}

/**
 * This function is the overloaded assignment operator for the BSTree class.
 * 
 *This function will check if the current object is not the other parameter.
 *The function will first clear the object, and then call the recursive function insert, with the parameters as root of the class and source.root.
 *
* @param const BSTree <DataType, KeyType> &other, which takes a BSTree by reference so that it can be used to copy the expression tree from the source to this object.
 * @return This function does not return anything.
 *
 * @pre An object that is not the same as the object that was passed as the parameter for the copy constructor to be modified.
 * @post This function will create a copy of the parameter of BSTree& other and make the copy to this object.
 *
 */
template <typename DataType, class KeyType> 
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator=(const BSTree<DataType, KeyType>& other)
{
	if(this != &other)
	{
		clear();
		copyHelper(root, other.root);
	}
	return *this;
}


/**
 * This function is the copyHelper function for the BSTree class, which is the helper function for the constructors for me.
 *
 *This function will take in a pointer by reference and a pointer and take the source and modify the current to be the same as the soure.
 *This is done by checking if the source is NULL, if it is, then return from the function.
 *If Source is not NULL, then, we set the current with the ExprTreeNode param constructor with source's dataItem and its left and right set to NULL.
 *I then recursively call the function till there is nothing left to insert, with dest -> left, src -> left and dest -> right and src -> right passed as the parameters.
 *
 * @param BSTreeNode *& dest, which takes a BSTreeNode pointer by reference so that it can be modified
 * @param BSTreeNode *src, which takes a BSTreeNode pointer so that it can be used to set the other pointer passed to be reference as.
 * @return This function does not return anything.
 *
 * @pre The BSTreeNode*& dest is empty and was just created or needs to be copied from the BSTreeNode* Src
 * @post The BSTreeNode*& dest will have a copy of the function of BSTreeNode*source.
 *
 */
template <typename DataType, class KeyType> 
void BSTree<DataType, KeyType>::copyHelper (BSTreeNode *& dest, BSTreeNode *src)
{
	if( src == NULL)
	{
		return;
	}
	dest = new BSTreeNode (src -> dataItem, NULL, NULL);
	copy_Helper(dest -> left, src -> left);
	copy_Helper(dest -> right, src -> right);
	
}

/**
 * This function is the destructor for the BSTree class.
 * 
 *This function will call the clear function to dynamically deallocate the memory for the current object.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre An Exprtree object.
 * @post This BinaryTree will be cleared through dynamically memory allocation.
 *
 */
template <typename DataType, class KeyType> 
BSTree<DataType, KeyType>::~BSTree()
{
	clear();
}



/**
 * This function is the insert function for the BSTree class, which inserts a new dataItem into the binary search true.
 *
 *This function will call the insertHelper function with root and newDataItem passed as the parameters for the helper function.
 *
 * @param const DataType& newDataItem, which is the dataItem passed by reference to be inserted.
 * @return This function does not return anything.
 *
 * @pre A BSTree object to be modified.
 * @post The new DataItem will be inserted into the tree, if there is a dataItem with that already it replaces it anyways.
 *
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem)
{
	insertHelper(root, newDataItem);
}

/**
 * This function is the insertHelper function for the BSTree class, which is the helper function for the insert function.
 *
 * If the current BSTreeNode current is NULL, the function creates a new node with the dataItem as the parameter and NULL, NULL as the other two, and return.
 * If the DataItem key is smaller than the current dataItem key, the function calls itself with the parameters as current -> left and the dataitem.
 * If the dataItem key is larger than the current dataItem key, the function calls itself with the parameters as current -> right and the dataitem.
 * If the dataItem key is equal to the current dataItem key, the function inserts the newDataItem into current dataItem.
 *
 * @param BSTreeNode *& current, which takes a ExpTreeNode pointer by reference so that it can be modified
 * @param const DataType & newDataItem , dataItem passed by reference to be inserted.
 * @return This function does not return anything.
 *
 * @pre A BSTree object to be modified.
 * @post A modified BSTree with the dataItem inserted into the BSTree.
 *
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode *& current, const DataType & newDataItem)
{
	if(current == NULL)
	{
		current = new BSTreeNode(newDataItem, NULL, NULL);
		return;
	}
	if(newDataItem.getKey() < (current -> dataItem.getKey()))
	{
		insertHelper(current -> left, newDataItem);
	}
	else if(newDataItem.getKey() > (current -> dataItem.getKey())) 
	{
		insertHelper(current -> right, newDataItem);
	}
	else if(newDataItem.getKey() == (current -> dataItem.getKey()))
	{
		current -> dataItem = newDataItem;
	}
}

/**
 * This function is the retrieve function for the BSTree class, which copies the dataItem to searchDataItem and returns true.
 *
 *This function will call the insertHelper function with root and searchDataItem passed as the parameters for the helper function.
 *
 * @param const KeyType& searchKey, which is the KeyType to be found in the BSTree.
 * @param const DataType& searchDataItem, which holds the copied data of the searchKey if it is found.
 * @return This function does returns true or false, based on if the function dataItem is found.
 *
 * @pre A BSTree object. 
 * @post searchDataItem contains the data of the searchKey if the searchKey was found.
 *
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const 
{
	return retrieveHelper(root, searchKey, searchDataItem);
}

/**
 * This function is the retrieveHelper function for the BSTree class, which copies the dataItem to searchDataItem and returns true.
 *
 * If the current BSTreeNode is null, the function returns false. 
 * If the searchKey is smaller than the current dataItem key, the function calls itself with current -> left, searchKey and searchDataItem as the parameters.
 * If the searchKey is larger than the current dataItem key, the function calls itself with current -> right, searchKey and searchDataItem as the parameters.
 * If the searchKey is equal to the current dataItem key, the function sets searchDataItem to the current dataItem and returns true.
 * 
 * @param BSTreeNode * current, which is the current BSTree Node that will be observed to search for the key.
 * @param const KeyType& searchKey, which is the KeyType to be found in the BSTree.
 * @param const DataType& searchDataItem, which holds the copied data of the searchKey if it is found.
 * @return This function does returns true or false, based on if the function dataItem is found.
 *
 * @pre A BSTree object. 
 * @post searchDataItem contains the data of the searchKey if the searchKey was found.
 *
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode * current, const KeyType& searchKey, DataType& searchDataItem) const
{
	if(current == NULL)
	{
		return false;
	}
	if(searchKey < (current -> dataItem.getKey()))
	{
		retrieveHelper(current -> left, searchKey, searchDataItem);
	}
	else if(searchKey > (current -> dataItem.getKey()))
	{
		retrieveHelper(current -> right, searchKey, searchDataItem);
	}
	else if(searchKey == (current -> dataItem.getKey()))
	{
		searchDataItem = current -> dataItem;
		return true;
	}
}


/**
 * This function is the remove function for the BSTree class.
 * 
 *This function will call the removeHelper function with root and the passed parameter deleteKey as the parameters.
 *
 * @param const KeyType &delete key, which is the key to be deleted from the BSTree.
 * @return This function returns true if the deletekey was found and deleted.
 *
 * @pre An Exprtree object.
 * @post This function will delete the key if it is found and return true.
 *
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::remove(const KeyType & deleteKey)
{
	return removeHelper(root,deleteKey);
}

/**
 * This function is the removeHelper function for the BSTree class.
 * 
 * This function will return false if the current BSTreeNode is NULL.
 * If the current dataItem key is smaller than the deleteKey, the function will return itself with current -> right and deleteKey as the passed parameters.
 * If the current dataItem key is larger than the deleteKey, the function will return itself with current -> left and deleteKey as the passed parameters.
 * If the current dataItem key is equal to the delete key, the function will check for the cases to delete the node.
 * 		If the node has no children, the function will delete current, set current to NULL and return true.
 * 		If the node has a left child, the function will set a temp node to equal current, set current to current -> left, delete temp and return true.
 * 		If the node has a right child, the function will set a temp node to equal current, set current to current -> right, delete temp and return true.
 * 		If the node has two children, the function sets the temp node to current -> left. Then in a while loop, the function will traverse the tree for current -> right until it finds the last one.
 * 		The function then sets current -> dataItem to temp -> dataItem and calls itself with current -> left and delete key as the parameters and returns true when it succeeds with the recursion.
 *
 * @param const KeyType &delete key, which is the key to be deleted from the BSTree.
 * @param BSTreeNode *& current, which is the current tree node to be observed or deleted if it is the key.
 * @return This function returns true if the deletekey was found and deleted.
 *
 * @pre An Exprtree object.
 * @post This function will delete the key if it is found and return true.
 *
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode *& current, const KeyType & deleteKey)
{
	if(current == NULL)
	{
		return false;
	}
	if(current -> dataItem.getKey() < deleteKey)
	{
		return removeHelper(current -> right, deleteKey);
	}
	if (current -> dataItem.getKey() > deleteKey)
	{
		return removeHelper(current -> left, deleteKey);
	}
	
	if(current -> dataItem.getKey() == deleteKey){

		if((current -> left == NULL) && (current -> right == NULL))
		{
			delete current;
			current = NULL;
			return true;
		}
		if((current -> left != NULL) && (current -> right == NULL))
		{
			BSTreeNode * temp = current;
			current = current -> left;
			delete temp;
			return true;
		}
		if((current -> left == NULL) && (current -> right != NULL))
		{
			BSTreeNode * temp = current;
			current = current -> right;
			delete temp;
			return true;
		}
		if((current -> left != NULL) && (current -> right != NULL))
		{
			BSTreeNode * temp = current -> left;
			while(temp -> right != NULL)
			{
				temp = temp -> right;
			}
			current -> dataItem = temp -> dataItem;
			removeHelper(current -> left, deleteKey);
			return true;
		}
	}
}

/**
 * This function is the writeKeys function for the BSTree class.
 * 
 *This function will call the writeKeysHelper function with root and the passed parameter if the BSTree is not empty.
 *
 * @param none
 * @return This function returns nothing..
 *
 * @pre An Exprtree object that is not empty.
 * @post This function will output the keys of the dataItem in the binary search tree.
 *
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeys() const 
{
	//if(!isEmpty())
	//{
		writeKeysHelper(root);
		cout << endl;
	//}
}

/**
 * This function is the writeKeysHelper function for the BSTree class.
 * 
 * The function checks to see if the current pointer is not null.
 * If it isnt, the function calls itself with current -> left and prints out itself's item.
 * Then the function calls itself with current -> right.
 *
 * @param const BSTreeNode * current, which is the current tree node to print out the dataItem.
 * @return This function returns nothing..
 *
 * @pre An Exprtree object that is not empty.
 * @post This function will output the keys of the dataItem in the binary search tree.
 *
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeysHelper(const BSTreeNode *current) const 
{
	if(current == NULL)
	{
		return;
	}
	writeKeysHelper(current->left);
	cout << current->dataItem.getKey() << " ";
	writeKeysHelper(current->right);
	
}

/**
 * This function is the clear for the BSTree class.
 * 
 *This function will call the clearHelper function to dynamically deallocate the memory for the current object.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre An Exprtree object.
 * @post The BinaryTree will be cleared through dynamically memory allocation.
 *
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clear()
{
	clearHelper(root);
}

/**
 * This function is the clearHelper for the BSTree class.
 * 
 * If current is not NULL, the function calls itself with current -> left as the parameter and then calls itself against with current -> right as the parameter. 
 * The function then deletes the current node and sets it to NULL.
 *
 * @param BSTreeNode *& current, the current BSTreeNode to be passed so that it could be deleted from the BSTree.
 * @return This function does not return anything.
 *
 * @pre An Exprtree object.
 * @post The BinaryTree will be cleared through dynamically memory allocation.
 *
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode *& current)
{
	if(current != NULL)
	{
		clearHelper(current -> left);
		clearHelper(current -> right);
	}
	delete current;
	current = NULL;
}

/**
 * This function is the isEmpty for the BSTree class.
 * 
 * The function checks to see if the root of the tree is NULL, and if it is NULL, the function returns true. Else the function returns false.
 *
 * @param none
 * @return The function returns true or false based on if the tree is empty or not.
 *
 * @pre An Exprtree object.
 * @post The function returns true or false based on if the tree is empty or not.
 *
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::isEmpty() const
{
	if(root == NULL){
		return true;
	}
	else
	{
		return false;
	}
}


/**
 * This function is the showStructure function for the BSTree class
 *
 *The function will make sure that the tree is not empty. If it is, the function will print empty tree. Other wise it will call the showHelper function with root, and 1 passed as the parameters.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre none
 * @post The contents of the BSTree will be printed to the terminal in the way that it should be.
 *
 */
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


/**
 * This function is the showHelper function for the BSTree class
 *
 *The function will iterate through the loop, and print out the leaves and branches of the Binary search tree.
 *
 * @param BSTreeNode *p, which is the node to start the printing at.
 * @param int level, the level to start the printing of the trees and branches at. 
 * @return This function does not return anything.
 *
 * @pre none
 * @post The contents of the BSTree will be printed to the terminal in the way that it should be.
 *
 */
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p,
                               int level             ) const

// Recursive helper for showStructure. 
// Outputs the subtree whose root node is pointed to by p. 
// Parameter level is the level of this node within the tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}

/**
 * This function is the getHeight for the BSTree class.
 * 
 * The function checks to see if the tree is empty, if it is, the function returns 0, else the function returns getHeightHelper with root passed as the parameter.
 *
 * @param none
 * @return The function returns the height of the tree.
 *
 * @pre A BSTree object.
 * @post The function returns the height of the tree.
 *
 */
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getHeight() const
{
	if(isEmpty())
	{
		return 0;
	}
	else
	{
		return getHeightHelper(root);
	}
}	

/**
 * This function is the getHeightHelper for the BSTree class.
 * 
 * The function creates local int Lheight and Rheight variables and sets them to 0.
 * If the current Node -> left is not NULL, put Lheight += call function with current -> left as the passed parameter.
 * If the current Node -> right is not NULL, put Rheight += call function with current -> right as the passed parameter.
 * If Lheigh is larger than Rheight the function returns Lheight + 1 for the size, which includes the first node. 
 * If Rheight is larger than or equal to Lheight the function returns Rheight + 1 for the size, which includes the first node.
 * Otherwise the function will return one for the root node. 
 *
 * @param const BSTreeNode * current, the current node to look at / observer to find the height of the tree.
 * @return The function returns the height of the tree.
 *
 * @pre A BSTree object.
 * @post The function returns the height of the tree.
 *
 */
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getHeightHelper(const BSTreeNode * current) const
{
	int Lheight = 0; 
	int Rheight = 0;
	if(current -> left != NULL)
	{
		Lheight += getHeightHelper(current -> left);
	}
	if(current -> right != NULL)
	{
		Rheight += getHeightHelper(current -> right);
	}
	if(Lheight > Rheight){
		return Lheight + 1;
	}
	else if (Rheight >= Lheight)
	{
		return Rheight + 1;
	}
	else 
	{
		return 1;
	}
}

/**
 * This function is the getHeight for the BSTree class.
 * 
 * The function checks to see if the tree is empty, if it is, the function returns 0, else the function returns getCountHelper with root passed as the parameter.
 *
 * @param none
 * @return The function returns the number of data items in the tree.
 *
 * @pre A BSTree object.
 * @post The function returns the number of data items in the tree.
 *
 */
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCount() const
{
	if(isEmpty())
	{
		return 0;
	}
	else
	{
		return getCountHelper(root);
	}
}

/**
 * This function is the getCountHelper for the BSTree class.
 * 
 * The function creates local int count that is set to 1, to account for the root node.
 * The function checks to see if current -> left is not NULL, and it if is not the function sets count += recursive function call with current -> left passed as the parameter.
 * The function checks to see if current -> right is not NULL, and it if is not the function sets count += recursive function call with current -> right passed as the parameter.
 * The function always returns count. 
 *
 * @param const BSTreeNode * current, the current node to look at / observer to find the number of data items in the tree.
 * @return The function returns the number of data items in the tree.
 *
 * @pre A BSTree object.
 * @post The function returns the number of data items in the tree.
 *
 */
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCountHelper(const BSTreeNode * current) const
{
	int count = 1;
	if(current -> left != NULL)
	{
		count += getCountHelper(current -> left);
	}
	if(current -> right != NULL)
	{
		count += getCountHelper(current -> right);
	}
	return count;
}

