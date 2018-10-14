/** @file ExpressionTree.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will implement an Expression Tree ADT using a linked tree structure. 
@details The specifications of the program are instructed and documented on Lab 8 Queue ADT of C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Wednesday, October 11, 2017
*/

/**
@mainpage
This program contains the necessary functions to implement
-the Expression Tree ADT using a linked tree structure. 

While doing this project, I used various helper functions on top of the functions that were already given 
and called them recursively, both indirect and direct. In this project, we will learn about preorder, inorder
and post order traversals to perform and implement the necessary functions needed for the Expression tree 
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

#include "ExpressionTree.h"

#include "iostream" 
using namespace std;


//
// Supporting Function Implementations ///////////////////////////////////////////////////
//


/**
 * This function is the default constructor for the Expr Tree class
 *
 *This function will set the root of the ExprTreeNode Class of the ExprTree Class to NULL.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre The ExprTree is empty and was just created or needs to be modified.
 * @post The ExprTree will not have the ExprTreeNode root set to NULL
 *
 */
template <typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = NULL;
}


/**
 * This function is the insert function for the ExprTree class, which is the helper function for the constructors for me.
 *
 *This function will take in a pointer by reference and a pointer and take the source and modify the current to be the same as the soure.
 *This is done by checking if the source is NULL, if it is, then current is set to NULL.
 *If Source is not NULL, then, we set the current with the ExprTreeNode param constructor with source's dataItem and its left and right set to NULL.
 *I then recursively call the function till there is nothing left to insert, with current -> left, source -> left and current -> right and source -> right passed as the parameters.
 *
 * @param ExprTreeNode *& current, which takes a ExpTreeNode pointer by reference so that it can be modified
 * @param ExprTreeNode *source, which takes a ExprTreeNode pointer so that it can be used to set the other pointer passed to be reference as.
 * @return This function does not return anything.
 *
 * @pre The ExprTreeNode*&current is empty and was just created or needs to be copied from the ExprTreeNode* Source
 * @post The ExprTreeNode*& current will have a copy of the function of ExprTreeNode*source.
 *
 */
template <typename DataType>
void ExprTree<DataType>::insert(ExprTreeNode*& current, ExprTreeNode* source)
{

	if(source != NULL)
	{
		current = new ExprTreeNode(source -> dataItem, NULL, NULL);
		insert(current -> left, source ->left);
		insert(current -> right, source->right);
	}
	else if(source == NULL)
	{
		current = NULL;
	}
}

/**
 * This function is the copy constructor for the ExprTree class.
 *
 *This function will first set the root to NULL and then call the recursive function insert, with the parameters as root of the class and source.root.
 *
 * @param ExprTree &source, which takes a ExprTree by reference so that it can be used to copy the expression tree from the source to this object.
 * @return This function does not return anything.
 *
 * @pre none
 * @post This function will create a copy of the parameter of ExprTree& source and make the copy to this object.
 *
 */
template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
	root = NULL;
	insert(root, source.root);
}

/**
 * This function is the overloaded assignment operator for the ExprTree class.
 * 
 *This function will check if the current object is not the source parameter.
 *The function will first clear the object, and then the root to NULL and then call the recursive function insert, with the parameters as root of the class and source.root.
 *
 * @param Const ExprTree &source, which takes a ExprTree by reference  so that it can be used to copy the expression tree from the source to this object.
 * @return This function does not return anything.
 *
 * @pre An object that is not the same as the object that was passed as the parameter for the copy constructor.
 * @post This function will create a copy of the parameter of ExprTree& source and make the copy to this object.
 *
 */
template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)
{
	if(this!= &source)
	{
		clear();
		root = NULL;
		insert(root, source.root);
	}
	return *this;
}

/**
 * This function is the destructor for the ExprTree class.
 * 
 *This function will call the clear function to dynamically deallocate the memory for the current object.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre An Exprtree object.
 * @post This function will be cleared through dynamically memory allocation.
 *
 */
template <typename DataType>
ExprTree<DataType>::~ExprTree()
{
	clear();
}

/**
 * This function is the build function for the ExprTree class.
 * 
 *This function will call the buildHelper function for to build the ExprTree.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre An ExprTree object that needs to be built.
 * @post This function will build an ExprTree that is inputted to the terminal.
 *
 */
template <typename DataType>
void ExprTree<DataType>::build()
{
	buildHelper(root);

}

/**
 * This function is the buildHelper function for the ExprTree class.
 * 
 *This function will create a location character called temp and cin to the temp.
 *The function will then create a new ExprTreeNode with the parameters of the param constructor as the char temp, NULL and NULL.
 *The function will then check to see if Temp was equal to the operators +,-,* and /.
 *If it is, then the function will recursively call buildHelper function twice with the parameters, as node -> left and node-> right.
 *
 * @param ExprTreeNode*& node, an ExprTreeNode pointer by reference so that it can be modified to build.
 * @return This function does not return anything.
 *
 * @pre An ExprTree object that needs to be built.
 * @post This function will build an ExprTree that is inputted to the terminal. The function will call itself, if the char from the terminal is an operator, since it assums that operations has to be done, and if there isnt then we assume the char is a number and there is no operation left to do.
 *
 */
template <typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode*& node)
{
	char temp;
	cin >> temp;
	node = new ExprTreeNode(temp, NULL, NULL);
	if((temp == '+') || (temp == '-') || (temp == '*') || (temp == '/'))
	{
		buildHelper(node -> left);
		buildHelper(node -> right);
	}
	

}

/**
 * This function is the expression function for the ExprTree class.
 * 
 *This function will check to see if the root of the ExprTree is not NULL.If the ExprTree is not NULL, the function will call the expressionHelper function with the parameter passed as the root.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre An ExprTree that is not empty.
 * @post This function will call the expressionHelper function to print out the expression of the ExprTree.
 *
 */
template <typename DataType>
void ExprTree<DataType>::expression() const
{
	if(root != NULL)
	{
		expressionHelper(root);
	}
}

/**
 * This function is the expressionHelper function for the ExprTree class.
 * 
 *This function will create a local char variable called temp. Temp will be equal to the current -> dataItem.
 *The function then checks, to see if the char contains a number between 0-9. If it is, it the prints out the char.
 *If the char is not a number, then the function prints out the open parantheses first amd then recurssively calls itself twice with the parameters current -> left and then cout the current -> dataItem and t
 *the parameter current -> right and then cout a close parantheses. 
 *
 * @param const ExprTreeNode* current, a ExprTreeNode pointer that is used to start the recursion to print out the expression of the object.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post This function will recursively printout the expression of the ExprTree.
 *
 */
template <typename DataType>
void ExprTree<DataType>::expressionHelper(const ExprTreeNode* current) const
{
	char temp;
	temp = current -> dataItem;
	if (('0' <= temp) && (temp <= '9'))
	{
		cout << temp; 
	}
	else 
	{
		cout << "(";
		expressionHelper(current -> left);
		cout << current ->dataItem;
		expressionHelper(current -> right);
		cout << ")";
	}
}

/**
 * This function is the evaluate function for the ExprTree class.
 * 
 *This function will first check to see if the root of the object is NULL, if it is, we throw a logic error. 
 *If the root is not NULL , then we call the evaluateHelper function with root as the passed parameter.
 *
 * @param none
 * @return This function returns the evaluateHelper function with root as the passed parameter.
 *
 * @pre The object should not be an empty tree.
 * @post This function will recursively evaluate the expression of the ExprTree.
 *
 */
template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
	if(root == NULL)
	{
		throw logic_error ("evaluate() The tree is empty");
	}
	return evaluateHelper(root);

}

/**
 * This function is the evaluateHelper function for the ExprTree class.
 * 
 *This function will create a local char temp which will have current node -> dataItem. The function will then create a DataType holder variable. 
 *The function will switch the char temp to evaluate the expression.If temp is a number between 0 and 9, the function will hold the datatype in the holder and convert it by subtractin '0' from it and then 
 *return the holder variable. If the operator is a '+', the function will call itself with the current -> left + current -> right passed in as parameters to evaluate it.
 *If the operator is a '-', the function will call itself with the current-> left - current -> right passed in as parameters to evaluate it.
 *If the operator is a '*', the function will call itself with the current-> left * current -> right passed in as parameters to evaluate it.
 *If the operator is a '/', the function will call itself with the current-> left / current -> right passed in as parameters to evaluate it.
 *
 * @param const ExprTreeNode* current, which is the current TreeNode that will be observed, such as if it an operator or a number and so on.
 * @return This function returns the evaluated expression based on the case statement that switches the char temp, which is the dataItem of the current parameter. 
 *
 * @pre The object should not be an empty tree.
 * @post This function will recursively evaluate the expression of the ExprTree.
 *
 */
template <typename DataType>
DataType ExprTree<DataType>::evaluateHelper(const ExprTreeNode* current) const
{
	char temp = current -> dataItem;
	DataType holder;
	switch(temp)
	{

		case '+':
				return(evaluateHelper(current -> left) + evaluateHelper(current -> right));
				break;
		case '-': 
				return (evaluateHelper(current -> left) - evaluateHelper(current -> right));	
				break;	
		case '*':
				return (evaluateHelper(current -> left) * evaluateHelper(current -> right));
				break;
		case'/':
				return (evaluateHelper(current -> left) / evaluateHelper(current -> right));
				break;
		default: 
				holder = (current -> dataItem) - '0';
				return holder;
				break;
	}
}

/**
 * This function is the clear function for the Expr Tree class
 *
 *The function checks to see that the root is not NULL, so that it can clear the expression tree.
 *This function will call the clearHelper function with root passed as parameter to dynamically deallocate the expression tree.
 *The function then sets the root equal to NULL, just to double check.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre An expression tree object.
 * @post The ExprTree will be dynamically deallocated and cleared.
 *
 */
template <typename DataType>
void ExprTree<DataType>::clear()
{
	if(root != NULL)
	{
		clearHelper(root);
	}
	root = NULL;
}

/**
 * This function is the clearHelper function for the Expr Tree class
 *
 *The function checks to make sure that the current ExprTreeNode pointer passed by reference's left is not NULL. 
 *If it is not Null, the function will call itself with the parameters of current -> left. 
 *The function repeats the same process for current -> right. 
 *The function will then delete current and then set it to NULL.
 *
 * @param ExprTreeNode*& current, ExprTreeNode pointer passed by reference to modify so that it may be dynamically deleted.
 * @return This function does not return anything.
 *
 * @pre An expression tree object.
 * @post The ExprTree will be dynamically deallocated and cleared and call itself.
 *
 */
template <typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode*& current)
{
		if(current -> left != NULL)
		{
			clearHelper(current -> left);
		}
		else if (current -> right != NULL)
		{
			clearHelper(current -> right);
		}
		delete current;
		current = NULL;
}

/**
 * This function is the commute function for the Expr Tree class
 *
 *The ExprTree will call the commuteHelper function with root passed as the parameter.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre none
 * @post The ExprTree will call the commuteHelper function with root passed as the parameter. This is to commute the oeprands for every arithmetic operating in the expression tree.
 *
 */
template <typename DataType>
void ExprTree<DataType>::commute()
{
	commuteHelper(root);
}

/**
 * This function is the commuteHelper function for the Expr Tree class
 *
 *The ExprTree will first check to see if the passed parameter current is not NULL. If it is not, the function will then declare and initialize 
 *a ExprTreeNode pointer called temp to current -> left. The function will then set current -> left to current -> right. 
 * The function will then set current -> right to temp. The function will then recursively call itself with current -> left and current -> right as the parameters.
 *
 * @param ExprTreeNode*& current, which is the current tree node that the function will go through to commute.
 * @return This function does not return anything.
 *
 * @pre none
 * @post The ExprTree will call the commuteHelper function with root passed as the parameter. This is to commute the oeprands for every arithmetic operating in the expression tree.
 *
 */
template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode*& current)
{
	if(current != NULL)
	{
		ExprTreeNode* temp = current -> left;
		current -> left = current -> right; 
		current -> right = temp;
		commuteHelper(current -> left);
		commuteHelper(current -> right);

	}
}

/**
 * This function is the isEquivalent function for the Expr Tree class
 *
 *The function will check to see if both the root of the current object and the source object are NULL. 
 *If they are, the function will then check to see if they are equal. If they are, the function returns true, other wise it returns false. 
 *The function then checks to see if the current root->dataItem is equal to source.root -> dataItem, and if they are equal the function returns isEquivalentHelper with root and source.root passed as the 
 *parameters. Otherwise the function will return false.
 *
 * @param const ExprTree& source, which is the other tree that the current object will be compared to.
 * @return This function returns either true of false, depending on if the expression tree computations are equal.
 *
 * @pre none
 * @post The ExprTree will call the commuteHelper function with root passed as the parameter. This is to commute the oeprands for every arithmetic operating in the expression tree.
 *
 */
template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
	bool truth;
	if (root == NULL || source.root == NULL)
	{
		if(source.root == root)
		{
			return true;		
		}
		else
		{
			return false;
		}
	}
	else if(root -> dataItem == source.root -> dataItem)
	{
		return isEquivalentHelper(root, source.root);
	}
	return false;
}

/**
 * This function is the isEquivalentHelper function for the Expr Tree class
 *
 *The function first declares and intializes a local char temp variable to current -> dataItem. The function then creates local char variables called left and right. 
 *The function will check to see if the temp is a number between 0 and 9, and then if it is, it makes to sure that the two nodes passed, have the same dataItem and then return true if that is the case and
 * return false if that is not the case. The function assigns left and right to current -> left -> dataItem and current -> right ->dataItem. 
 * The function then checks to see if either left or right is an operator. If so, it goes to make sure that left and right are equal to other -> left -> dataItem and other -> right -> dataItem. 
 * If that is true, then the function will return itself with current -> left, other -> left, current -> right and other-> right passed as parameters. 
 * The function also checks to make sure that the left of the current is equal to the right of the other and vice versa and does the same return call but with, current -> left, other -> right, current ->right
 * and other -> left respectively. 
 * The function then checks to see if temp is either a - or /, since 1-2 and 2-1, and 1/2 and 2/1 are different for example. The property wont apply to the two operator. So the function
 * checks that and returns itself with the left and right data item of current and other to make sure that it is equal. 
 * Otherwise, it does the same check but with two cases, where (current -> left -> dataItem, other -> left -> dataItem, current -> right -> dataItem and other -> right dataItem, are equal) or 
 *(current -> left -> dataItem, other -> right -> dataItem, current -> right -> dataItem and other -> left dataItem, are equal
 *
 * @param ExprTreeNode* current, which is the current node that the function will look at and compare to the other. 
   @param ExprTreeNode* other, which is the other node that the function will compare with to check if they are equal.
 * @return This function returns either true of false, depending on if the expression tree computations are equal.
 *
 * @pre Two ExprTreeNode pointers must be passed so that the entire tree traversal can be compared. 
 * @post The function will go and traverse through the trees of both of Node representatives and check to see if they are equal and return true of false based on that. The function will call itself to check if certain cases are true or false and then return that.
 *
 */
template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(ExprTreeNode* current, ExprTreeNode* other) const
{
	
	char temp = current -> dataItem;
	char left, right;
	if (('0' <= temp) && (temp <= '9'))
	{
		if(current -> dataItem == other -> dataItem)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	left = current -> left -> dataItem;
	right = current -> right -> dataItem;
	if (((left == '+') || (left == '-') || (left == '*') || (left== '/')) || ((right == '+') || (right == '-') || (right == '*') || (right == '/')))
	{
		if((left == other -> left -> dataItem) && (right == other -> right -> dataItem))
		{
			return ((isEquivalentHelper(current -> left, other -> left)) && (isEquivalentHelper(current -> right, other -> right)));
		}
		if((left == other -> right -> dataItem) && (right == other -> left -> dataItem))
		{
			return ((isEquivalentHelper(current -> left, other -> right)) && (isEquivalentHelper(current -> right, other -> left)));
		}
		else
		{
			return false;
		}
	}
	else
	{
		if((temp == '-') || (temp == '/'))
		{
			return ((current -> left -> dataItem == other -> left -> dataItem) && (current -> right -> dataItem == other -> right -> dataItem));
		}
		return (((current -> left -> dataItem == other -> left -> dataItem) && (current -> right -> dataItem == other -> right -> dataItem)) || ((current -> left -> dataItem == other -> right -> dataItem) && (current -> right -> dataItem == other -> left -> dataItem)));
	}
}


/**
 * This function is the showStructure function for the Expr Tree class
 *
 *The function will make sure that the tree is not empty. If it is, the function will print empty tree. Other wise it will call the showHelper function with root, and 1 passed as the parameters.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre none
 * @post The contents of the ExpressionTree will be printed to the terminal in the way that it should be.
 *
 */
template <typename DataType>
void ExprTree<DataType>:: showStructure () const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
    if (root == NULL)
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
 * This function is the showHelper function for the Expr Tree class
 *
 *The function will iterate through the loop, and print out the leaves and branches of the expression tree.
 *
 * @param ExpTreeNode *p, which is the node to start the printing at.
 * @param int level, the level to start the printing of the trees and branches at. 
 * @return This function does not return anything.
 *
 * @pre none
 * @post The contents of the ExpressionTree will be printed to the terminal in the way that it should be.
 *
 */
template <typename DataType>
void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}
/**
 * This function is the ExprTreeNode param constructoror the Expr Tree class
 *
 *This function will initialize the ExprTreeNode to hold a certain dataItem, and point to the left and right of its branch/leaf, depending on if they exist.
 *
 * @param char elem, which will be the dataItem that the node holds. 
 * @param ExprTreeNode *leftPtr, which will be the node's left branch/leaf
 * @param ExprTreeNode *rightPtr, which will be the node's right branch/leaf
 *
 * @return This function does not return anything.
 *
 * @pre none
 * @post modifies the TreeNode to hold a dataitem and point to the left and right based on the parameters passed. 
 *
 */
template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode (char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr)
{
	dataItem = elem;
	left = leftPtr;
	right = rightPtr;
}


