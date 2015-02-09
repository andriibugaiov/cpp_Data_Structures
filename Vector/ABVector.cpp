//
//  ABVector.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABVector.h"

#include <stdexcept>
//#include <iostream>

using namespace std;

template <typename T>
ABVector<T>::ABVector() : _size(0), _capacity(0)
{
	_origin = nullptr;
}

template <typename T>
ABVector<T>::ABVector(int aCapacity) : _size(0), _capacity(aCapacity)
{
	_origin = getCapacity() > 0 ? new T[getCapacity()] : nullptr;
}

template <typename T>
ABVector<T>::ABVector(const ABVector<T> &anOther)
{
	_capacity = anOther.getCapacity();
	_size = anOther.getSize();
	_origin = getCapacity() > 0 ? new T[getCapacity()] : nullptr;
	
	int i;
	for (i = 0; i < getSize(); ++i)
	{
		_origin[i] = anOther[i];
	}
}

template <typename T>
ABVector<T>::~ABVector()
{
	delete [] _origin;
}

#pragma mark -

template <typename T>
void ABVector<T>::reserve(int aCapacity)
{
	if (aCapacity <= getCapacity())
	{
		return;
	}
	
	T *origin = _origin;
	
	_capacity = aCapacity;
	_origin = new T[getCapacity()];
	
	int i;
	for (i = 0; i < getSize(); ++i)
	{
		_origin[i] = origin[i];
	}
	delete [] origin;
}

#pragma mark -

template <typename T>
int ABVector<T>::getSize() const
{
	return _size;
}

template <typename T>
int ABVector<T>::getCapacity() const
{
	return _capacity;
}

template <typename T>
bool ABVector<T>::isEmpty() const
{
	return !(getSize() > 0);
}

#pragma mark -

template <typename T>
const ABVector<T> &ABVector<T>::operator=(const ABVector &anOther)
{
	if (this != &anOther)
	{
		if (getCapacity() > 0)
		{
			delete [] _origin;
		}
		_capacity = anOther.getCapacity();
		_size = anOther.getSize();
		_origin = getCapacity() > 0 ? new T[getCapacity()] : nullptr;
		
		int i;
		for (i = 0; i < getSize(); ++i)
		{
			_origin[i] = anOther[i];
		}
	}
	return *this;
}

template <typename T>
T &ABVector<T>::operator[](int aPosition)
{
	if (aPosition >= getSize())
	{
		throw invalid_argument("aPosition >= getSize()");
	}
	return _origin[aPosition];
}

template <typename T>
const T &ABVector<T>::operator[](int aPosition) const
{
	if (aPosition >= getSize())
	{
		throw invalid_argument("aPosition >= getSize()");
	}
	return _origin[aPosition];
}

#pragma mark -

template <typename T>
void ABVector<T>::pushBack(const T &aData)
{
	insert(getSize(), aData);
}

template <typename T>
T ABVector<T>::popBack()
{
	return remove(getSize() - 1);
}

#pragma mark -

template <typename T>
void ABVector<T>::insert(int aPosition, const T &aData)
{
	if (aPosition > getSize())
	{
		throw invalid_argument("aPosition > getSize()");
	}
	if (getSize() == getCapacity())
	{
		reserve(2 * getCapacity() + 1);
	}
	
	int i;
	for (i = getSize() - 1; i >= aPosition; --i)
 	{
		_origin[i + 1] = _origin[i];
	}
	_origin[aPosition] = aData;
	++_size;
}

template <typename T>
T ABVector<T>::remove(int aPosition)
{
	if (aPosition >= getSize())
	{
		throw invalid_argument("aPosition >= getSize()");
	}
	
	T retValue = _origin[aPosition];
	
	int i;
	for (i = aPosition + 1; i < getSize(); ++i)
	{
		_origin[i - 1] = _origin[i];
	}	
	--_size;
	
	return retValue;
}

#pragma mark -

template <typename T>
typename ABVector<T>::ABIterator ABVector<T>::begin()
{
	if (isEmpty())
	{
		throw invalid_argument("isEmpty()");
	}
	return &_origin[0];
}

template <typename T>
typename ABVector<T>::ABConstIterator ABVector<T>::begin() const
{
	if (isEmpty())
	{
		throw invalid_argument("isEmpty()");
	}
	return &_origin[0];
}

template <typename T>
typename ABVector<T>::ABIterator ABVector<T>::end()
{
	if (isEmpty())
	{
		throw invalid_argument("isEmpty()");
	}
	return &_origin[getSize() - 1];
}

template <typename T>
typename ABVector<T>::ABConstIterator ABVector<T>::end() const
{
	if (isEmpty())
	{
		throw invalid_argument("isEmpty()");
	}
	return &_origin[getSize() - 1];
}


template class ABVector<int>;
template class ABVector<int *>;
