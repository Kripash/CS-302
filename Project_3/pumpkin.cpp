#include <iostream> 


using namespace std;

bool findPatch(int &row, int &col, char **Patch);
int checkPatchSize(int row, int col, char **Patch);
void sort(int size, int array[]); 



bool findPatch(int &row, int &col, char **Patch)
{

	int rowFind = 0;
	int colFind = 0;

	while (Patch[rowFind][colFind]!= 'p' && rowFind < row){

		colFind = 0;
		while (Patch[rowFind][colFind]!= 'p' && colFind < col){

			colFind++;
		}
		rowFind++; 
	}

	if(Patch[rowFind][colFind] != 'p'){

	   return false; 
	}

	col = colFind;
	row = rowFind;
	cout << colFind << endl;
	cout << rowFind << endl;
	cout << row << endl;
	cout << col << endl;
	return true;
}

int checkPatchSize(int row, int col, char **Patch)
{

	int size;
	if(Patch[row][col] == 'p'){
	
	   size++;
	   Patch[row][col] = '0';
	   size = size + checkPatchSize(row - 1, col, Patch);
	   size = size + checkPatchSize(row, col - 1, Patch);
	   size = size + checkPatchSize(row + 1, col, Patch);
	   size = size + checkPatchSize(row, col + 1, Patch);

	   return size;
	}
	return 0;
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
  int data[41][41];
  gardenNum = 1; 
  int increment;
  rowSize = -1; colSize = -1;	

  while(rowSize != 0 || colSize != 0){

       cin >> rowSize;
       cin >> colSize;
       
       char** garden =  new char*[rowSize];
       for(i = 0; i < rowSize; ++i){

            garden[i] = new char[colSize];
       }
	

       cout << endl << rowSize << " " << colSize << endl;
       for(i = 0; i < rowSize; ++i)
       {
           for(j = 0; j < colSize; j++){
		cin >> garden[i][j];
           }
            
      }

       cout << "everything good till now" << endl;
       int rowPatch, colPatch, size, patches = 0;
       bool found = true;
       gardenNum = 1;

       while (found == true){

              rowPatch = -1;
              colPatch = -1;
              found = findPatch(rowPatch, colPatch, garden);
              if( found == true ){

                  patches++;
                  size = checkPatchSize(rowPatch, colPatch, garden);
                  data[gardenNum][increment] = size;
                  increment++;
              }
              data[gardenNum][increment] = patches;
              gardenNum++;
       }
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

