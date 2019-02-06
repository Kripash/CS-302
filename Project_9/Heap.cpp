/** @file Heap.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will implement a HashTable using a Binary Search Tree ADT.
@details The specifications of the program are instructed and documented on Lab 11  C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Wednesday, November 15, 2017
*/

/**
@mainpage
This project contains the following items
-a Heap ADT implemented by using an array representation of a tree
-a Heap which can have dataitems inserted and deleted from it with the proper function to rearrange the heap.
-a writelevels function that outputs the data in a heap in level order, one level per line 
-a inheritance class called Priority queue to develop a simulation of an operating system's task schedule using a priority queue 

*/

/*
Author self-assessment statement:
This program is complete and working according to specifications,
according to the best of my knowledge.
*/


//
// Header Files ///////////////////////////////////////////////////
//



#include "Heap.h"
using namespace std;

//
// Supporting Function Implementations ///////////////////////////////////////////////////
//


/**
 * This function is the param constructor for the Heap class.
 *
 * This function will set the maxSize equal to the parameter maxNumber passed in.
 * This function will set the size to 0 since we are not putting in any data yet.
 * This function will dynamically allocate memory for the array of DataType with maxSize.	
 *
 * @param int maxNumber, which is the largest possible size for the heap.
 * @return This function does not return anything.
 *
 * @pre none
 * @post The heap is empty and was just created.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];

}

/**
 * This function is the copy constructor for the Heap class.
 *
 * This function will set the maxSize equal to the other heap's maxSize.
 * This function will set the size equal to the other heap's size.
 * This function will dynamically allocate memory for the array of DataType with maxSize.
 * This function will iterate a for loop for the maxSize until it copies the data of the other heap's dataItems array into this heap's dataItems array.	
 *
 * @param const Heap& other which is the other object to be copied to make this object
 * @return This function does not return anything.
 *
 * @pre none
 * @post This heap is an exact copy of the other object that was passed in.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)
{
	maxSize = other.maxSize;
	size = other.size;
	dataItems = new DataType[maxSize];
	int i = 0;
	for (i = 0; i < maxSize; i++)
	{
		dataItems[i] = other.dataItems[i];
	}
}

/**
 * This function is the overloaded assignment operator for the Heap class.
 *
 * This function will first check to see that the other object is not the same as this object.
 * This function will then clear the current object.
 * This function will set the maxSize equal to the other heap's maxSize.
 * This function will set the size equal to the other heap's size.
 * This function will dynamically allocate memory for the array of DataType with maxSize.
 * This function will iterate a for loop for the maxSize until it copies the data of the other heap's dataItems array into this heap's dataItems array.	
 *
 * @param const Heap& other which is the other object to be copied to make this object
 * @return This function returns a pointer to this object.
 *
 * @pre none
 * @post This heap is an exact copy of the other object that was passed in.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>&Heap<DataType, KeyType, Comparator>::operator=(const Heap& other) 
{
	if(this != &other)
	{
		clear();
		maxSize = other.maxSize;
		size = other.size;
		dataItems = new DataType[maxSize];
		int i = 0;
		for (i = 0; i < maxSize; i++)
		{
			dataItems[i] = other.dataItems[i];
		}
	}
	return *this;
} 


/**
 * This function is the destructor for the Heap class.
 *
 * This function will call the clear function to clear the dataItems array.
 * This function will call the delete operator on dataItems.
 * This function will set dataItems to NULL.
 *
 * @param  none
 * @return none
 *
 * @pre none
 * @post dataItems will be cleared and deleted and set to NULL.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap()
{
	clear();
	delete [] dataItems;
	dataItems = NULL;
}


/**
 * This function is the parent function for the Heap class.
 *
 * This function will take the child and subtract one from it and then divide 2 from that value.
 * This algorithm can be found in the C++ datastructure course textbook.
 *
 * @param int child which is the child index that we use to find the parent of the child.
 * @return This function will return the parent of the child index that was passed in.
 *
 * @pre  none
 * @post This function will return the parent index from the child index that was passed in.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::Parent(int child) 
{
	return ((child-1)/2);
}

/**
 * This function is the LeftChild function for the Heap class.
 *
 * This function will take the parent and multiply the parent by 2 and add 1.
 * This algorithm can be found in the C++ datastructure course textbook.
 *
 * @param int parent which is used to find the left child of the parent
 * @return This function will return the index of the left child of the parent
 *
 * @pre  none
 * @post This function will return the left child index from the parent index that was passed in.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::LeftChild(int parent) 
{
	return ((2 * parent) + 1);
}


/**
 * This function is the RightChild function for the Heap class.
 *
 * This function will take the parent and multiply the parent by 2 and add 2.
 * This algorithm can be found in the C++ datastructure course textbook.
 *
 * @param int parent which is used to find the right child of the parent
 * @return This function will return the index of the right child of the parent
 *
 * @pre  none
 * @post This function will return the right child index from the parent index that was passed in.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::RightChild(int parent) 
{
	return ((2 * parent) + 2);
}

/**
 * This function is the swap function for the Heap class.
 *
 * This function will take in two indexes and swap the data in them.
 * This function creates a local variable DataType temp and initializes it to be of dataItems[index1];
 * The function assigns the value of that index to be the value of the second index passed.
 * The function then assigns the value of the second index to be the temp variable that was created.
 *
 * @param int index1 which is the first index to be swapped
 * @param int index2 which is the second index to be swapped
 * @return This function does not return anything
 *
 * @pre  none
 * @post This function will swap the values of the two indexes that were passed in as the parameters.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::swap(int index1, int index2)
{
	DataType temp = dataItems[index1];
	dataItems[index1] = dataItems[index2];
	dataItems[index2] = temp;
}

/**
 * This function is the insert function for the Heap class.
 *
 * The function first checks to see if the heap is full, if it is, the function throws a logic error.
 * Otherwise the function creates an index called child that is equal to the size of the array.
 * The Function then inserts the dataItem passed into the child index of the array.
 * The Function then incremenets the size. 
 * The Function runs in a while loop where child is greater than 0 and by calling the comparator function which checks to see if the value of the newDataItem is smaller than the parent
 * of the newly inserted dataItem. If that statement is true, the while loop runs and calls swap with the Parent of the child and child as the parameters. 
 * The function then sets child equal to the Parent of the current index since they were swapped. 
 * The while loop runs until one of the statements is false, which will finish rearranging the heap. 
 *
 * @param const DataType &newDataItem which is the new item to be inserted into the heap
 * @return This function does not return anything
 *
 * @pre  A heap so that items may be inserted into.
 * @post This function will insert the newDataItem and rearrange the heap accordingly.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert(const DataType &newDataItem) throw (logic_error)
{
	if(isFull())
	{ 
		throw logic_error("Full Heap");
	}
	else
	{
		int child = size;
		dataItems[child] = newDataItem;
		size++;
		while (child > 0 && comparator(newDataItem.getPriority(), dataItems[Parent(child)].getPriority()))
		{
			swap(Parent(child),child);	//swap the parent and the child 
			child = Parent(child);		//set the child equal to the new parent, since they were swapped.
		}
	}
}

/**
 * This function is the remove function for the Heap class.
 *
 * The function first checks to see if the heap is empty by calling the isEmpty function, if it iself, the function throws a logic error.
 * Otherwise the function creates a temp DataType that is of index 0 of the dataItems array, which is the DataType to be returned.
 * The function then sets the index 0 of the array to be the last index in the array. The function then sets the parent to be 0, since thats the index since we will rearrange the array.
 * The function will use a while loop to run until the parent is smaller than the size, so that way the function runs until it traverses the array or a return is performed. 
 * The function will then check to see if the RightChild of the parent is smaller than the size. We check the right child first because if a right child exists, then we know for a fact 
 * that a left child must exist so we can compare the values of the left and right child. 
 * The function then does a comparison to check to see if the left child is smaller than the right child, if it is, the function swaps the parent with the right child, and then sets the parent equal to 
 * the right child of the parent since they were swapped. 
 * Otherwise the function does a comparison to check to see if the right child is smaller than the left child, if it is, the function swaps the parent with the left child, and then sets the parent equal to 
 * the left child of the parent since they were swapped. 
 * Other wise the function does a comparison to check to see if the right child is equal to the left child, if it is, the function swaps it with the left child since it wont matter, and then sets the parent 
 * equal to the left child of the parent since they were swapped.
 * If both of those are false, the function just returns temp since
 * The function then check to see if the left child of the parent is smaller than the size of the array. If it is, we just check to see if the the dataItem of the left item is larger than the parent's
 * dataItem and if it is we swap them and set the parent as the new parent left child since they were swapped. 
 * If that isn't true, the function returns temp since there is no right child to compare with since we first checked to see if a right child exists or not.
 *
 * @param none
 * @return This function returns the DataType item that was removed from the heap.
 *
 * @pre  A heap so that the item may be removed from the heap.
 * @post This function removes the max heap of the heap and returns the DataType item that was removed from the heap.
 *h
 */
template <typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator>::remove() throw (logic_error)
{
	if(isEmpty())
	{
		throw logic_error("Empty Heap");
	}
	else
	{
		DataType temp = dataItems[0];
		dataItems[0] = dataItems[--size];
		int parent = 0;

		while(parent < size)
		{
			if(RightChild(parent) <= size) 
			{
				if((dataItems[RightChild(parent)].getPriority()> dataItems[LeftChild(parent)].getPriority()))
				{
					swap(parent,RightChild(parent));
					parent = RightChild(parent);
				}
				else if((dataItems[LeftChild(parent)].getPriority()> dataItems[RightChild(parent)].getPriority()))
				{
					swap(parent, LeftChild(parent));
					parent = LeftChild(parent);
				}
				else if(dataItems[LeftChild(parent)].getPriority() == dataItems[RightChild(parent)].getPriority())
				{
					swap(parent,LeftChild(parent));
					parent = LeftChild(parent);
				}
				else
				{
					return temp;				
				}
			}
			else if(LeftChild(parent) <= size)
			{
				if((dataItems[parent].getPriority() < dataItems[LeftChild(parent)].getPriority()))
				{
					swap(parent,LeftChild(parent));	
					parent = LeftChild(parent);
				}
				else
				{
					return temp;
				}
			}    
			else
			{
				return temp;
			}
		}
	return temp;
	}
}

/**
 * This function is the clear function for the Heap class.
 *
 * This function calls the remove function while the isEmpty function is called. 
 * The function keeps calling the remove functio until the heap is empty.
 *
 * @param none
 * @return This function does not return anything
 *
 * @pre  none
 * @post This function will clear the dataItems array in the heap class and make sure that the size is 0.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::clear()
{

	while(!isEmpty()){
		remove();
	}
	size = 0;

}

/**
 * This function is the isEmpty function for the Heap class.
 *
 * This function checks to see if size is equal to 0. If it is, the function returns true. Otherwise the function returns false.
 *
 * @param none
 * @return This function returns if the heap is empty or not.
 *
 * @pre  none
 * @post This function will return if the heap is empty or not.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
	if(size == 0)
	{
		return true;
	}	
	else
	{
		return false;
	}

}

/**
 * This function is the isFull function for the Heap class.
 *
 * This function checks to see if size is equal to the maxSize. If it is, the function returns true. Otherwise the function returns false.
 *
 * @param none
 * @return This function returns if the heap is full or not.
 *
 * @pre  none
 * @post This function will return if the heap is fullor not.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isFull() const 
{
	if(size == maxSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is the writeLevels function for the Heap class.
 *
 * The function creates two int local variables called curr_Node and level and sets them to 0 and 1 respectively.
 * The function checks to see if the array is empty by calling the isEmpty function and if it is, the function couts "Empty Heap."
 * The function outputs the data items in a heal in level order, one level per line. 
 * The function does this by iterating through the size of the array.
 * The function then sets if the curr_Node is equal to the level, it prints a new line and then multiplies the level by 2 and sets the curr_Node to 0.
 * The function then prints the dataItems in current index and increments curr_Node;
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre  An object to write the levels of the heap.
 * @post This function does not return anything.
 *
 */
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType,KeyType,Comparator>::writeLevels() const
{
	int curr_Node = 0;
	int level = 1;

	if(isEmpty())
	{
		cout << "Empty Heap" << endl;
	}
	else
	{
		for(int i = 0; i < size; i++)
		{
			if(curr_Node == level)
			{
				cout << endl;
				level = level * 2;
				curr_Node = 0;
			}
			cout << dataItems[i].getPriority() << " ";
			curr_Node++;
		} 	
		
		cout << endl;
	}
}


/**
 * This function is the showStructure function for the Heap class
 *
 * Outputs the priorities of the data items in a heap in both array and tree form. If the heap is empty, outputs "Empty heap". This operation is intended for testing/debugging purposes only.
 *
 * @param none
 * @param 
 * @return This function does not return anything.
 *
 * @pre none
 * @post The contents of the Heap will be printed.
 *
 */
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showStructure () const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}


/**
 * This function is the showStructure function for the Heap class
 *
 *The function is the Helper function for the showStructure() function. Outputs the subtree (subheap) whose root is stored in dataItems[index]. Argument level is the level of this dataItems within the tree.
 *
 * @param none
 * @param 
 * @return This function does not return anything.
 *
 * @pre none
 * @post The contents of the Heap will be printed.
 *
 */
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}







