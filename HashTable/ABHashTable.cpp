//
//  ABHashTable.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-04.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABHashTable.h"

#include "ABNodeKeyValue.h"
#include "ABNodeTwoSum.h"

#include <iostream>

using namespace std;

template <typename T>
void ABHashTable<T>::rehash()
{
//	double loadFactor = double(getSize()) / double(getTableSize());
	// TODO:
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
int ABHashTable<T>::hashPosition(/*const*/ T &aData)
{
    int hashPosition = _hash(aData) % getTableSize();
    if (hashPosition < 0)
    {
        hashPosition += getTableSize();
    }
    return hashPosition;
}

template <typename T>
int ABHashTable<T>::getTableSize() const
{
    return _table.getSize();
}

#pragma mark -

template <typename T>
bool ABHashTable<T>::search(/*const*/ T &aData)
{
	int position = hashPosition(aData);
	ABList<T> &list = _table[position];
	
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
	int position = hashPosition(aData);
	ABList<T> &list = _table[position];
	
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
	int position = hashPosition(aData);
	ABList<T> &list = _table[position];
	
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
template class ABHashTable<ABNodeKeyValue<long long>>;
template class ABHashTable<ABNodeTwoSum>;

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
