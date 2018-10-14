int Heap::remove() throw (logic_error)
{
	if(isEmpty())
	{
		throw logic_error("Empty Heap");
	}
	else
	{
		int temp = dataItems[0];
		dataItems[0] = dataItems[--size];
		int parent = 0;

		while(parent < size)
		{
			if(RightChild(parent) <= size) 
			{
				if((dataItems[RightChild(parent)]) > (dataItems[LeftChild(parent)]))
				{
					swap(parent,RightChild(parent));
					parent = RightChild(parent);
				}
				else if((dataItems[LeftChild(parent)]) > (dataItems[RightChild(parent)]))
				{
					swap(parent, LeftChild(parent));
					parent = LeftChild(parent);
				}
				else if(dataItems[LeftChild(parent)]== dataItems[RightChild(parent)])
				{
					swap(parent,LeftChild(parent));
					parent = LeftChild(parent);
				}
				else
				{
					return temp;				
				}
			}
			else if(LeftChild(parent) <= size)
			{
				if((dataItems[parent].getPriority() < dataItems[LeftChild(parent)].getPriority()))
				{
					swap(parent,LeftChild(parent));	
					parent = LeftChild(parent);
				}
				else
				{
					return temp;
				}
			}    
			else
			{
				return temp;
			}
		}
	return temp;
	}
}
