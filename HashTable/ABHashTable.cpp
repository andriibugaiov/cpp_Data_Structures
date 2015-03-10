//
//  ABHashTable.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-04.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABHashTable.h"

#include "ABNodeHeapTree.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
void ABHashTable<T>::rehash()
{
//	double loadFactor = double(getSize()) / double(getTableSize());
	// TODO:
}

template <typename T>
int ABHashTable<T>::myHash(/*const*/ T &aData)
{
	int hashValue = _hash(aData) % getTableSize();
	if (hashValue < 0)
	{
		hashValue += getTableSize();
	}
	return hashValue;
}

#pragma mark -

template <typename T>
ABHashTable<T>::ABHashTable(int aCapacity) : _size(0)
{
	_table.reserve(aCapacity);
	int i;
	for (i = 0; i < _table.getCapacity(); ++i)
	{
		ABList<T> list;
		_table.pushBack(list);
	}
	if (getTableSize() != _table.getCapacity())
	{
		throw runtime_error("Size of the table is not equal to its capacity.");
	}
}

template <typename T>
void ABHashTable<T>::display()
{
	int i = 0;
	for (; i < _table.getSize(); ++i)
	{
		cout << i + 1 << " - ";
		ABList<T> &list = _table[i];
		
		if (list.isEmpty())
		{
			cout << "Empty row.";
		}
		else
		{
			cout << list.getSize() << " ";
		}
		cout << endl;
	}
}

#pragma mark -

template <typename T>
int ABHashTable<T>::getSize() const
{
	return _size;
}

template <typename T>
int ABHashTable<T>::getTableSize() const
{
	return _table.getSize();
}

template <typename T>
bool ABHashTable<T>::isEmpty() const
{
	return getSize() == 0;
}

#pragma mark -

template <typename T>
const ABList<T> &ABHashTable<T>::operator[](int aPosition) const
{
	if (aPosition >= getTableSize())
	{
		throw runtime_error("aPosition >= getTableSize()");
	}
	return _table[aPosition];
}

template <typename T>
bool ABHashTable<T>::search(/*const*/ T &aData)
{
	int hashValue = myHash(aData);
	ABList<T> &list = _table[hashValue];
	
	typename ABList<T>::ABIterator iterator = list.begin();
	for (;iterator != list.end(); ++iterator)
	{
		if (*iterator == aData)
		{
			return true;
		}
	}
	return false;
}

template <typename T>
void ABHashTable<T>::insert(/*const*/ T &aData)
{
	int hashValue = myHash(aData);
	ABList<T> &list = _table[hashValue];
	
	typename ABList<T>::ABIterator iterator = list.begin();
	for (;iterator != list.end(); ++iterator)
	{
		if (*iterator == aData)
		{
			return;
		}
	}
	list.pushFront(aData);
	++_size;
	
	rehash();
}

template <typename T>
void ABHashTable<T>::remove(/*const*/ T &aData)
{
	int hashValue = myHash(aData);
	ABList<T> &list = _table[hashValue];
	
	typename ABList<T>::ABIterator iterator = list.begin();
	for (;iterator != list.end(); ++iterator)
	{
		if (*iterator == aData)
		{
			list.remove(iterator);
			--_size;
			
			rehash();
			return;
		}
	}
}

#pragma mark -

template class ABHashTable<long long>;
template class ABHashTable<ABNodeHeapTree<long long>>;

#pragma mark - 

template <typename T>
void ABHashTableUnitTests(ABHashTable<T> &aHashTable)
{
	
}

#pragma mark -

long long _hash(long long aValue)
{
	return aValue;
}

#pragma mark - 

#define T_MIN (-10000)
#define T_MAX (10000)

// TODO:
int ABTwoSumComputingAlgorithm(const char *aFileName)
{
	ifstream filestream(aFileName);
	if(!filestream)
	{
		throw runtime_error("Failed to open file.");
	}
	
	int twoSums[T_MAX - T_MIN + 1] = {0};
	long long m = T_MAX - T_MIN + 1;
	
	ABHashTable<ABNodeHeapTree<long long>> ht(546527);
	long long value;
	while (filestream >> value)
	{
		int key = int(value / m);
		ABNodeHeapTree<long long> node(value, key);
		ht.insert(node);
	}
	filestream.close();	
	//	ht.display();
	
	int j = 0;
	for (; j < ht.getTableSize(); ++j)
	{
		const ABList<ABNodeHeapTree<long long>> &list = ht[j];
		ABList<ABNodeHeapTree<long long>>::ABConstIterator listIterator = list.begin();
		for (; listIterator != list.end(); ++listIterator)
		{
			long long T = T_MIN - (*listIterator).getData();
			int keys[2];
			keys[0] = int(T / m);
			keys[1] = int(T / m) + 1;
			
			int i = 0;
			for (; i < sizeof(keys) / sizeof(keys[0]); ++i)
			{
				int hashValue = keys[i] % ht.getTableSize();
				if (hashValue < 0)
				{
					hashValue += ht.getTableSize();
				}
				
				const ABList<ABNodeHeapTree<long long>> &otherList = ht[hashValue];
				ABList<ABNodeHeapTree<long long>>::ABConstIterator otherListIterator = otherList.begin();
				for (; otherListIterator != otherList.end(); ++otherListIterator)
				{
					long long twoSum = (*listIterator).getData() + (*otherListIterator).getData();
					if (twoSum >= T_MIN && twoSum <= T_MAX)
					{
						twoSums[twoSum - T_MIN] = 1;
					}
				}
			}
		}
	}
	
	int counter = 0;
	for (j = 0; j < T_MAX - T_MIN + 1; ++j)
	{
		counter += twoSums[j];
	}
	return counter;
}

long long _hash(ABNodeHeapTree<long long> &aNode)
{
	return aNode.getKey();
}