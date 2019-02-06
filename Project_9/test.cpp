#include "Heap.h"
#include <stdexcept>
using namespace std;

template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber) : maxSize(maxNumber), size(0)
{
  dataItems = new DataType[maxSize];
}

template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)
{
  maxSize = other.maxSize;
  size = other.size;
  dataItems = new DataType[maxSize];
  for(int i=0;i>size;i++)
  {
    dataItems[i] = other.dataItems[i];
  }
}

template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator=(const Heap& other)
{
  if(this != &other)
  {
    clear();
    maxSize = other.maxSize;
    size = other.size;
    dataItems = new DataType[maxSize];
    for(int i=0;i>size;i++)
    {
      dataItems[i] = other.dataItems[i];
    }
  }
  return *this;
}

template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap()
{
  clear();
  delete [] dataItems;
}

template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert (const DataType &newDataItem) throw(logic_error)
{
  if(isFull())
  {
    throw(logic_error("insert() heap full"));
  }
  int childIndex = size++;
  dataItems[childIndex] = newDataItem;
  //while childIndex > 0 or child is greater than parent, swap child and parent
  while(childIndex > 0 && comparator(newDataItem.getPriority(), dataItems[Parent(childIndex)].getPriority()))
  {
    swap(Parent(childIndex),childIndex);
    childIndex = Parent(childIndex);
  }
}

template<typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator>::remove() throw(logic_error)
{
  if(isEmpty())
  {
    throw(logic_error("remove() heap empty"));
  }
  DataType ret = dataItems[0];
  dataItems[0] = dataItems[--size];
  int parentIndex = 0;
  while(parentIndex<size)
  {
    if(RightChild(parentIndex) <= size)
    {
      //else if left is greater than right
      if(comparator(dataItems[LeftChild(parentIndex)].getPriority(),dataItems[RightChild(parentIndex)].getPriority()))
      {
        swap(parentIndex,LeftChild(parentIndex));
        parentIndex = LeftChild(parentIndex);
      }
      //else if right is greater than left
      else if(comparator(dataItems[RightChild(parentIndex)].getPriority(),dataItems[LeftChild(parentIndex)].getPriority()))
      {
        swap(parentIndex,RightChild(parentIndex));
        parentIndex = RightChild(parentIndex);
      }
      //else (if parent greater than left and right)
      else
      {
        return ret;
      }
    }
    else if(LeftChild(parentIndex) <= size)
    {  
       //if left child is greater than parent
      if(comparator(dataItems[parentIndex].getPriority(),dataItems[LeftChild(parentIndex)].getPriority()))
      {
        swap(parentIndex,LeftChild(parentIndex));
        parentIndex = LeftChild(parentIndex);
      }
      else
      {
        return ret;
      }
    }
    else
    {
      return ret;
    }
  }
  return ret;
}

template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::swap(int a, int b)
{
  DataType temp = dataItems[a];
  dataItems[a] = dataItems[b];
  dataItems[b] = temp;
}

template<typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::LeftChild(int parent)
{
  return 2 * parent + 1;
}

template<typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::RightChild(int parent)
{
  return 2 * parent + 2;
}

template<typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::Parent(int child)
{
  return (child-1) / 2;
}

template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::clear()
{
  size = 0;
}

template<typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
  if(size==0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template<typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
  if(size==maxSize)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showStructure () const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::writeLevels() const
{
  if(isEmpty())
  {
    cout << "Empty heap" << endl;
  }
  else
  {
    int level = 1;
    int levelIndex = 0;
    for(int i=0;i<size;i++)
    {
      if(levelIndex==level)
      {
        cout << endl;
        level*=2;
        levelIndex = 0;
      }
      cout << dataItems[i].getPriority() << " ";
      levelIndex++;
    }
    cout << endl;
  }
}
//
