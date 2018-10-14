#include <iostream> 


using namespace std;

bool findPatch(int &row, int &col, char Patch[40][40]);
int checkPatches(int row, int col, char Patch[40][40], int rowS, int colS);
void sort(int size, int array[]); 



bool findPatch(int &row, int &col, char Patch[40][40])
{

	for( int i = 0; i < row; i++){
	   for(int j = 0; j < col; j++){
	      if(Patch[i][j] == 'p'){
		 col = j;
		 row = i;
		 return true;
	      }
	   }
	}

	return false;
}

int checkPatches(int row, int col, char Patch[40][40], int rowS, int colS)
{

	int size = 1;
	cout << "test" << endl;
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


int main()
{

  int i, j, rowSize, colSize, gardenNum; 
  char garden [40][40];
  int data[41][41];
  gardenNum = 1; 
  int increment = 1;
  rowSize = -1; colSize = -1;
  	

  while(1){

       cin >> rowSize;
       cin >> colSize;
       if(rowSize != 0 || colSize != 0){
	  break;
       }
       
       /*garden =  new char*[rowSize];
       for(i = 0; i < rowSize; ++i){

            garden[i] = new char[colSize];
       }*/
	
       for(i = 0; i < rowSize; ++i)
       {
           for(j = 0; j < colSize; j++){
		cin >> garden[i][j];
           }
       }

       for( i = 0; i < rowsize; i++){
	   cout << garden[i]
	}

       int rowPatch = 0 , colPatch = 0, size = 0, patches = 0;
       bool found = true;
       gardenNum = 0;
	
       while (findPatch(rowPatch, colPatch, garden)){
	      patches++;  //numbers of patches is now incremented
	      size = checkPatches(rowPatch, colPatch, garden, rowSize, colSize);	//find the current size of the patch	
	      data[gardenNum][increment] = size;     // garden is the garden before program terminates, increment is the  
	      increment++;       		
	}
	data[gardenNum][0] = patches;
	gardenNum++;
        
  }

  int holder = 0;
  for(i = 0; i < gardenNum; i++){

    cout << "Garden # " << i + 1 <<": " << data[i][0] << " patches, sizes: ";
    holder = data[i][0];
    int hold[holder];
    for ( j = 0; j < holder; j++){
    
        hold[j] = data[i][j+1];
    }
    sort(holder, hold);
    for (j = 0; j < holder; j++){
    
        cout << data[j] << " ";
    }
    cout << "\n";

    
  }

   
  return 0;
}

