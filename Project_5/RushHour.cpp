/** @file rushhour.cpp
@author Kripash Shrestha, Ethan Park and Kien Duong
@version 2.0
@brief This program will use two classes named Board and Car and use the functions and memebers within the class to solve a Rush hour board. It will go trhough multiple iterations using queues and maps to find the smallest number of moves it takes to complete the board, and then it will output the moves required. 
@details The specifications of the program are on the Rush Hour Problem pdf on Professor Fred Harris's website, there are no specifications other than the outputs must match.
@date Friday, December 8, 2017
*/


/**
@mainpage
This program contains the necessary functions to implement
- Setup() that takes the inputs from the terminal and sets up the board according to the given specifications.
- moveFoward() takes in a car number and moves the car Forward if it is possible. 
- moveBackward() takes in a car number and moves the car Backward if it is possible.
- isSolved() to check if car 0 is at the end of the board. 
- Print() this was used for my own testing purposes to print out the board and its data.
- clear() used to clear the board , essentially the same as setup but used to make sure that the board is reset so the next board can be setup.
- SolveIt() which will be used to try to solve the board if possible.
- boardToString() which will convert our board into a string.



We implemented it with two classes, called Board and Car. The board contains all of the information about the board including the number of cars on the board and the number of current moves taken to solve
the board. To prevent seg faults, We had to keep in mind the boundaries of the board when moving the cars inside the board.  
For my implementation, I created an int board, where 0 marked empty spaces with no cars that other cars could freely move to and (i+1) the car number in which it was entered in the terminal(
so the first car will be 1, second car will be 2 and so on) on the board represented where the space was occupied by a car and another
car could not move there. I used the board to see and decide if the cars could move forward or backward based on its current position.

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
using namespace std;


#include <map>
#include <queue>
#include <string>


//
// Function Prototypes ///////////////////////////////////////////
//

int SolveIt();

//
// Class and Function Declarations ///////////////////////////////////////////////////
//


class Board
{

    public:

		Board(); 
		
		void Setup();
		bool moveForward(int i);
		bool moveBackward(int i);
		bool isSolved();
		//int SolveIt();
		//int LetsSolve();
		void Print();
		void clear();
		string boardToString();

		int numberOfCars;
		int numberOfMoves;
		int BestMoves;
		
	
    private:

		class Car
		{
			public:
			int row;
			int col;
			int length;
			bool vertical;
			bool horizontal;

		};
	
		int board[6][6];
		Car cars[18];
	
};


//
// Main Function Implementation ///////////////////////////////////
//
int main(){

	//set moves to 0
	int moves = 0;
	//set current board to 1
	int current = 1;
	
	while(1){
	
		//calcualte moves by calling SolveIt();
		moves = SolveIt();
		//if moves is -1, that means the board has 0 cards or it wasnt solved, exit main
		if(moves == -1)
		{
			return 0;
		}
		//print out the amount of moves the current scenario requires
		cout << "Scenario " << current << " requires " << moves << " moves\n";
		//increment the current board/scenario
		current++;
		//set moves back to 0 for safety
		moves = 0;
		
	}

	return 0;
}


/**
 * This is the free function SolveIt.
 *
 * 
 * This creates a board based on user setup and solves the board using the least amount of move possible, returning this value to the main function.
 * It uses a queue to iterate through board configurations and a map to check if specific configurations have already been seen.
 * Once the board is set up, it is pushed onto the queue. While the queue is not empty it will continue to find a solution.
 * Once in the while loop it first sets the rushHour board to the first board on the queue, then pops the queue
 * If the board is solved it returns the number of moves to main.
 * Otherwise it begins a for loop that will iterate though every vehical on the board.
 * In the for loop it first checks if the vehical indicated by the index can move forward, moving forward if it can.
 * If it moves forward, it then checks the map to see if the board has been seen before.
 * If not, it increments the number of moves, adds the board to the map, adds the board to the queue, then decrements the number of moves.
 * It then checks if the vehical indicated by the index can move backward, moving backward if it can.
 * If it moves backward, it then checks the map to see if the board has been seen before.
 * If not, it increments the number of moves, adds the board to the map, adds the board to the queue, then decrements the number of moves.
 * The for loop then reapeats.
 * Once the for loop finishes, the while loop loops again.
 *
 * @param NONE
 * @return This function returns an integer which indicates the minimumn number of moves to solve a board. 
 *
 * @pre Function is called to solve a board the user will input. 
 * @post A board is set up and the minimum number of moves to solve the board is found and returned.
 */
int SolveIt()
{
	Board rushHour; 
  	queue <Board> boardQueue;
  	map <string, int> dejavu;
	int to_return = 0;

  	rushHour.Setup();
  	//rushHour.Print();
  	if(rushHour.numberOfCars == 0)
  	{
    	return -1;
  	}

  	//rushHour = this;

  	//put first board onto queue
  	boardQueue.push(rushHour);
  	dejavu.insert(pair<string,int>(rushHour.boardToString(),rushHour.numberOfMoves));
  	while(!boardQueue.empty())
  	{
    	rushHour = boardQueue.front();
    	boardQueue.pop();
    	if(rushHour.isSolved())
    	{
			to_return = rushHour.numberOfMoves;
			rushHour.clear();
    		return to_return;
    	}
    	for(int i=0; i<rushHour.numberOfCars; i++)
    	{
    		if(rushHour.moveForward(i))
      		{
        		if(dejavu.count(rushHour.boardToString()) == 0)
        		{
        			rushHour.numberOfMoves++;
        			dejavu.insert(pair<string,int>(rushHour.boardToString(),rushHour.numberOfMoves));
        			boardQueue.push(rushHour);
        			rushHour.numberOfMoves--;
        		}
        		rushHour.moveBackward(i);
      		}

      		if (rushHour.moveBackward(i))
      		{
        		if(dejavu.count(rushHour.boardToString()) == 0)
        		{
          			rushHour.numberOfMoves++;
          			dejavu.insert(pair<string,int>(rushHour.boardToString(),rushHour.numberOfMoves));
          			boardQueue.push(rushHour);
          			rushHour.numberOfMoves--;
        		}
        		rushHour.moveForward(i);
      		}
    	}  
  	}
	return -1;
}

//
// Supporting Function Implementations ///////////////////////////////////////////////////
//


/**
 * This function  is the default constructor for the Board class. 
 *
 * This function will create a defaulted object of the Board class with a board that is empty, in other terms filled with 0s.The numberOfCars, numberOfMoves and BestMoves variables will be set to 0.
 * The board will be empty and be entirely filled with 0s.
 * The Car class will be intialized with the row being -1, the col being -1, the length being 0, and its orientiation members, vertical and horizontal set to false.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post The Board class will be intialized and the private member Car class will also be initalized within this function.
 *
 */
Board::Board(){


	numberOfCars = 0;
	numberOfMoves = 0;
	BestMoves = 10;
	int car_pointer = 0;
	int i, j = 0;
	
	for (i = 0; i < 6; i++){
		
		for(j = 0; j < 6; j++){
			
			board[i][j] = 0;
		}
	}
	
	for( i = 0; i < 18; i++){
		cars[i].row = -1;
		cars[i].col = -1;
		cars[i].length = 0;
		cars[i].vertical = false;
		cars[i].horizontal = false;
	}
}



/**
 * This function  is the clear function for the Board class. 
 *
 * The function is intended to clear the board so that the next board can be setup properly. This
 * This function will clear the Board class and set the board to empty, in other terms filled with 0s.The numberOfCars, numberOfMoves and BestMoves variables will be set to 0.
 * The board will be empty and be entirely filled with 0s.
 * The Car class will be cleared  with the row being -1, the col being -1, the length being 0, and its orientiation members, vertical and horizontal set to false.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre Usually, it till be a class that is initialized already so that it may be reset.
 * @post The Board class will be cleared, and is identical to the default constructor. 
 *
 */
void Board::clear(){

	numberOfCars = 0;
	numberOfMoves = 0;
	BestMoves = 0;
	int car_pointer = 0;
	int i, j = 0;
	
	for (i = 0; i < 6; i++){
		
		for(j = 0; j < 6; j++){
			
			board[i][j] = 0;
		}
	}
	
	for( i = 0; i < 18; i++){
		cars[i].row = -1;
		cars[i].col = -1;
		cars[i].length = 0;
		cars[i].vertical = false;
		cars[i].horizontal = false;
	}


}

/**
 * This function  is the setup function for the Board class. 
 *
 * This function takes in the input of the terminal and properly arranges the board from the specified inputs. 
 * This function also takes the input of the cars and properly fills the data members of the Car class based on the inputs. 
 * The board will be filled with (i+1) the car number in which it was entered in the terminal(so the first car will be 1, second car will be 2 and so on), where a car exists and 0s where a car 
 * does not exist. We did this so that it was easier to convert the board into strings and see if it was seen before since using all ones would cause confusion with orientation for some cars.
 * The class will contain the numberOfCars in the board. 
 * The Car class will input the size of the cars, its orientation will be set to true and its row and col will be set for its starting position.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre Usually, it till be a class that is initialized already so that it may be properly setup.
 * @post The Board class and Car class will be setup to contain the information that is taken from the terminal as an input.
 */
void Board::Setup(){

	cin >> numberOfCars;
	char test;
	
	int i = 0;
	for ( i = 0; i < numberOfCars; i++){
		cin >> cars[i].length; 
		cin >> test;
		if( test == 'H'){
			cars[i].horizontal = true;
		}
		else if( test == 'V'){
				cars[i].vertical = true;
		}
		cin >> cars[i].row;
		cin >> cars[i].col;
	}
	
	int r;	
	int c;

	i = 0;
	int j = 1;
	for(i = 0; i < numberOfCars; i++){
		for (j = 0; j < cars[i].length; j++){
			 r = cars[i].row;
			 c = cars[i].col;
			 board[r][c] = (i+1);
			 if(cars[i].horizontal == true){
				board[r][c+j] = (i+1);;
			}
			else if (cars[i].vertical == true){
					 board[r+j][c] = (i+1);;

			}	
		}
	}
}

/**
 * This function  is the print function for the Board class. 
 *
 * This function prints the data in the board class and the data of each car in the Car class for debugging and testing purposes.  
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre Usually, it till be a class that is initialized and setup, so i can print out its data. 
 * @post Nothing will change, but the data of the board and cars will be outputted to the terminal.
 */
void Board::Print(){

	int i, j; 
	i = j = 0;
	cout << "\n";
	for (i = 0; i < 6; i++){
		for(j = 0; j < 6; j++){

			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
	
	cout << "\n";

	for( i = 0; i < numberOfCars; i++){
		cout << cars[i].length << "  ";
		if(cars[i].vertical == true){
			cout << "V  ";
		}
		else if (cars[i].horizontal == true){
			cout << "H  ";
		}
		cout << cars[i].row << "  ";
		cout << cars[i].col << "  ";
		
		cout << "\n";
	}
}

/**
 * This function  is the moveBackward function of the Board class.
 *
 * This function takes in a parameter of int i, which determines which car to check for. 
 * This function checks to see if the chosen car can move backwards. If the car can move backwards, the function will adjust the board properly to do so.
 * The function will then return true if it had succeeding in moving backwards.
 * If the function cannot do so, it will return false. 
 * 
 * @param int i , which designates which car to check to move.
 * @return This function returns true if the car can move backwards and if the car cannot move backwards, it will return false.
 *
 * @pre Usually, it till be a class that is initialized and setup so we can test to see if the car can move. 
 * @post The car will be moved backwards 1 slot from its current position. The board will then be updated to represented to show where the cars are. 
 */
bool Board::moveBackward(int i){

	int r = cars[i].row;
	int c = cars[i].col;

	if(cars[i].horizontal == true){
		if (board[r][c + cars[i].length] == 0 && (c + cars[i].length) <= 5 ){
			board[r][c]= 0;
			cars[i].col = c + 1;
			board[r][cars[i].col + cars[i].length - 1] = (i+1);
			return true;
		}
		else{
			return false;
		}
	}
	else if(cars[i].vertical == true){
		if(board[r + cars[i].length][c] == 0 && (r + cars[i].length) <= 5){
		    board[r][c] = 0;
			cars[i].row = r + 1;
			board[cars[i].row + cars[i].length - 1 ][c] = (i+1);
			return true;
		}
		else{
			return false;
		}
	}
	
}

/**
 * This function  is the moveForward function of the Board class.
 *
 * This function takes in a parameter of int i, which determines which car to check for. 
 * This function checks to see if the chosen car can move forward. If the car can move forward, the function will adjust the board properly to do so.
 * The function will then return true if it had succeeding in moving forward.
 * If the function cannot do so, it will return false. 
 * 
 * @param int i , which designates which car to check to move.
 * @return This function returns true if the car can move forward and if the car cannot move forwards, it will return false.
 *
 * @pre Usually, it till be a class that is initialized and setup so we can test to see if the car can move. 
 * @post The car will be moved forwards 1 slot from its current position. The board will then be updated to represented to show where the cars are. 
 */
bool Board::moveForward(int i){

	int r = cars[i].row;
	int c = cars[i].col;
	
	if(cars[i].horizontal == true){
		if (board[r][c-1] == 0 && c != 0){
			cars[i].col = c - 1;
			board[r][cars[i].col] = (i+1);
			board [r][cars[i].col + cars[i].length] = 0;
			 
			return true;
		}
		else{
			return false;
		}
	}
	else if(cars[i].vertical == true){
		if(board[r-1][c] == 0 && r != 0){
			cars[i].row = r - 1;
			board[cars[i].row][c] = (i+1);
			board[cars[i].row + cars[i].length][c] = 0;
			return true;
		}
		else{
			return false;
		}
	}
	
}

/**
 * This function  is the isSolved function of the Board class.
 *
 * This function returns by checking to see if the first car's col + its length is equal to 6. If that is true, it returns true, otherwise it returns false.
 * 
 * @param none.
 * @return This function returns true if the first car's col + its length is equal to 6, else it will return false.
 *
 * @pre Usually, it till be a class that is initialized and setup so we can test to see if the board is solved.
 * @post Nothing will be changed, but it will return true of false to check if the board is solved.
 */
bool Board::isSolved(){

	/*if(cars[0].length == 2)
	{
		return (cars[0].col == 4);
	}
	else if (cars[0].length == 3)
	{
		return (cars[0].col == 3);
	}
	else
	{
		return false;
	}*/

	// the colunm + length of vehicle should be equal to board size if the car is escaped such as 4 + 2 = 6 for car or 3 + 3 = 6 for truck
	return ((cars[0].col + cars[0].length) == 6);	
}

/**
 * This function is the boardToString function of the Board class.
 *
 * 
 * This function creates a string representing the board array in the Board class and returns it.
 * It uses a nested for loop to add each element of the 2d array to the string.
 *
 * @param NONE
 * @return This function returns a string which represents the board array in the Board class. 
 *
 * @pre Function takes the 2d board array in the current class. 
 * @post A 2d board array is converted into a string and returned.
 */
string Board::boardToString()
{
  string s;
  for(int i=0;i<6;i++)
  {
      for(int j=0;j<6;j++)
      {
        s += board[i][j];
      }
  }
  return s;
}

