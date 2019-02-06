//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "BSTree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 38;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};

//--------------------------------------------------------------------

int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum;                          // Record number

	searchID = 0;
	recNum = 0;

    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.
	string temp;
	acctFile >> entry.acctID;
	for(entry.recNum = 0; !acctFile.eof(); entry.recNum++)
	{
		index.insert(entry);
		acctFile >> temp; 
		acctFile >> temp; 
		acctFile >> temp;
		acctFile >> entry.acctID;

	}

    // Output the account IDs in ascending order.
	cout << endl << "Account IDs :" << endl;
	index.writeKeys();
	cout << endl;

    // Clear the status flags for the database file.

    acctFile.clear();

    // Read an account ID from the keyboard and output the
    // corresponding record.

	cout << "Enter account ID: ";
	

	while(cin >> searchID)			//ran into errors with cin.good and !cin.bad for while statement but this seemed to work so stuck to this
	{
		
		if(index.retrieve(searchID,entry)){		//if the ID can be found 
			
			cout << entry.recNum << " : ";
			acctFile.seekg(((bytesPerRecord - 1) * entry.recNum), ios_base::beg);	//go to the recNum of the ID by using seekg
			acctFile >> acctRec.acctID;						//store the data into account record. 
			acctFile >> acctRec.firstName;				
			acctFile >> acctRec.lastName;
			acctFile >> acctRec.balance;
			cout << acctRec.acctID							//start printing the following data to the terminal.
			<< " " << acctRec.firstName 
			<< " " << acctRec.lastName 
			<< " " << acctRec.balance;
			cout << endl;
		}
		else
		{
			cout << "No record with that account ID" << endl;
		}
		cout << "Enter account ID (EOF to quit): ";			
	}

	return 0;
}


