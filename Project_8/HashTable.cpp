/** @file HashTable.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will implement a HashTable using a Binary Search Tree ADT.
@details The specifications of the program are instructed and documented on Lab 10  C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Wednesday, November 8, 2017
*/

/**
@mainpage
This program contains the necessary functions to implement
-a Binary Search Tree ADT using a linked tree structure 

While doing this project I had to keep in mind that I was using the Binary Search Tree to 
create the dataTable of the HashTable. I had to use my Binary Search Tree functions to implement the 
HashTable entirely. 

*/

/*
Author self-assessment statement:
This program is complete and working according to specifications,
according to the best of my knowledge.
*/


//
// Header Files ///////////////////////////////////////////////////
//

#include "HashTable.h"
using namespace std;

//
// Supporting Function Implementations ///////////////////////////////////////////////////
//



/**
 * This function is the param constructor for the HashTable class.
 *
 *This function will set the tableSize of the HashTable equal to the integer parameter passed. 
 *This function will also create a dataTable (array) of Binary Search Trees with the size of
 *tableSize.
 *
 * @param int initTableSize, which is the size of the HashTable 
 * @return This function does not return anything.
 *
 * @pre The Hashtable is empty and was just created or needs to be modified.
 * @post The HashTable will be intialized to be the size of the integer parameter passed.
 *
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
{
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
}


/**
 * This function is the copy constructor for the HashTable class.
 *
 *This function will first call the copyTable function with other passed in as the parameter to 
 *create a copy of the other HashTable.
 *
 * @param const HashTable<DataType, KeyType>& other, which is the other HashTable that is to be copied so that this object is the copy of the other./
 * @return This function does not return anything.
 *
 * @pre none
 * @post This function will create a copy of the parameter of HashTable& other and make the copy to this object.
 *
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable<DataType, KeyType>& other)
{
	copyTable(other);
}


/**
 * This function is the overloaded assignment operator for the HashTable class.
 * 
 *This function will check if the current object is not the other parameter.
 *Then the function will first clear the object.
 *This function will then call the copyTable function with other passed in as the parameter to 
 *create a copy of the other HashTable.
 *
 * @param const HashTable<DataType, KeyType>& other, which is the other HashTable that is to be copied so that this object is the copy of the other./
 * @return This function returns a pointer to this object.
 *
 * @pre none
 * @post This function will create a copy of the parameter of HashTable& other and make the copy to this object.
 *
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType> & HashTable<DataType, KeyType>::operator=(const HashTable<DataType, KeyType>& other)
{
	if(this != &other)	
	{
		clear();
		copyTable(other);
	}
	return *this;

}

/**
 * This function is the destructor for the HashTable class.
 * 
 *This function will call the clear function to clear the data for the current object.
 * Then the function calls the delete operator on dataTable and sets dataTable to NULL.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre A HashTable to be cleared.
 * @post This HashTable will be cleared. dataTable will be set to NULL.
 *
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
	clear();
	delete [] dataTable;
	dataTable = NULL;
}
/**
 * This function is the insert function for the HashTable class, which inserts a new dataItem into the HashTable.
 *
 * This function creates a local variable called index, and sets it to 0.
 * Index is then set to the newDataItem's function called hash with the dataItem's getKey with modulus size of tableSize since we have to recircle back to the index of the table based on the bounds of the size of the HashTable.
 * The function then inserts the newDataItem to the index of HashTable that we calculated.
 *
 * @param const DataType& newDataItem, which is the dataItem passed by reference to be inserted.
 * @return This function does not return anything.
 *
 * @pre A HashTable object to be modified.
 * @post The new DataItem will be inserted into the HashTable based on the index we calculate.
 *
 */
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	int index = 0;
	index = newDataItem.hash(newDataItem.getKey()) % tableSize;
	dataTable[index].insert(newDataItem);

}

/**
 * This function is the remove function for the HashTable class, which removes a deleteKey from the HashTable.
 *
 * This function loops from index 0 to the size of the tableSize. 
 * In this for loop, the function checks to see if the deleteKey is removed from the HashTable.
 * the function does this by looping until the HashTable is able to do this by calling the remove function from the 
 * Binary Search Tree ADT with the deleteKey passed as the parameter. If that statement is true, the function returns
 * true. If that statement is not true and the for loop ends. The function returns false since the Key was never found 
 * or deleted. 
 *
 * @param const KeyType& deleteKey, which is the Key passed by reference to be deleted.
 * @return This function returns true if the KeyType was removed successfully from the HashTable.
 *
 * @pre A HashTable object to be modified.
 * @post The deleteKey of the same value in the HashTable will be deleted.
 *
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	int i = 0;
	for(i = 0; i < tableSize; i++)
	{
		if((dataTable[i].remove(deleteKey)) == true)
		{
			return true;
		}
	}
	return false;
}

/**
 * This function is the retrieve function for the HashTable class, which copies the dataItem to searchDataItem and returns true.
 *
 *This function will loop from index 0 to the size of the tableSize.
 *In this for loop, the function checks to see if the SearchKey is found in the HashTable. 
 *The function does this by checking the binary tree of each index to see if the searchKey is found in there. 
 *It does that by calling the retrieve function from the Binary Search Tree ADT of each index with the parameters 
 *of searchKey and returnItem passed as the parameters. The function checks to see if that process will return true.
 * If it does, the function itself returns true. If the for loop ends and that process is never true, the function will 
 * return false. 
 *
 * @param const KeyType& searchKey, which is the KeyType to be found in the HashTable.
 * @param const DataType& searchDataItem, which holds the copied data of the searchKey if it is found.
 * @return This function does returns true or false, based on if the function dataItem is found.
 *
 * @pre A HashTable object. 
 * @post searchDataItem contains the data of the searchKey if the searchKey was found.
 *
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
	int i = 0;
	for(i = 0; i < tableSize; i++)
	{
		if((dataTable[i].retrieve(searchKey, returnItem)) == true)
		{
			return true;
		}
	}
	return false;
}

/**
 * This function is the clear for the HashTable class.
 * 
 *This function will loop from index 0 to the size of the tableSize. 
 *In this for loop, the function iterates through each index of the HashTable and clears the object in the index. 
 *It does this by calling the clear function for each Binary Search Tree ADT within the index of the HashTable. 
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre An HashTable object.
 * @post HashTable will be cleared through dynamically memory allocation.
 *
 */
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	int i = 0;
	for(i = 0; i < tableSize; i++)
	{
		dataTable[i].clear();
	}
	//delete [] dataTable;
	//dataTable = NULL;
}

/**
 * This function is the isEmpty function for the HashTable class.
 * 
 *This function will loop from index 0 to the size of the tableSize. 
 *In the loop the function checks each index/Binary Search Tree and checks if it is Empty or not. 
 *This does this by calling the isEmpty function for the BST.
 *The function returns false it isn't, otherwise the function returns true if all of it is cleared.
 *
 * @param none
 * @return This function returns true if the HashTable is empty, otherwise it returns false.
 *
 * @pre An HashTable object.
 * @post Returns true if the HashTable is empty, otherwise it returns false.
 *
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const 
{
	for(int i = 0; i < tableSize; i++)
	{
		if(!(dataTable[i].isEmpty()))
		{
			return false;
		}
	}
	return true;
}

/**
 * This function is the showStructure function for the HashTable class
 *
 *The function will iterate through the loop, and print out the indexes of the HashTable.
 *
 * @param none
 * @param 
 * @return This function does not return anything.
 *
 * @pre none
 * @post The contents of the HashTable will be printed.
 *
 */
// show10.cpp: contains implementation of the HashTable showStructure function
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
    for (int i = 0; i < tableSize; ++i) {
		cout << i << ": ";
		dataTable[i].writeKeys();
		//cout << endl;
    }
}

/**
 * This function is the copyTable function of the HashTable class.
 * The function sets tableSize to the source's tableSize.
 * The function then allocates memory to create an array of Binary Search Tree's equal to the tableSize.
 * The function goes from index 0 to the tableSize and copies the data of the source array index to the current index. 
 *
 * @param const HashTable<DataType, KeyType>& source, which is the other HashTable to copy 
 * @return None
 *
 * @pre None
 * @post This HashTable will have the same data as the source HashTable.
*/
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::copyTable(const HashTable<DataType, KeyType>& source)
{
	int i = 0;
	tableSize = source.tableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
	for(i = 0; i < tableSize; i++)
	{
		dataTable[i] = source.dataTable[i];
	}
}



































