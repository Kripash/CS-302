/** @file pumpkin.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will take a size of a garden by input and also the containments of the garden and copy it to a 2D array and then calculate the amount of pumpkins patches sizes of pumpking patches per garden. 
@details The specifications of the program are on the It's the Great Pumpkin Patch Problem pdf on Professor Fred Harris's website, there are no specifications other than the outputs must match.
@date Wednesday, September 19, 2017
*/


/**
@mainpage
This program contains the necessary functions to implement
- dynamically allocate a garden of size inputed 
- copy the characters of the garden from the input to the dynamically allocated garden 
- calculate the number of patches in the garden
- calculate the number pumpkins per patches 


The way that i had implemented this was I went through the garden to find the first patch. 
After the first patch was found, I had a check patch function with the row and col of the first pumpkin in the patch. 
Then I can keep counting the patches to the left, right, top and bottomrecursively until the recursion. 
However, i have to keep in mind that, they must only go forward if the array limits are not reached and can only go backwards if it does not go below the array limits.

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

//
// Function Prototypes ///////////////////////////////////////////
//
bool findPatch(int &row, int &col, char ** Patch, int rowS, int colS);
int checkPatches(int row, int col, char ** Patch , int rowS, int colS);
void sort(int size, int array[]); 

//
// Main Function Implementation ///////////////////////////////////
//
int main()
{
     //variable delcaration for the size of the row entered by file.
     int rowSize = 0; 
     //variable delcaration for the size of the col entered by file.
     int colSize = 0;
     //variable declaration used for variables used to iterate loops.
     int i , j;
     // array int declaraction that is used to hold the data of the patch and gardens.
     int data[40][40];
     //variable declaration to intialize amount of gardens to 0.
     int gardenNum= 0;
     //variable declaration for a pointer to the 2D array that will hold the garden.
     char ** garden;

     while(1){


       cin >> rowSize; //input the size of the row.
       cin >> colSize; //input the size of the column.

       if(rowSize == 0 || colSize == 0){
	  break;
       }
       // if either the row or column is set to 0, then the while loop exists. 
      
       //allocates enough memory for the 2D array equal to the row of the input.
       garden =  new char*[rowSize];
       //iterates through to allocated enough memory for the col input of the garden.
       for(i = 0; i < rowSize; ++i){

            garden[i] = new char[colSize];
       }
	
       //iterates to the size of the row and col to take in the input of the garden and assign it to the 2D dynamically allocated char array.
       for(i = 0; i < rowSize; ++i)
       {
           for(j = 0; j < colSize; j++){
		cin >> garden[i][j];
           }
      }
      
      //intializes the current pumpkin in avaialble patch to row 0 and col 0 with a size of 0 and with the pathces set ot 0.
      int rowPatch = 0, colPatch = 0, size = 0;
      int patchNum = 0;
      
      //while loop used to check if a patch has been found. If a patch is found, assigns the row of the pumpkin to rowPatch and the col of the pumpkin to colPatch.
      while(findPatch(rowPatch, colPatch, garden, rowSize, colSize)){
           //increments the number of patches since a patch was found. 
	   patchNum++;
           //calls the checkPatches function, which can recursively call itself to find the size of the patch and then set the variable size to the size of the patch.
	   size = checkPatches(rowPatch, colPatch, garden , rowSize, colSize);	 
           //stores the size of the patch corresponding to the garden number and the patch. 
	   data[gardenNum][patchNum] = size;
           //sets size back to 0 just in case. 
	   size = 0;
      }
      //sets the first element of the garden row equal to the number of patches in the garden. 
      data[gardenNum][0] = patchNum;
      //increments the number of gardens. Was initially set to 0.
      gardenNum++;
      //deallocates the 2D array since it was dynamically allocated to hold the garden. Will be used so that we can copy another garden.
      for(int i = 0; i < rowSize; i++){
	  delete [] garden[i];
      }
      delete [] garden;
    }
      
      int holder = 0;
      //used to print the values of the garden number, the patches and the sizes of the patches in ascending order.
      for(i = 0; i < gardenNum; i++){
	
      cout << "Garden # " << i + 1 <<": " << data[i][0] << " patches, sizes:";
      holder = data[i][0];
      int hold[holder];
      for (j = 0; j < holder; j++){  
           hold[j] = data[i][j+1];
      }
      //calls the sort function to sort the sizes of the patches in ascending order.
      sort(holder, hold);
      for (j = 0; j < holder; j++){    
           cout << " " << hold[j];
      }
      cout << "\n";
      }
	
   return 0;
	
}

//
// Supporting Function Implementations //////////////////////////////
//

/**
 * This function will find the first pumpkin avaialble in an available patch. 
 *
 * The function will iterate through the garden, until it finds the first available pumpkin in an available patch. 
 * If the function finds a pumpkin it will assign, the values of row and col to the location of the pumpkin and then it will return true.
 * If the function does not find anything, it will return false. The function will only iterate through the size of the row and col.
 *
 * 
 * @param int &row assins the value of the row of the pumpkin found to row.
 * @param int &col assins the value of the col of the pumpkin found to col.
 * @param char **Patch is the garden that is taken from the input and will be used to find the patch and pumpkin.
 * @param int rowS is the max available rows in the garden, so the function knows when to stop iterating.
 * @param int colS is the max avaialble cols in the garden, so the function knows when to stop iterating.
 * @return This function returns true if a pumpkin patch is found, if not it will return flase. 
 * 
 * @pre None. 
 * @post The function will locate the first avaialble pumpkin in an avaialble patch and then gives the value of that position to the ints of row and col and then return true or false.
 * 
 */
bool findPatch(int &row, int &col, char ** Patch, int rowS, int colS)
{
	for( int i = 0; i < rowS; i++){
	   for(int j = 0; j < colS; j++){
	      if(Patch[i][j] == 'p'){
		 col = j;
		 row = i;
		 return true;
	      }
	   }
	}

	return false;
}

/**
 * The function will take the array of sizes of the patches and arrange them in ascending order.  
 *
 * The function will check to see if the first element is larger than the next element. If it is, the parition is set to the first element.
 * The function will then swap the data of the array elements. The function will then continue the same way, checking if the current element is larger than the next and then swapping properly if so.
 * 
 * @param int size is the size of the array so the function knows how long and how much it needs to operate. 
 * @param int array [] is the array if integers that contains the sizes of the patches in any order.
 * @return This function does not return anything. 
 * 
 * @pre An array of the sizes of patches in any order. 
 * @post The function will take the array of sizes of the patches and arrange them in ascending order within the array that was passed. 
 * 
 */
void sort(int size, int array[])
{

	int i = 0;
	int partition = 0;
	int j = 0;
	
	for(i = 0; i < (size - 1); i++){
	  for(j = 0; j < (size - i - 1); j++){ 	
	    if(array[j] > array[j+1]){
		partition = array[j];
		array[j] = array[j+1];
		array[j+1] = partition;
	    }
	  }
	}
}

/**
 * This function will set the size to 1 since we assume the find patch is true for the code to  even get to this function.  
 *
 * The function then sets the current pumpkin to 'X' marking it as already ready so the next time we come around, the findPatch function will not read it as the beginning of the new patch.
 * The function then has 4 statements. 
 * The function checks if it can check above the current pumpkin, if it can, the function will check to see if it is a pumpkin, if it is, it calls itself with the location of that pumpkin.
 * The function checks if it can check below the current pumpkin, if it can, the function will check to see if it is a pumpkin, if it is, it calls itself with the location of that pumpkin.
 * The function checks if it can check to the right of the current pumpkin, if it can, the function will check to see if it is a pumpkin, if it is, it calls itself with the location of that pumpkin.
 * The function checks if it can check to the left of the current pumpkin, if it can, the function will check to see if it is a pumpkin, if it is, it calls itself with the location of that pumpkin.
 * The function will make sure that it stays within the bounds of the garden with the values of int rowS and int colS that were passed in at function call.
 *
 * @param int &row assins the value of the row of the pumpkin found to row.
 * @param int &col assins the value of the col of the pumpkin found to col.
 * @param char **Patch is the garden that is taken from the input and will be used to find the pumpkin and the rest of the patch and set the pumpkins in the patch to read.
 * @param int rowS is the max available rows in the garden, so the function knows when to stop iterating.
 * @param int colS is the max avaialble cols in the garden, so the function knows when to stop iterating.
 * @return This function, after going through recursion (if available in 4 directions) , will return the size of the pumpkin patch it went through. 
 * 
 * @pre The function will send in the location of the first pumpkin in an available patch. 
 * @post The function will change all the pumpkins of the patch to 'X' marking them as read and to be skipped next time and then the function will then return the size of the pumpkin patch. 
 * 
 */
int checkPatches(int row, int col, char ** Patch , int rowS, int colS)
{

	int size = 1;
	
	Patch[row][col] = 'X';
	if(row - 1 >= 0){
	   if(Patch[row-1][col] == 'p'){
	      size = size + checkPatches(row - 1, col, Patch, rowS, colS); 
	   }
	}
	if(col - 1 >=0){
	   if(Patch[row][col-1] == 'p'){
	      size = size + checkPatches(row, col - 1, Patch, rowS, colS);
	   }
	}
	if(row + 1 < rowS){
	   if(Patch[row+1][col] == 'p'){
	      size = size + checkPatches(row + 1, col, Patch, rowS, colS); 
	   }
	}
	if(col + 1 < colS){
	   if(Patch[row][col+1] == 'p'){
	      size = size + checkPatches(row, col + 1, Patch, rowS, colS);
	   }
	}
	return size;
}

