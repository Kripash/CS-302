


#include <algorithm>
#include <iostream>
#include <fstream> 
 using namespace std;

 int findTotalPumpkins(char **pPatch);
 bool checkForPatches(char **pPatch, int &row, int &col);
 int findPatchSize(char **pPatch, int row, int col, int from);
 
int patchRows = 0;
int patchCols = 0;
 /********************************************//**
 *  Main method implementation
 ***********************************************/
int main()
{
int count = 1; // Current "Garden" the program is on
while(true) // Program will break when it comes across a row and/or column of 0
{
	/*******************************//**
	*  Get input from the keyboard and create pumpkin patch
	***********************************/
	// Ask user for input
	cin >> patchRows;
	cin >> patchCols;
	/*	Check for valid input
	*	If row or col is 0, end of input - terminate program
	*/
	if(patchRows == 0 || patchCols == 0)
		return 0; 
	char** pumpkinPatch = new char*[patchRows];
	for(int i = 0; i < patchRows; i++)
	{
		pumpkinPatch[i] = new char[patchCols];
	}
	for(int i = 0; i < patchRows; i++)
	{
		for(int j = 0; j < patchCols; j++)
		{
			cin >> pumpkinPatch[i][j];
		}
	}
	// Calculate number of patches and size of patches
	int pRow = -1;
	int pCol = -1;
	int* listOfSizes = new int[(findTotalPumpkins(pumpkinPatch) / 2) + 1]; // There can't possibly be more than ((total # of pumpkins / 2) + 1), by the nature of patches
	int index = 0; // Index of sizes currently on
	while(checkForPatches(pumpkinPatch, pRow, pCol))
	{
		 listOfSizes[index] = findPatchSize(pumpkinPatch, pRow, pCol, 0);
		 index++;
	}
	sort(listOfSizes, listOfSizes + index);
	// Output info about pumpkins
	cout << "Garden # " << count << ": " << index << " patches, sizes:";
	for(int i = 0; i < index; i++)
	{
		cout << " " << listOfSizes[i];
	}
	cout << endl;
	// Clean up
	for(int i = 0; i < patchRows; i++) {
		delete [] pumpkinPatch[i];
	}
	delete [] pumpkinPatch;
	delete [] listOfSizes;
	count++;
}
}

 
int findTotalPumpkins(char **pPatch)
{
	int count = 0;
	for(int i = 0; i < patchRows; i++)
	{
		for(int j = 0; j < patchCols; j++)
		{
			if(pPatch[i][j] == 'p')
			{
				count++;
			}
		}
	}
	
	return count;
}  
  
bool checkForPatches(char **pPatch, int &row, int &col)
{
	for(int i = 0; i < patchRows; i++)
	{
		for(int j = 0; j < patchCols; j++)
		{
			if(pPatch[i][j] == 'p')
			{
				row = i;
				col = j;
				return true;
			}
		}
	}
	
	return false;
}


int findPatchSize(char **pPatch, int row, int col, int from)
{
	int count = 1;
	// Set current pumpkin to 0
	pPatch[row][col] = 0;	
	// Search north - check that row-1 is greater than or equal to 0 (ie, still within bounds of array) and check that we were not just called from the cell to the north (from = 1 = south)
	if((from != 1) && (row - 1 >= 0))
	{
		if(pPatch[row-1][col] == 'p')
		{
			count += findPatchSize(pPatch, row-1, col, 3);
		}
	}
	// Search east - check that col+1 is less than patchCols (ie, still within bounds of array) and check that we were not just called from the cell to the east (from = 2 = west)
	if((from != 2) && (col + 1 < patchCols))
	{
		if(pPatch[row][col+1] == 'p')
		{
			count += findPatchSize(pPatch, row, col+1, 4);
		}
	}
	// Search south - check that row+1 is less than patchRows (ie, still within the bounds of array) and check that we were not just called from the cell to the south (from = 3 = north)
	if((from != 3) && (row + 1 < patchRows))
	{
		if(pPatch[row+1][col] == 'p')
		{
			count += findPatchSize(pPatch, row+1, col, 1);
		}
	}
	// Search west - check that col-1 is greater than or equal to 0 (ie, still within bounds of array) and check that we were not just called from the cell to the west (from = 4 = east)
	if((from != 4) && (col - 1 >= 0))
	{
		if(pPatch[row][col-1] == 'p')
		{
			count += findPatchSize(pPatch, row, col-1, 2);
		}
	}
	
	return count;
}


