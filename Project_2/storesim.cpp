//--------------------------------------------------------------------
//
//  Laboratory 7, Programming Exercise 1                   storesim.cs
//
//  Program implementation shell.
//
//--------------------------------------------------------------------

// Simulates the flow of customers through a line in a store.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "config.h"

// Use which ever implementation is currently configured.
#if LAB7_TEST1
#   include "QueueLinked.cpp"
#else
#   include "QueueArray.cpp"
#endif

using namespace std;

int main ()
{
#if LAB7_TEST1
    QueueLinked<int> custQ;      // Line (queue) of customers containing the
#else
    QueueArray<int> custQ;       // Line (queue) of customers containing the
#endif 				 //   time that each customer arrived and
                                 //   joined the line
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        timeArrived,             // Time dequeued customer arrived
        waitTime,                // How long dequeued customer waited
        totalServed = 0,         // Total customers served
        totalWait   = 0,         // Total waiting time
        maxWait     = 0,         // Longest wait
        numArrivals = 0;         // Number of new arrivals

    // Seed the random number generator. Equally instructive to run the
    // simulation with the generator seeded and not seeded.
    srand(7);

    cout << endl << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    // Put your code here to run this simulation. Use "rand()" to get
    // a pseudorandom number that you can use to calculate probabilities.
	int k = 0; //used to generated random number from 0-3. 
	int i = 0; 
	for(minute = 0; minute < simLength; minute++){

		if(!custQ.isEmpty()){
			timeArrived = custQ.dequeue();	//time arrived is equal to when the customer is dequeued. 
			waitTime = minute - timeArrived;  //wait time is now total time - when it was dequeued. 
			totalWait = totalWait + waitTime;  //total wait set to increment so its the entire time. 
			if(waitTime > maxWait){	
				maxWait = waitTime;	  //maxwait is equal to waitTime if it was smaller before.
			}
			totalServed++;
		}
		//switch statement used for the number of customers enqueued. 
		k = rand () % 4;
		switch(k){
			case 1:
				numArrivals = 1;
				break;
			case 2:
				numArrivals = 2;
				break;
			default:
				numArrivals = 0;
		}
		//enqueues the customers with the time. 
		for(i = 0; i < numArrivals; i++){
			custQ.enqueue(minute);
		}

	}

    // Print out simulation results
    cout << endl;
    cout << "Customers served : " << totalServed << endl;
    cout << "Average wait     : " << setprecision(2)
         << double(totalWait)/totalServed << endl;
    cout << "Longest wait     : " << maxWait << endl;

    return 0;
}
