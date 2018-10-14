/** @file PriorityQueue.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will implement a inheritance class called Priority queue to develop a simulation of an operating system's task schedule using a priority queue 
@details The specifications of the program are instructed and documented on Lab 11  C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Wednesday, November 15, 2017
*/


//
// Header Files ///////////////////////////////////////////////////
//


#include "PriorityQueue.h"
using namespace std;

//
// Supporting Function Implementations ///////////////////////////////////////////////////
//



/**
 * This function is the constructor for the PriorityQueue class.
 *
 * This function calls the base class implementation of the heap constructor, with the pass parameter maxNumber as the parameter.
 *
 * @param int maxNumber, which is the largest possible size for the priorityqueue
 * @return This function does not return anything.
 *
 * @pre none
 * @post The priotity queue is empty and has been dynamically allocated to have the maxNumber equal to the size.
 *
 */
template < typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue(int maxNumber):Heap<DataType, KeyType, Comparator>(maxNumber)
{
}

/**
 * This function is the insert function for the PriorityQueue class.
 *
 * This function calls the base class implementation of the insert function, with the passed parameter newdataItem as the parameter.
 *
 * @param const DataType &newDataItem, the dataItem to be inserted.
 * @return This function does not return anything.
 *
 * @pre none
 * @post Inserts a new item into the priorityQueue.
 *
 */
template < typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType, KeyType, Comparator>::enqueue(const DataType &newdataItem)
{
	Heap<DataType, KeyType, Comparator>::insert(newdataItem);
}

/**
 * This function is the dequeue function for the PriorityQueue class.
 *
 * This function calls the base class implementation of the remove function and returns return of the remove function.
 *
 * @param none
 * @return This function returns true or false depending on if the item was dequeued.
 *
 * @pre none
 * @post This function dequeues the top item of the priorityqueue and returns true or false depending on if the item was dequeued.
 *
 */
template < typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue()
{
	return Heap<DataType, KeyType, Comparator>::remove();

}

