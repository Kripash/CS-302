//--------------------------------------------------------------------
//
//  Laboratory 11, Programming Exercise 1                     ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include "PriorityQueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int getPriority () const
        { return priority; }     // Returns the priority. Needed by the heap.

    int priority,                // Task's priority
        arrived;                 // Time when task was enqueued

};


//--------------------------------------------------------------------

int main ()
{
    PriorityQueue<TaskData, int, Less<int> > taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals,             // Number of new tasks arriving
        j;                       // Loop counter

    // Seed the random number generator
    srand(7);

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    for ( minute = 0 ; minute < simLength ; minute++ )
    {
        // Dequeue the first task in the queue (if any).
	// Your code here
		if(!taskPQ.isEmpty())						//remove the task at the front of the queue if it is not empty.
		{
			task = taskPQ.dequeue();				//remove the task by calling dequeue
			cout << "At " << minute << " dequeued : " << task.priority << " " << task.arrived << " " << (minute - task.arrived) << endl;	//print out when it was dequeued.
		}
        // Determine the number of new tasks and add them to
        // the queue.
	// Your code here
		int random = rand() % 4;				//generate a random integer between 0 and 3 .
		switch(random)							//switch statement based on the integer generated
		{
			case 1: 							//if 1 is generated, numArrivals is 1.						
					numArrivals = 1;
					break;
			case 2:
					numArrivals = 2;			//if 2 is generated, numArrivals is 2.
					break;
			default:
					numArrivals = 0;			//if it is anything else ( 0 or 3), numArrivals is 0.
					break;
		}
		for(j = 1; j <= numArrivals; j++)		//run the loop based on the amount of arrivals generated.
		{
			task.arrived = minute;						//set the arrived equal to the minute
			task.priority = rand() % numPtyLevels;		//set the priority to be a random number between it and the number of priority levels 
			taskPQ.enqueue(task);						//enqueue the task 
		}

    }	

    return 0;
}

