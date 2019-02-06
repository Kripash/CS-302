/** @file login.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will implement a login simulator using HashTables. 
@details The specifications of the program are instructed and documented on Lab 10  C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Wednesday, November 8, 2017
*/

/**

This program contains the implementation of the HashTable and BinarySearchTree.
This program generates a login simulator with a user and password.


*/


/*
Author self-assessment statement:
This program is complete and working according to specifications,
according to the best of my knowledge.
*/


//
// Header Files ///////////////////////////////////////////////////
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "HashTable.cpp"


//class definitions/edclarations
class TestData {
  public:
    TestData();
    void setKey(const string& newKey);
    string getKey() const;
	void setValue(const string& newValue);
    string getValue() const;
    static unsigned int hash(const string& str);

  private:
	//using key for the user and the value for the password
    string key;
    string value;
    static int count;
};

//
// Supporting Function Implementations ///////////////////////////////////////////////////
//


int TestData::count = 0;


/**
 * This function is the constructor for the TestData class.
 * 
 *This function does nothing.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre nothing.
 * @post nothing.
 *
 */
TestData::TestData(){
}


/**
 * This function is the setKey function for the TestData class.
 * 
 *This function will set the string key equal to newKey.
 *
 * @param const string& newKey, which is the string to be user of the class.
 * @return This function does not return anything.
 *
 * @pre A TestData class.
 * @post Key will now be equal to newKey.
 *
 */
void TestData::setKey(const string& newKey) {
    key = newKey;
}

/**
 * This function is the getKey for the TestData class.
 * 
 *This function returns the key(user) string.
 *
 * @param none
 * @return This function returns the key(user) string.
 *
 * @pre nothing.
 * @post This function returns the key(user) string.
 *
 */
string TestData::getKey() const {
    return key;
}

/**
 * This function is the setValue function for the TestData class.
 * 
 *This function will set the string value equal to newValue.
 *
 * @param const string& newValue, which is the string to be password of the class.
 * @return This function does not return anything.
 *
 * @pre A TestData class.
 * @post Value will now be equal to newValue.
 *
 */
void TestData::setValue(const string& newValue){
	value = newValue;
}


/**
 * This function is the getValue function for the TestData class.
 * 
 *This function returns the Value(password) string.
 *
 * @param none
 * @return This function returns the Value(password) string.
 *
 * @pre nothing.
 * @post This function returns the Value(password) string.
 *
 */
string TestData::getValue() const {
    return value;
}

unsigned int TestData::hash(const string& str) {
    unsigned int val = 0;

    for (int i = 0; i < str.length(); ++i) {
		val += str[i];
    }

    return val;
}



int main()
{


	//delcare and initialize the hashtable for size 8
	HashTable<TestData, string> HTable(8);
	ifstream openFile ("password.dat");
	//TestData class
	TestData TData;
	
	string temp;

	while(openFile >> temp)
	{
		//cout << temp << endl;
		//set the user name after recieved
		TData.setKey(temp);
		//get the password for the user above
		openFile >> temp;
		//cout << temp << endl;
		//set the password for the user above
		TData.setValue(temp);
		//insert the Data into the HashTable
		HTable.insert(TData);
	}
	//show the structure of the HashTable
	HTable.showStructure();
	cout << "Login: ";
	//close the file.
	openFile.close();
	while(cin >> temp)
	{
		//call retrieve into TData
		HTable.retrieve(temp,TData);
		
		cout << "Password: ";
		cin >> temp;
		//if the password can be found, successful
		if((TData.getValue()) == temp)
		{
			cout << "Authentication successful";
		}
		//otherwise failure
		else
		{
			//cout << "temp: " << temp << endl;
			//cout << "Key: " << TData.getValue() << endl;
			cout << "Authentication failure";
		}
		cout << endl << "Login: ";
	}
	//return 0;
}

