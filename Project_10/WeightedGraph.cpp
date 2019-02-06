/** @file WeightedGraph.cpp
@author Kripash Shrestha
@version 1.2
@brief This program will create an implementation of the Weighted Graph ADT using a vertex list and adjacency matrix. 
@details The specifications of the program are instructed and documented on Lab 12  C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Wednesday, November 27, 2017
*/

/**
@mainpage
This project contains the following items
-create an implementation of the Weighted Graph ADT usin ga vertex list and an adjacency matrix. 
-Develop a routine that finds the shorted path between each pair of vertices in a graph. 
-add vertex coloring and implement a function that checks whether a graph has a proper coloring.
-investiate the four color theorem by generating a graph for which no proper coloring can be creating using less than five colors. 

*/

/*
Author self-assessment statement:
This program is complete and working according to specifications,
according to the best of my knowledge.
*/


//
// Header Files ///////////////////////////////////////////////////
//


#include "WeightedGraph.h" 
using namespace std; 

//
// Supporting Function Implementations ///////////////////////////////////////////////////
//

/**
 * This function is the param constructor for the WeightedGraph class.
 *
 * The function will set the maxSize equal to the parameter maxNumber passed in.
 * The function will set the size to 0 since we are not putting in any data yet.
 * The function will dynamically allocate memory for the vertexList to be equal to the maxSize.
 * The function will dynamically allocate memory for the adjMatrix and pathMatrix equal to the maxSize * maxSize.
 * The function will then loop through the maxSize of the array, acting like a 2D array and turning it into a 1D array
 * for the adjacency matrix, and then set everything to Infinite weight.
 *
 * @param int maxNumber, which is the largest possible size for the WeightedGraph.
 * @return This function does not return anything.
 *
 * @pre none
 * @post The WeightedGraph is empty and was just created.
 *
 */
WeightedGraph::WeightedGraph(int maxNumber)
{
	size = 0;
	maxSize = maxNumber;
	vertexList = new Vertex[maxSize];
	adjMatrix = new int [maxSize * maxSize];
	pathMatrix = new int [maxSize * maxSize];
	for(int i = 0; i < maxSize; i++)
	{
		for(int j = 0; j< maxSize; j++)
		{
			adjMatrix[(i*maxSize) + j] = INFINITE_EDGE_WT; 
		}
	}
}

/**
 * This function is the copy constructor for the WeightedGraph class.
 *
 * The function will set the maxSize equal to the other WeightedGraph's maxSize.
 * The function will set the size equal to the other WeightedGraph's size.
 * The function will dynamically allocate memory for the vertexList to be equal to the maxSize.
 * The function will dynamically allocate memory for the adjMatrix and pathMatrix equal to the maxSize * maxSize.
 * The function will then loop through the maxSize of the array, acting like a 2D array and turning it into a 1D array
 * for the adjacency matrix, and then set copy the data from the other arrays to this array.
 *
 * @param const WeightedGraph & otherm which is the other object to be copied to make this object.
 * @return This function does not return anything.
 *
 * @pre none
 * @post The WeightedGraph is an exact copy of the other object that was passed in.
 *
 */
WeightedGraph::WeightedGraph(const WeightedGraph & other)
{
	size = other.size;
	maxSize = other.maxSize;
	vertexList = new Vertex[other.maxSize];
	adjMatrix = new int[other.maxSize * other.maxSize];
	pathMatrix = new int [maxSize * maxSize];
	for(int i = 0; i < other.maxSize; i++)
	{
		vertexList[i] = other.vertexList[i];
		for(int j = 0; j < other.maxSize; j++)
		{
			adjMatrix[(i * other.maxSize) + j] = other.adjMatrix[(i * other.maxSize) + j];
			pathMatrix[(i * other.maxSize) + j] = other.pathMatrix[(i * other.maxSize) + j];
		}
	}
}

/**
 * This function is the overloaded assignment operator for the WeightedGraph class.
 *
 * The function will first check to make sure that the other object is not the same as this object.
 * The function will then set the maxSize equal to the other WeightedGraph's maxSize.
 * The function will set the size equal to the other WeightedGraph's size.
 * The function will dynamically allocate memory for the vertexList to be equal to the maxSize.
 * The function will dynamically allocate memory for the adjMatrix and pathMatrix equal to the maxSize * maxSize.
 * The function will then loop through the maxSize of the array, acting like a 2D array and turning it into a 1D array
 * for the adjacency matrix, and then set copy the data from the other arrays to this array.
 *
 * @param const WeightedGraph & otherm which is the other object to be copied to make this object.
 * @return This function returns a pointer to this object.
 *
 * @pre none
 * @post The WeightedGraph is an exact copy of the other object that was passed in.
 *
 */
WeightedGraph& WeightedGraph::operator=(const WeightedGraph& other)
{

	if(this != &other)
	{
		size = other.size;
		maxSize = other.maxSize;
		vertexList = new Vertex[other.maxSize];
		adjMatrix = new int[other.maxSize * other.maxSize];
		for(int i = 0; i < other.maxSize; i++)
		{
			vertexList[i] = other.vertexList[i];
			for(int j = 0; j < other.maxSize; j++)
			{
				adjMatrix[(i * other.maxSize) + j] = other.adjMatrix[(i * other.maxSize) + j];
				pathMatrix[(i * other.maxSize) + j] = other.pathMatrix[(i * other.maxSize) + j];
			}
		}
	}

	return *this;
}

/**
 * This function is the destructor for the WeightedGraph class.
 *
 * This function will call the clear function to clear to set the size to 0.
 * This function will call the delete operator on pathMatrix, adjMatrix and vertexList.
 * This function will set pathMatrix, adjMatrix and vertexList to NULL.
 *
 * @param  none
 * @return This function does not return anything.
 *
 * @pre none
 * @post Size will be set to 0 and pathMatrix, adjMatrix and vertexList will be cleared and deleted and set to NULL.
 *
 */
WeightedGraph::~WeightedGraph()
{
	clear();
	delete[] pathMatrix;
	pathMatrix = NULL;
	delete[] adjMatrix;
	adjMatrix = NULL;
	delete [] vertexList;
	vertexList = NULL;
}

/**
 * This function is the insertVertex function for the WeightedGraph class.
 *
 * The function first checks to see if the vertex already exists in the graph. 
 * If it does, the function will set is equal to the new Vertex and sets the edges with infinite weight and updates them. 
 * Otherwise, if the object is full, the function will throw a logic_error saying Graph Full.
 * If not, the function will increment size and insert the newVertex and set the edges with infinite weight.
 *
 * @param const Vertex& newVertex, which is the newVertex that will be either inserted or updated.
 * @return This function does not return anything.
 *
 * @pre none
 * @post newVertex will be either be inserted into the graph, or the graph will be updated. 
 *
 */
void WeightedGraph::insertVertex(const Vertex& newVertex) throw (logic_error)
{
	for(int i = 0; i < size; i++)
	{
		if((vertexList[i].getLabel()) == (newVertex.getLabel()))
		{
			vertexList[i] = newVertex;
			for(int j = 0; j < size; j++)
			{
				setEdge(i, j, INFINITE_EDGE_WT);
			}
			return;
		}
	}
	if(isFull())
	{
		throw logic_error ("Graph full");
	}
	vertexList[size++] = newVertex;
	for(int k = 0; k < size; k++)
	{
		setEdge(size, k, INFINITE_EDGE_WT);
	}

}

/**
 * This function is the insertEdge function for the WeightedGraph class.
 *
 * The function first checks creates local variables to hold the 2 indexs to insert the edge for and sets them to -10 (invalid number)
 * The function then gets the 2 indexes by calling getIndex with string v1 and string v2 passed as parameters. 
 * If both of the indexes are between 0 and (size * size) the function sets the edge by calling setEdge with V1_Index, V2_Index and the weight passed as the parameters.
 * Other wise, the function throws a logic error saying the vertex was not found or bound error.
 *
 * @param const string& v1, which is the string to look for one of the vertex.
 * @param const string& v2, which is the string to look for the second first.
 * @param int wt, which is the weight to insert for the edge. 
 * @return This function does not return anything.
 *
 * @pre Valid vertices containing v1 and v2. 
 * @post The function will insert the edge with the given weight for the the two vertices.
 *
 */
void WeightedGraph::insertEdge(const string& v1, const string& v2, int wt) throw (logic_error)
{
	int V1_Index = -10;
	int V2_Index = -10;

	V1_Index = getIndex(v1);
	V2_Index = getIndex(v2);

	if((0 <= V1_Index < (size*size)) && (0 <= V2_Index < (size*size)))
	{
		setEdge(V1_Index, V2_Index, wt);
	}
	else
	{
		throw logic_error("Vertex not found or bound error");
	}
}

/**
 * This function is the retrieveVertex function for the WeightedGraph class.
 *
 * The function first declares a local bool variable called to_return and sets it as false.  
 * The function then iterates through the entire size of the vertexList and continues until it finds the label that is equal to the string v. 
 * The function sets vData to be equal to the vertex that was found to be equal to the label of string v.
 * The function returns the variable to_return;
 *
 * @param const string& v, which is the label to look for in the vertices.
 * @param Vertex& vData, which holds the value of the vertex's data that was found.
 * @return This function returns the variable to_return indicating true of false if the vertex was found and retrieved.
 *
 * @pre none
 * @post This function returns the variable to_return indicating true of false if the vertex was found and retrieved and then sets vData equal to the vertex that was found.
 *
 */
bool WeightedGraph::retrieveVertex(const string& v, Vertex& vData) const
{

	bool to_return = false;
	
	for(int i = 0; i < size; i++)
	{
			if(vertexList[i].getLabel() == v)
			{
				vData = vertexList[i];
				to_return = true;
			}	
	}
	
	return to_return;
}


/**
 * This function is the getEdgeWeight function for the WeightedGraph class.
 *
 * The function first checks creates local variables to hold the 2 indexs to insert the edge for and sets them to -10 (invalid number) and a bool variable to return.
 * The function then gets the 2 indexes by calling getIndex with string v1 and string v2 passed as parameters. 
 * If both of the indexes are not between 0 and (size * size) the function throws a logic error saying vertex not found or bound error.
 * Other wise, the function throws a logic error saying the vertex was not found or bound error.
 * The function checks to see that the edge weight is not infinite, to make sure that an edge exists. If an edge exists, the weight of to the edge is set to wt and to_return is set to true.
 *
 * @param const string& v1, which is the string to look for one of the vertex.
 * @param const string& v2, which is the string to look for the second first.
 * @param int wt, which is the variable to hold the weight from the edge between the two vertices.
 * @return This function returns return to_return based on if the vertices if found and the edge weight exists.
 *
 * @pre Valid vertices containing v1 and v2. 
 * @post The function will return to_return based on if the vertices is found and the edge weight exists, and then set wt equal to the weight of the ede.
 *
 */
bool WeightedGraph::getEdgeWeight(const string& v1, const string& v2, int& wt) const throw (logic_error)
{

	bool to_return = false;
	int V1_Index = -10;
	int V2_Index = -10;
	
	V1_Index = getIndex(v1);
	V2_Index = getIndex(v2);
	
	if(!(0 <= V1_Index < (size*size)) || (!(0 <= V2_Index < (size*size))))
	{
		throw logic_error("Vertex not found or bound error");
	}
	
	if(adjMatrix[(V1_Index * maxSize) + V2_Index] != INFINITE_EDGE_WT)
	{
		wt = adjMatrix[(V1_Index * maxSize) + V2_Index];
		to_return = true;
	}

	return to_return;
}

/**
 * This function is the removeVertex function for the WeightedGraph class.
 *
 * The function looks to see if the label of a vertex is equal to the string v. 
 * If it is found, the function fixes the adjacency matrix by moving everything to the left by 1. 
 * The function then fixes the adjacency matrix by by moving everything up by 1. 
 * The function has to fix by left and up because it is imagined as a 2d array, but it is represented as a 1d array.
 * The funtion then moves everything from the vertexList to the left by 1 from the point it is at to the size and then decrements the size, which will then force the function to return.
 * If none of that occurs, the function throws a logic error saying that either the vertex was not found or there was a bound error.
 *
 * @param const string& v1, which is the string to look for the vertex label.
 * @return This function does not return anything.
 *
 * @pre A valid vertex in the graph.
 * @post The function removs the vertex from the list and removes edges connected to it and fixes the adjacency matrix.
 *
 */
void WeightedGraph::removeVertex(const string& v) throw (logic_error)
{
	for(int i = 0; i < size; i++)
	{
		if(vertexList[i].getLabel() == v)
		{
			for(int j = i; j < (size -1); j++)
			{
				for(int k = 0; k < size; k++)
				{
					adjMatrix[(k * maxSize) + j] = adjMatrix[(k * maxSize) + (j+1)];
				}
			}
			for(int L = 0; L < (size - 1); L++)
			{
				for(int M = i; M < size; M++)
				{
					adjMatrix[(M * maxSize) + L] = adjMatrix[(M + 1) * maxSize + L];
				}
			}
			for(int N = i; N < size; N++)
			{
				vertexList[N] = vertexList[N+1];
			}
			--size;
			return;
		}
	}
	//else
	throw logic_error("Vertex not found or bound error");	
}

/**
 * This function is the removeEdge function for the WeightedGraph class.
 *
 * The function first checks creates local variables to hold the 2 indexs to insert the edge for and sets them to -10 (invalid number.
 * The function then gets the 2 indexes by calling getIndex with string v1 and string v2 passed as parameters. 
 * If both of the indexes are between 0 and (size * size) the function sets the edge by calling setEdge with V1_Index, V2_Index and Infinite passed as the parameters.
 * Other wise, the function throws a logic error saying the vertex was not found or bound error.
 *
 * @param const string& v1, which is the string to look for one of the vertex.
 * @param const string& v2, which is the string to look for the second first.
 * @return This function does not return anything.
 *
 * @pre Valid vertices containing v1 and v2. 
 * @post The function will remove the edge connecting between two vertices if they are found.
 *
 */
void WeightedGraph::removeEdge(const string& v1, const string& v2) throw (logic_error)
{
	int V1_Index = -10;
	int V2_Index = -10;

	V1_Index = getIndex(v1);
	V2_Index = getIndex(v2);

	if((0 <= V1_Index < (size*size)) && (0 <= V2_Index < (size*size)))
	{
		setEdge(V1_Index, V2_Index, INFINITE_EDGE_WT);
	}
	else
	{
		throw logic_error("Vertex not found or bound error");
	}
	

}

/**
 * This function is the clear function for the WightedGraph class.
 *
 * This function sets the size of the WeightedGraph to be 0.
 *
 * @param none
 * @return This function does not return anything
 *
 * @pre  none
 * @post This function will clear the WeightedGraph by setting size is 0.
 *
 */
void WeightedGraph::clear()
{
	size = 0;
}

/**
 * This function is the isEmpty function for the WeightedGraph class.
 *
 * This function checks to see if size is equal to 0. If it is, the function returns true. Otherwise the function returns false.
 *
 * @param none
 * @return This function returns if the WeightedGraph is empty or not.
 *
 * @pre  none
 * @post This function will return if the WeightedGraph is empty or not.
 *
 */
bool WeightedGraph::isEmpty() const
{
	if(size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is the isFull function for the WeightedGraph class.
 *
 * This function checks to see if size is equal to the maxSize. If it is, the function returns true. Otherwise the function returns false.
 *
 * @param none
 * @return This function returns if the WeightedGraph is full or not.
 *
 * @pre  none
 * @post This function will return if the WeightedGraph is full or not.
 *
 */
bool WeightedGraph::isFull() const 
{
	if(size == maxSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is the showStructure function for the WeightedGraph class
 *
 * Outputs the vertexList and adjacency Matrix of the WeightedGraph will be printed.
 * If the size is 0, the function will just print out empty graph.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre none
 * @post The vertexList and adjacency Matrix of the WeightedGraph will be printed.
 *
 */
void WeightedGraph::showStructure () const
{
	if (size == 0) 
	{
		cout << "Empty graph" << endl;
	} 
	else 
	{
		cout << endl << "Vertex list : " << endl;
		for (int row = 0; row < size; row++)
		{
			cout << row << '\t' << vertexList[row].getLabel();
			cout << '\t' << vertexList[row].getColor();	
			cout << endl;
		}
		cout << endl << "Edge matrix : " << endl << '\t';
		for (int col = 0; col < size; col++)
		{
			cout << col << '\t';
		}
		cout << endl;
		for (int row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (int col = 0; col < size; col++)
			{
				int wt = getEdge(row,col);
				if (wt == INFINITE_EDGE_WT )
				{
					cout << "- \t";
				}
				else
				{
					
					cout << wt << '\t';
				}
			}
			cout << endl;
		}
	}
}


/**
 * This function is the showShortestPath function for the WeightedGraph class
 *
 * We use Floyd's algorithm to make sure that a path from vertex k to vertex j and there exists a path from vertex j to vertex l
 * and the sum of entries (k,j) abd (j,l) is less than entry (k,l) in the path matrix. Then we replace entry (k,l)with the sum of entries (k,j) and (j,l)
 * We make sure that the paths exist at first, and then we check to see that Floyd's algorhtm is true, and if it is, we set the Path to be the smallest path.
 *
 * @param none
 * @return This function does not return anything.
 *
 * @pre none
 * @post The Path Matrix is printed just like shown above in the showStructure function for the Edge and Matrix, as that one was given and i modeled it to match that.
 *
 */
void WeightedGraph::showShortestPaths()
{

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			int w = getEdge(i, j);
			setPath(i, j, w);
		}
		setPath(i, i, 0);
	}
	for(int j = 0; j < size; j++)
	{
		for(int k = 0; k < size; k++)
		{
			for(int l = 0; l < size; l++)
			{
				if((getPath(k, j) != INFINITE_EDGE_WT) && (getPath(j, l) != INFINITE_EDGE_WT))
				{
					if((getPath(k, j) + getPath(j, l) < getPath(k, l)) || (getPath(k, l) == INFINITE_EDGE_WT))
					{
						setPath(k, l, (getPath(k, j) + getPath(j, l)));
					}
				}
			}
		}
	}
	// example taken from the show structure function
    cout << endl << "Path matrix : " << endl << '\t';
    for (int col = 0; col < size; col++)
	{
        cout << col << '\t';
	}
    cout << endl;
    for (int row = 0; row < size; row++)
    {
        cout << row << '\t';
        for (int col = 0 ; col < size ; col++)
        {
            int wt = getPath(row, col);
            if (wt == INFINITE_EDGE_WT)
			{
				cout << "- \t";
			}
            else
			{
				cout << wt << '\t';
			}
        }
        cout << endl;
    }
}


/**
 * This function is the hasProperColoring function for the WeightedGraph class
 *
 * The function checks to see if the vertice's colors in the graph are different from adjacent vertices. 
 * The function does this by checking the vertex next to it by making sure that the vertex in front of it and connected via an edge are not equal in color.
 *
 * @param none
 * @return If the vertice's colors in the graph are different from adjacenct vertices, it returns, else it returns false.
 *
 * @pre All verties have been assigned a color
 * @post If the vertice's colors in the graph are different from adjacenct vertices, it returns, else it returns false.
 *
 */
bool WeightedGraph::hasProperColoring() const 
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if((getEdge(i, j) != INFINITE_EDGE_WT) && (vertexList[i].getColor() == vertexList[j].getColor()) && (i != j))
			{
				return false;	
			}
		}
	}
	return true;
}

/**
 * This function is the areAllEven function for the WeightedGraph class
 *
 * The function checks to see if every vertex in a graph is of even degree, meaning that the amount of vertices the vertex is connected to is an even number.
 * The function does this by looping through an checks to see if there exists an edge between a vertix and another. If it does, it increments edges by one. 
 * After one vertex is done, it checks to see if the the number of edges of that vertex is not divisible by 2, if it isn't the function sets to_return to false.
 * Otherwise, the function resets Edges to 0 and increments i and moves to the next vertex. The function returns to_return at the end.
 *
 * @param none
 * @return If all of the vertices on the graph is even, the function returns true, else it returns false.
 *
 * @pre none
 * @post If all of the vertices on the graph is even, the function returns true, else it returns false.
 *
 */
bool WeightedGraph::areAllEven() const
{
	int Edges = 0;
	bool to_return = true;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(adjMatrix[i*maxSize + j] != INFINITE_EDGE_WT)
			{
				Edges++;
			}
		}
		if(Edges % 2 != 0)
		{
			to_return = false;
		}
		Edges = 0;
	}
	
	return to_return;
}

/**
 * This function is the getIndexfunction for the WeightedGraph class
 *
 * The function goes through the size of the vertexList and checks to see if a vertex's label is equal to the string v. 
 * If it does, the function returns the index of the Vertex. If it doesn't the function returns -10, to show that the function could not find the vertex. 
 *
 * @param const string& v which is the string label to look for in a vertex.
 * @return returns the index of the vertex if it is found, or it returns -10 if the vertex is not found.
 *
 * @pre none
 * @post returns the index of the vertex if it is found, or it returns -10 if the vertex is not found.
 *
 */
int WeightedGraph::getIndex(const string& v) const
{

	for(int i = 0; i < size; i++)
	{
		if(vertexList[i].getLabel() == v)
		{
			return i;
		}
	}
	return -10;
}

/**
 * This function is the getEdge for the WeightedGraph class
 *
 * The function makes sure that row and size are within the maxSize of the array. it it is, the function returns the edge associated with the row and col of the adjacency matrix.
 *
 * @param int row, which is the row of the edge to look for
 * @param int col, which is the col of the edge to look for
 * @return returns the edge of the given row and col from the adjacency matrix, if it is within bounds. Otherwise it returns -10.
 *
 * @pre none
 * @post returns the edge of the given row and col from the adjacency matrix, if it is within bounds. Otherwise it returns -10.
 */
int WeightedGraph::getEdge(int row, int col) const 
{
	if((row < maxSize) && (col < maxSize))
	{
		return adjMatrix[(row*maxSize) + col];
	}
	else
	{
		return -10;
	}
}

/**
 * This function is the getPath for the WeightedGraph class
 *
 * The function makes sure that row and size are within the maxSize of the array. it it is, the function returns the edge associated with the row and col of the pathMatrix.
 *
 * @param int row, which is the row of the  path to look for
 * @param int col, which is the col of the path  to look for
 * @return returns the path of the given row and col from the path matrix, if it is within bounds. Otherwise it returns -10.
 *
 * @pre none
 * @post returns the path of the given row and col from the path matrix, if it is within bounds. Otherwise it returns -10.
 */
int WeightedGraph::getPath(int row, int col) const 
{
	if((row < maxSize) && (col < maxSize))
	{
		return pathMatrix[(row * maxSize) + col];
	}
	else
	{
		return -10;
	}
}

/**
 * This function is the setEdge for the WeightedGraph class
 *
 * The function makes sure that row and size are within the maxSize of the array. it it is, the function then sets the edge for the row and col. 
 * Sine we have a 1d array mapped as a 2d array, we have to set the edge weight for both index in the adjacency Matrix.
 *
 * @param int row, which is the row of the edge to set for
 * @param int col, which is the col of the edge to set for
 * @return This function does not return anything.
 *
 * @pre none
 * @post sets the edge of a given row and col by setting the edge weight for the index in the adjacency Matrix.
 */
void WeightedGraph::setEdge(int row, int col, int wt)
{
	if((row < maxSize) && (col < maxSize))
	{
		adjMatrix[(row*maxSize) + col] = wt;
		adjMatrix[(col*maxSize) + row] = wt;
	}
}

/**
 * This function is the setPath for the WeightedGraph class
 *
 * The function makes sure that row and size are within the maxSize of the array. it it is, the function then sets the path for the row and col. 
 * Sine we have a 1d array mapped as a 2d array, we have to set the path for both index in the Path Matrix.
 *
 * @param int row, which is the row of the path to set for
 * @param int col, which is the col of the path to set for
 * @return This function does not return anything.
 *
 * @pre none
 * @post sets the path of a given row and col by setting the path for the index in the adjacency Matrix.
 */
void WeightedGraph::setPath(int row, int col, int wt) 
{
	if((row < maxSize) && (col < maxSize))
	{
		pathMatrix[(row*maxSize) + col] = wt;
		pathMatrix[(col*maxSize) + row] = wt;
	}
}











