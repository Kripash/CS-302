/*Kripash Shrestha
Project 1 is a Single linked list implementation 
CS 302 Data Structures */

#include "ListLinked.h"

using namespace std;

/*This function is the constructor and create an empty list by setting head and cursor to null. 
The parameter is to passed to make sure that it is ignored and a size isnt declared. 
This function does not return anything*/
template <typename DataType>
List<DataType>::List(int ignored){

    head = NULL;
    cursor = NULL;
}

/*This funtion is the copy constructor of the linked list and creates an exact copy of the object that //gets passed through its parameter. 
This function does not return anything*/
template <typename DataType>
List<DataType>::List(const List& other){

    //intially points to the head of the new list but will be used to travel the list.
    ListNode * head_ptr;
    //initially points to the head of the object to copy but will be used to travel the list to copy the items.
    ListNode * other_current = other.head;
    // will initially point to head of the new list but will be used to set the current location's next point to the head_ptr and then be set to head_ptr;
    ListNode * previous;

    if(other.isEmpty()){

        head = NULL;
        cursor = NULL;
    }

    else{

        head = new ListNode(other.head -> dataItem, NULL);
        head_ptr = head;
        previous = head;
        if(other.cursor == other.head){
            cursor = head;
        }

        while((other_current -> next) != NULL){

            other_current = other_current -> next;
            head_ptr = new ListNode(other_current -> dataItem, NULL);
            previous -> next = head_ptr;
            previous = head_ptr;
            if(other.cursor == other_current){
                      cursor = head_ptr;
            }
        }
    }
}

/*  This funtion is an overloaded assignment operator for the object. It will create an exact copy of the object that is passed to its parameter. 
This function is a copy of the copy constructor and in addition will return a reference to the newly created object*/
template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other){

    //intially points to the head of the new list but will be used to travel the list.
    ListNode * head_ptr;
    //initially points to the head of the object to copy but will be used to travel the list to copy the items.
    ListNode * other_current = other.head;
    // will initially point to head of the new list but will be used to set the current location's next point to the head_ptr and then be set to head_ptr;
    ListNode * previous;

    if(other.isEmpty()){

        head = NULL;
        cursor = NULL;
    }

    else{

        head = new ListNode(other.head -> dataItem, NULL);
        head_ptr = head;
        previous = head;
        if(other.cursor == other.head){
            cursor = head;
        }

        while((other_current -> next) != NULL){

            other_current = other_current -> next;
            head_ptr = new ListNode(other_current -> dataItem, NULL);
            previous -> next = head_ptr;
            previous = head_ptr;
            if(other.cursor == other_current){
                      cursor = head_ptr;
            }
        }

    }
    return *this;
}

/*This function is the destructor for the class and will be used to delete objects that have been created.
This function does not return anything.*/
template <typename DataType>
List<DataType>::~List(){

        ListNode * temp;
	//will point to the ListNode that will be deleted.
	temp = head;
	ListNode * holder;
	//Will point to the ListNode that is next in line to be delete until there is nothing left to delete.
	while(temp != NULL){
	     holder = temp -> next;
	     delete temp;
	     temp = holder;
	}
	//set both to NULL just in case the pointers start dangling
	head = NULL;
	cursor = NULL;
}

/*This function is the insert function for the class List. 
This function will insert the parameter newDataItem next to the DataItem where the current cursor is. 
The cursor will then be set the newly added item. This is all assumed that the list is not full (which is never supposed to happen). 
The function does not return anything. 
The function will throw an exception is the list is full and cause the program to terminate.*/
template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error){

    if(isFull()){

        throw(logic_error("insert() full list"));
    }

    //If the List is empty, the inserted item will be the only one and will be the head. The cursor will also point to it. 
    if(isEmpty()){

        head = new ListNode(newDataItem, NULL);
        cursor = head;
    }
    else{

	//This case checks if the cursor is at the end of the list. If it is, it creates a new Node at the end and points the cursor to it.

        if((cursor -> next) == NULL){

            cursor -> next = new ListNode(newDataItem, NULL);
            cursor = cursor -> next;
        }
	//This case is if the cursor is anywhere else in the list.
        else{

            ListNode * temp = cursor -> next;
            cursor -> next = new ListNode(newDataItem, NULL);
            cursor = cursor -> next;
            cursor -> next = temp;
        }
    }
}

/*This function is the remove function for the class List. 
This function will remove the item that is currently marked by the cursor. 
The cursor will then point to the item after the item that was just removed. 
If the item was at the end of the list, the cursor will be moved to the beginning of the list.
The function does not return anything. 
The function will throw an exception is the list is empty and cause the program to terminate.*/
template <typename DataType>
void List<DataType>::remove() throw (logic_error){

    if (isEmpty()){

        throw(logic_error("remove() empty list"));

    }
   
   //case 1 is to check if the removed item will be the head. There will be two cases for it, if it the only NodeList in the list and if there are more NodeLists.
   if( head == cursor){

	if(cursor -> next == NULL){
	    
            delete head;
            head = NULL; 
	    cursor = NULL;
        }       

   	else if( head -> next != NULL ) {
	     
            head = cursor -> next;
	    delete cursor;
	    cursor = head;

   	}
}

    /*This case checks if the cursor is in the middle of the list. If it is, it will point to the previous Node, then delete the Node that the cursor was at. It then sets the current cursor -> next to the 	   temp variable which points to the intital cursor's next. Then it moves the cursor to the Node after the Node that was deleted.*/
    else if (cursor -> next != NULL){
     
	     ListNode * temp; 
	     temp = cursor -> next;
             gotoPrior();
             delete cursor -> next;
             cursor -> next = temp;
             gotoNext();
    }

    /*This case checks if the cursor is at the end of the list. The cursor will be moved to the previous Node and then the new cursor's -> next will be deleted and instead be pointed to NULL. The cursor will 	then point to the beginning of the list*/
    else if (cursor -> next == NULL){

	ListNode * temp = cursor;
	gotoPrior();
	delete temp;
        cursor -> next = NULL;
	gotoBeginning();
    }
	
}


/*This function is the replace function for the class List. 
This function will insert the parameter newDataItem to as the dataItem of where the cursor points to.
The function does not return anything. 
The function will throw an exception is the list is empty and cause the program to terminate.*/
template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error){

    if (isEmpty()){

       throw(logic_error("replace() empty list"));
    }

    else{

        cursor -> dataItem = newDataItem;

    }
}

/*This function is the clear function for the class List. 
The function will remove all the data items in the list.
 However, each item must be deallocated since they were added through dynamic memory allocation.
 The function does not return anything. 
*/
template <typename DataType>
void List<DataType>::clear(){

    while (!isEmpty()){
	remove();
    }

}

/*This function is the isEmpty function for the class List. 
This function checks if the List is empty or not. 
The function checks to see if the head is pointed to NULL, if it is, the function returns true, else is returns false.
The function does not return anything. */
template <typename DataType>
bool List<DataType>::isEmpty() const{

    if(head == NULL){

        return true;
    }
    else{

        return false;
    }
}

template <typename DataType>
bool List<DataType>::isFull() const{

    return false;
}

/*This function is the gotoBeginning function for the class List. 
The function will point the cursor of the List to the head of the List. 
The function will throw an exception is the list is empty and cause the program to terminate.
The function does not return anything. */
template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error){

    if(isEmpty()){

        throw(logic_error("gotoBeginning() empty list"));
    }
    else{

        cursor = head;
    }
}

/*This function is the gotoEnd function for the class List. 
The function will point the cursor of the end of the list. 
The function does this by using a while statement, with the gotoNext() function. Since the gotoNext function returns a booltype, I can keep using it until it returns false, which is when the item can no longer traverse the list, and that occurs when it is at the end of the list.
The function will throw an exception is the list is empty and cause the program to terminate.
The function does not return anything. */
template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error){

    if(isEmpty()){

        throw(logic_error("gotoEnd() empty list"));
    }
    else{

        while(gotoNext()){

        }
    }
}

/*This function is the gotoNext function for the class List. 
The function will point the cursor of the List to the next Node in the List.  
If the cursor is at the end of the list, the function will do nothing and return false. If the cursor is anywhere else, it will move to the current cursor's next member.
The function will throw an exception is the list is empty and cause the program to terminate.
The function will return true if it sucessfully marks the next data, else it will return false. */
template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error){

    if(isEmpty()){

        throw(logic_error("gotoNext() empty list"));
    }

    else if((cursor -> next) == NULL){

        return false;
    }
    else{

        cursor = cursor -> next;
        return true;
    }
}

/*This function is the gotoPrior function for the class List. 
The function will point the Node that is before the current cursor. This function has multiple cases.
The function will throw an exception is the list is empty and cause the program to terminate.
The function will return true if it sucessfully marks the previouss data, else it will return false. */
template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error){

    ListNode * temp;

    if(isEmpty()){
	
        throw(logic_error("gotoPrior() empty list"));
    }

    //If the cursor is at the head, the function will do nothing and return false.
    else if(cursor == head){

        return false;
    }
    //this makes sure that the cursor is not at the head.
    else{
	
        temp = head;
	//sets the temp to the head. and uses a while loop to keep going till the pointer is right before the cursor. 
        while((temp -> next) != cursor){

            temp = temp -> next;
        }
	//then sets the cursor to the item that is pointed by the temporary pointer. and returns true.
        cursor = temp;
        return true;
    }
}

/*This function is the getCursor function for the class List. 
The function will return the dataItem that the curent cursor points to.
The function will throw an exception is the list is empty and cause the program to terminate.
The function does not return anything. */
template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error) {

    if(isEmpty()){

        throw(logic_error("getCursor() empty list"));
    }
    else{

        return cursor -> dataItem;
    }

}


template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    }
    else
    {
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
	    if (temp == cursor) {
		cout << "[";
	    }

	    // Assumes that dataItem can be printed via << because
	    // is is either primitive or operator<< is overloaded.
	    cout << temp->dataItem;

	    if (temp == cursor) {
		cout << "]";
		cout << cursor -> next << endl;
	    }
	    cout << " ";
	}
	cout << endl;
    }
	cout << head << endl;
	cout << cursor << endl;
	

}

/*This function is the movetoBeginning function for the class List. 
The function takes the item markbed by the cursor and reinserts it to the beginning of the list and then moves the cursor to the beginning.
The function will return and do nothing is the cursor is at the head. Since it is already at the beginning of the list,nothing needs to be implemented.
The function will throw an exception is the list is empty and cause the program to terminate.
The function does not return anything.*/
template <typename DataType>
void List<DataType>::moveToBeginning() throw (logic_error){

    ListNode * temp;

    if(isEmpty()){

        throw(logic_error("movetoBeginning() empty list"));
    }
    else if( cursor == head){

        return;
    }
    else{
	 //sets the temporary variable to to the cursor.
         temp = cursor;
	 //moves the cursor to the Node before the cursor.
         gotoPrior();
	 //sets the cursor's next to the next of the temporary variable. The temporary variaqble is where the original cursor was.  
         cursor -> next = temp -> next;
	 //sets the temporary variable next to the current head.
         temp -> next = head;
	 //sets the head to the temporary variable.
         head = temp;
	 //points the cursor to the current head, which was the item that was initially marked by the cursor. 
         cursor = head;
    }
}

/*This function is the insertBefore function for the class List. 
The function inserts the new DataItem to the place right before the cursor.
If the list is empty, the function will create a new Node and set that as the head and the cursor.
The function will throw an exception is the list is full and cause the program to terminate.
The function does not return anything.*/
template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error){


  if(isFull()){

	throw(logic_error("insertBefore() full list"));
    }

    if(isEmpty()){
     
        head = new ListNode(newDataItem, NULL);
        cursor = head;
    }

    else{ 
 	 // if the cursor is the head, it will create a new node and set that as the head. The new head's next will point to the cursor and then the cursor will be set to the new head.
	if ( cursor == head ){

        head = new ListNode(newDataItem, NULL);
        head -> next = cursor;
        cursor = head;
        }
	//if it isnt, the cursor will be moved to the previous Node and then it will insert, with the help of gotoPrior and insert functions created.
    	else{

        gotoPrior();
        insert(newDataItem);
    	}
    }
}

/*This function is the constructor for the class ListNode. 
This function takes in two parameters, of DataType and ListNode *. The function sets the dataItem of the List class as the nodeData passed in to the function and sets the next pointer as the nextPtr passed in the parameters.
The function does not return anything.*/
template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode * nextPtr){

    dataItem = nodeData;
    next = nextPtr;
}


