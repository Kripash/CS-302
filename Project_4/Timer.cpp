/** @file Timer.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will implement a timer to test multiple sort, searches, constructor and increment tests.
@details The specifications of the program are instructed and documented on Lab 13 Performance Evaluation of C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Wednesday, September 26, 2017
*/

/**
@mainpage
This program contains the necessary functions to implement
-the timer to test the multiple sort, search, constructor and increment tests. 

When mentioning a timer, one has to think about the start time and stop time to get the elapsed time. 
Timers have different accuracy and in terms of this one, we will implement one up to microseconds. 
We will have to evaluate the difference in the seconds and the difference in the microseconds measured. 
this can be solved with the structs of timeval of beginTime and duration. 
We will have a timerWasStarted boolean to tell us if the timer was ever started and if it was stopped. 

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
#include "Timer.h"


//
// Supporting Function Implementations //////////////////////////////
//



/**
 * This function will create a timer class using the constructor. This function is the default constructor of the Timer class.
 *
 * This function will be used specifically to initialize a Timer class with all of the private struct values to be set to and the boolean timerWasStarted to false since it was never
 * started.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post The timer class will be intialized to have a beginTime and duration struct with the time for both of their tv_sec and tv_usec members set to 0. The boolean timerWasStarted 	will be set to false since the time is not started. It is just initialized. 
 *
 */
Timer::Timer(){

    beginTime.tv_sec = 0;
    beginTime.tv_usec = 0;
    duration.tv_sec = 0;
    duration.tv_usec = 0;
    timerWasStarted = false;

}


/**
 * This function is the start() function of the Timer class.
 *
 * This function will be used specifically to initialize the timer start for the timer class.
 * The function throws a runtime_error saying the timer was already started since if the timer was already started, there is nothing left to start.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre timerWasStarted should be set to false.
 * @post The timer class will intialize the structure times to start with the use of gettimeofday function given by a given library in the header file. the function will set the    	timerWasStarted variable to true since the timer will now start recording. 
 *
 */
void Timer::start() throw(runtime_error){

    if(timerWasStarted == true){
        throw runtime_error("start() timer already started");
    }

    gettimeofday(&beginTime, NULL);
    timerWasStarted = true;
}


/**
 * This function is the stop() function of the Timer class.
 *
 * This function will be used specifically to stop the time for  the timer class.
 * The function will throw a logic error is timer was never started because there would be nothing to stop if timer was never started.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre timerWasStarted should be set to true. 
 * @post The timer class will stop the timer within the structure by using gettimeofday function again. It will then take the difference of the tv_sec and tv_usec variables from the 	 beginTime structure of the class and the stop structure that was created within this function. The function will take the difference of tv_sec and multiply it by 10^6 and store 	it to the tv_sec member of the duration structure in the timer class. The function also takes the difference of the tv_usec and store it to the tv_usec member of the duration 	structure in the timer class.
 *
 */
void Timer::stop() throw (logic_error){

    if(timerWasStarted == false){
        throw logic_error ("stop() timer was not started.");
    }
    struct timeval stop;
    gettimeofday(&stop, NULL);
    duration.tv_sec = (stop.tv_sec - beginTime.tv_sec) * 1000000;
    duration.tv_usec = (stop.tv_usec - beginTime.tv_usec);
    timerWasStarted = false;
}


/**
 * This function is the getElapsedTime() function for the Timer class.
 *
 * This function takes members of the duration structure and calculates the elapsed time and returns it as a double.
 * This function will throw a logic error if timerWasStarted is set to true because it is then assumed that the timer is still running at that point.
 * 
 * @param none.
 * @return This function returns a double that represents the amount of time that has passed since the timer was stopped and started.
 *
 * @pre timerWasStarted is set to false. 
 * @post The function takes the tv_sec and tv_usec values from the duration structure in the timer class and adds it together and stores it in a local double variable. The function 	then divides the value of the local variable by 10^6. The function will then return the elapsedTime local variable since it stores the value of the time that has passed.
 *
 */
double Timer::getElapsedTime() const throw (logic_error){

    if(timerWasStarted == true){
        throw logic_error ("getElapsedTime() timer is still running.");
    }
    double elapsedTime = duration.tv_sec + duration.tv_usec;
    elapsedTime = elapsedTime / 1000000.0;
    return elapsedTime;
}
