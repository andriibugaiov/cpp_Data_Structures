//
//  ABVector.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABVector.h"

#include "ABVertex.h"
#include "ABEdge.h"

#include <stdexcept>
#include <iostream>

using namespace std;

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
	return getSize() == 0;
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
	return &_origin[0];
}

template <typename T>
typename ABVector<T>::ABConstIterator ABVector<T>::begin() const
{
	return &_origin[0];
}

template <typename T>
typename ABVector<T>::ABIterator ABVector<T>::end()
{
	return &_origin[getSize()];
}

template <typename T>
typename ABVector<T>::ABConstIterator ABVector<T>::end() const
{
	return &_origin[getSize()];
}

#pragma mark - 

template class ABVector<int>;
template class ABVector<int *>;
template class ABVector<ABVertex>;
template class ABVector<ABEdge>;

#pragma mark -

void ABVectorUnitTests()
{
	ABVector<int *> v(0);
	int j;
	for (j = 0; j < 10; ++j)
	{
		int *i = new int(j);
		v.pushBack(i);
	}
	
	const ABVector<int *> constV = v;
	ABVector<int *>::ABConstIterator constI;
	for (constI = constV.begin(); constI != constV.end(); ++constI)
	{
		cout << **constI << endl;
	}
	
	ABVector<int *>::ABIterator i;
	for (i = v.begin(); i != v.end(); ++i)
	{
		delete *i;
	}
}
