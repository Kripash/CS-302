/** @file QueueLinked.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will implement a Queue ADT based on a single linked list representation.
@details The specifications of the program are instructed and documented on Lab 7 Queue ADT of C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Wednesday, September 12, 2017
*/

/**
@mainpage
This program contains the necessary functions to implement
-the single linked list representation of a queue.

When mentioning a queue, we must remember that is has a front and a back,
that way we can address which one is the first element that was added (front)
and which one was the last element that was added (back).
In a queue, the first item to go in will be the first item to come out
which results in  First In First Out (FIFO).

*/

/*
Author self-assessment statement:
This program is complete and working according to specifications,
according to the best of my knowledge.
*/


//
// Header Files ///////////////////////////////////////////////////
//

#include "QueueLinked.h"
using namespace std;

//
// Supporting Function Implementations ///////////////////////////////////////////////////
//

/**
 * This function will set the data and next variable of a QueueNode.
 *
 *This function will be used specifically to initialize a QueueNode so that
 *it will contain the dataItem passed to it and point to the next item in
 *the queue, which will be a memory address.
 *
 * @param nodeData to set in the QueueNode and nextPtr to point to the next QueueNode in the queue.
 * @return This function does not return anything.
 *
 * @pre The QueueNode is empty and was just created or needs to be modified.
 * @post The QueueNode will now contain the data that was passed to it and point to the next item in the queue.
 *
 */
template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}


/**
 * This function is the constructor for the QueueLinked object.
 *
 *This function will be used specifically to initialize a QueueLinked
 *with nothing in it, so the front and back will point to NULL.
 *
 * Other than initialize an empty queue, this function
 * performs no other operations.
 *
 * @param int maxNumber which is used for array implementation but not for linked list.
 * @return This function does not return anything.
 *
 * @pre Nothing
 * @post Creates an empty Queue. Allocates enough memory based on max number for array implementation.
 *
 */
template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumer)
{
	front = NULL;
	back = NULL;

}

/**
 * This function is the copy constructor for the QueueLinked object.
 *
 *This function will be used specifically to initialize a QueueLinked
 *to be the equivalent to the other. This is done so with a deep copy.
 *The function clears the object first and then copies the other object
 *passed.
 *
 * @param QueueLinked& other which will be the object to copy.
 * @return This function does not return anything.
 *
 * @pre Nothing.
 * @post The Queue will be equivalent to the queue that was passed to copy.
 *
 */
template <typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{

	front = NULL;
	back = NULL;
	/*QueueNode * temp = other -> front;
	front = new QueueNode(temp -> dataItem, NULL);
	QueueNode * ptr = front;
	QueueNode * previous = front;
	while(temp -> next != NULL)
	{
		temp = temp -> next;
		ptr = new QueueNode(temp -> dataItem, NULL);
		previous -> next = ptr;
		previous = ptr;
	}
	back = ptr*/
	
	QueueNode* temp = other.front;    
	while(temp->next != NULL)
	{
		enqueue(temp->dataItem);
		temp = temp->next;
	}
	enqueue(temp->dataItem);
}


/**
 * This function is the overloaded assignment operator for the QueueLinked object.
 *
 *This function will be used specifically to initialize a QueueLinked
 *to be the equivalent to the other. This is done so with a deep copy.
 *The function clears the object first and then copies the other object
 *passed.
 *
 * @param QueueLinked& other which will be the object to copy.
 * @return This function returns a reference to the object that was copied.
 *
 * @pre Nothing.
 * @post The Queue will be equivalent to the queue that was passed to copy and then returns a reference to the copied object.
 *
 */
template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
{
	
    if (!(front == other.front) && (other.front != NULL)){
	clear();
	front = NULL;
	back = NULL;

	/*QueueNode * temp = other.front;
	front = new QueueNode(temp -> dataItem, NULL);
	QueueNode * ptr = front;
	QueueNode * previous = front;
	while(temp -> next != NULL)
	{
		temp = temp -> next;
		ptr = new QueueNode(temp -> dataItem, NULL);
		previous -> next = ptr;
		previous = ptr;
	}
	back = ptr;*/

	QueueNode* temp = other.front;    
	while(temp->next != NULL)
	{
		enqueue(temp->dataItem);
		temp = temp->next;
	}
	enqueue(temp->dataItem);
    }

	

	return * this;

}

/**
 * This function is the Destructor for the QueueLinked object.
 * It deallocates all of the memory used to create the queue.
 * It does so by calling the clear function.
 *
 * @return This function does not return anything
 * @pre None
 * @post Deallocates all of the memory used to create the queue.
 */
template <typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
	clear();
}

 /**
 * This function is the enqueue function for the QueueLinked object.
 * It inserts a new node to the back of the queue.If the queue is full,
 * which it never should since it dynamically allocates memory,
 * the function will throw a logic error.
 *
 * @param DataType& Data, which is the dataItem that will be inserted at the back of the queue.
 * @return This function does not return anything.
 * @pre Queue is not full
 * @post Inserts newDataItem at the rear of the queue
 */
template <typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
	if(isFull()){
		throw logic_error("enqueue() queue full");
	}

	if(isEmpty()){
		front = new QueueNode(newDataItem, NULL);
		back = front;
	}
	else if (front == back){
		front -> next = new QueueNode(newDataItem, NULL);
		back = front -> next;
	}
	else{
		back -> next = new QueueNode(newDataItem, NULL);
		back = back -> next;
	}
}

/**
 * This function is the dequeue function for the QueueLinked object.
 * It removes the first item in the queue, and sets the front to be
 * the item after the item that was just deleted.
 * If the queue is empty, the function will throw a logic error.
 *
 * @param None
 * @return This function returns the dataItem that was removed.
 * @pre Queue is not empty.
 * @post The front of the queue is deleted,the front is changed to the next item and the dataItem that was deleted is returned.
 */
template <typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
	if(isEmpty()){
		throw logic_error("dequeue() queue empty");
	}
	DataType data = front -> dataItem;
	if(front == back){
		delete front;
		front = NULL;
		back = NULL;
	}
	else{
		QueueNode * temp = front;
		front = temp -> next;
		delete temp;
		temp = NULL;

	}
	return data;

}

/**
 * This function is the clear function for the QueueLinked object.
 * It deletes all the items in the queue by deallocating them.
 * This is done so by calling the dequeue function until the queue is empty.
 * If the queue is empty, the function will exit.
 *
 * @param None.
 * @return This function does not return anything.
 * @pre None
 * @post Completely clears the list by deallocating the queue by calling the dequeue function.
 */
template <typename DataType>
void QueueLinked<DataType>::clear()
{
	if(isEmpty()){
		return;
	}
	/*else if (front == back){
		delete front;
		front = NULL;
		back = NULL;
	}
	else{
		QueueNode * temp = front;
		while(!isempty()){
		temp = front -> next;
		delete front;
		front = temp;

		}
		back = NULL;
		front = NULL;
	}*/
	else{
		while(!isEmpty()){
			dequeue();
		}
	}
	front = NULL;
	back = NULL;

}

/**
 * This function is the isEmpty check function for the QueueLinked object.
 *
 * @param none.
 * @return This function returns true if Front and back are pointed equal to NULL, else is returns false.
 * @pre none.
 * @post Nothing, either true of false is returned based on if the queue is empty.
 */
template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	if((front == NULL) && (back == NULL)){
		return true;
	}
	else{
		return false;
	}
}

/**
 * This function is the isFull check function for the QueueLinked object.
 *
 * @param none.
 * @return This function always returns false, since the dynamically allocated queue in our case will never be full.
 * @pre none.
 * @post Nothing, the function will always return false.
 */
template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	return false;
}


/** Programming Exercise 2
 * This function is the putFront function for the QueueLinked object.
 * The function will insert a new dataItem to the front of the queue.
 * The remaining items and orders in the queue will not be changed.
 * If the queue is full, which it never should since it dynamically allocates memory,
 * the function will throw a logic error.
 *
 * @param DataType& A new item that is to be added to the front of the queue.
 * @return This function does not return anything.
 * @pre Queue is not full
 * @post newDataItem will be inserted at the front of the queue.
 */
template <typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
	if(isFull()){
		throw logic_error("putFront() queue full");
	}
	else if (isEmpty()){
		enqueue(newDataItem);
	}
	else if (front == back){
		front = new QueueNode(newDataItem, back);
	}
	else{
		QueueNode * temp;
		temp = new QueueNode(newDataItem, front);
		front = temp;

	}
}

/** Programming Exercise 2
 * This function is the getRear function for the QueueLinked object.
 * The function will remove the last item (back) from the queue and
 * return the dataItem that was removed.
 * If the queue is empty,the function will throw a logic error.
 *
 * @param none
 * @return This function returns the dataItem that was removed from the back of the queue.
 * @pre Queue is not empty.
 * @post The last item of the queue is removed, and returns the dataItem of the last item.
 */
template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
	if(isEmpty()){
		throw logic_error("getRear() queue empty");
	}
	DataType data = back -> dataItem;
	if (front == back){
		clear();
	}
	else{
		QueueNode * temp = front;
		while(temp -> next != back){
			temp = temp -> next;
		}
		delete back;
		back = NULL;
		temp -> next = NULL;
		back = temp;
	}
	return data;
}

/** Programming Exercise 3
 * This function is the getLength() function for the QueueLinked object.
 * The function will iterate through the queue until it reaches the last item.
 * return the dataItem that was removed.
 * If the queue is empty,the function will return 0; .
 *
 * @param none
 * @return This function returns the length of the queue as an int.
 * @pre none
 * @post Nothing, Returns the length of the queue.
 */
template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
	QueueNode * temp = front;
	int i = 0;
	if(isEmpty()){
	   return 0;
	}
	else if (front == back){
		return 1;
	}
	else{
		while(temp!=NULL){
			temp = temp -> next;
			i++;
		}
		return i;
	}
}

/**
 * This function is the showStructure function for the QueueLinked object.
 * The function outputs the dataItems of the queue and highlights the front of the queue.
 * If the queue is empty, the function outputs "Empty Queue."
 *
 * @param none
 * @return This function does not return anything.
 * @pre none.
 * @post The dataItems of the queue are printed to the terminal and nothing is changed.
 */
template <typename DataType>
void QueueLinked<DataType>::showStructure () const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
    QueueNode *p;   // Iterates through the queue

    if (isEmpty())
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != 0 ; p = p->next )
	{
	    if( p == front )
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}



