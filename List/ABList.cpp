//
//  ABList.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABList.h"
#include "ABNodeList.h"
#include "ABNode.h"

#include "ABEdge.h"
#include "ABVertex.h"

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
void ABList<T>::initialize()
{
	_pre_head = new ABNodeList<T>();
	_post_tail = new ABNodeList<T>();
	
	_pre_head -> setNext(_post_tail);
	_post_tail -> setPrevious(_pre_head);
}

#pragma mark -

template <typename T>
ABList<T>::ABList() : _size(0)
{
	initialize();
}

template <typename T>
ABList<T>::ABList(const ABList<T>& anOther) : _size(0)
{
	initialize();
	*this = anOther;
}

template <typename T>
ABList<T>::~ABList()
{
	clear();
	delete _pre_head;
	delete _post_tail;
}

#pragma mark -

template <typename T>
ABList<T>::ABConstIterator::ABConstIterator(ABNodeList<T> *aCurrent) : _current(aCurrent)
{
	
}

template <typename T>
ABNodeList<T> *ABList<T>::ABConstIterator::getCurrent() const
{
	return _current;
}

template <typename T>
void ABList<T>::ABConstIterator::setCurrent(ABNodeList<T> *aCurrent)
{
	_current = aCurrent;
}

template <typename T>
ABList<T>::ABConstIterator::ABConstIterator () : _current(nullptr)
{
	
}

#pragma mark -

template <typename T>
const T &ABList<T>::ABConstIterator::operator*() const
{
	return _current -> getData();
}

template <typename T>
typename ABList<T>::ABConstIterator &ABList<T>::ABConstIterator::operator++()
{
	_current = _current -> getNext();
	return *this;
}

template <typename T>
typename ABList<T>::ABConstIterator ABList<T>::ABConstIterator::operator++(int)
{
	ABConstIterator temp = *this;
	++(*this);
	return temp;
}

template <typename T>
typename ABList<T>::ABConstIterator &ABList<T>::ABConstIterator::operator--()
{
	_current = _current -> getPrevious();
	return *this;
}

template <typename T>
typename ABList<T>::ABConstIterator ABList<T>::ABConstIterator::operator--(int)
{
	ABConstIterator temp = *this;
	--(*this);
	return temp;
}

#pragma mark -

template <typename T>
bool ABList<T>::ABConstIterator::operator==(const ABList<T>::ABConstIterator &anOther) const
{
	return _current == anOther.getCurrent();
}

template <typename T>
bool ABList<T>::ABConstIterator::operator!=(const ABConstIterator & anOther) const
{
	return !(*this == anOther);
}

#pragma mark -

template <typename T>
ABList<T>::ABIterator::ABIterator(ABNodeList<T> *aCurrent) : ABConstIterator(aCurrent)
{
}

template <typename T>
ABList<T>::ABIterator::ABIterator() : ABConstIterator()
{
	
}

template <typename T>
T &ABList<T>::ABIterator::operator*()
{
	return this -> getCurrent() -> getData();
}

template <typename T>
const T &ABList<T>::ABIterator::operator*() const
{
	return ABConstIterator::operator*();
}

#pragma mark -

template <typename T>
typename ABList<T>::ABIterator &ABList<T>::ABIterator::operator++()
{
	this -> setCurrent(this -> getCurrent() -> getNext());
	return *this;
}

template <typename T>
typename ABList<T>::ABIterator ABList<T>::ABIterator::operator++(int)
{
	ABIterator temp = *this;
	++(*this);
	return temp;
}

template <typename T>
typename ABList<T>::ABIterator &ABList<T>::ABIterator::operator--()
{
	this -> setCurrent(this -> getCurrent() -> getPrevious());
	return *this;
}

template <typename T>
typename ABList<T>::ABIterator ABList<T>::ABIterator::operator--(int)
{
	ABIterator temp = *this;
	--(*this);
	return temp;
}

#pragma mark -

template <typename T>
const ABList<T> &ABList<T>::operator=(const ABList<T> &anOther)
{
	if (this == &anOther)
	{
		return *this;
	}
	clear();
	ABConstIterator i;
	for (i = anOther.begin(); i != anOther.end(); ++i)
 	{
		pushBack(*i);
	}
	return *this;
}

template <typename T>
typename ABList<T>::ABIterator ABList<T>::begin()
{
	return ABIterator(_pre_head -> getNext());
}

template <typename T>
typename ABList<T>::ABConstIterator ABList<T>::begin() const
{
	return ABConstIterator(_pre_head -> getNext());
}

template <typename T>
typename ABList<T>::ABIterator ABList<T>::end()
{
	return ABIterator(_post_tail);
}

template <typename T>
typename ABList<T>::ABConstIterator ABList<T>::end() const
{
	return ABConstIterator(_post_tail);
}

#pragma mark -

template <typename T>
T &ABList<T>::front()
{
	return *begin();
}

template <typename T>
const T &ABList<T>::front() const
{
	return *begin();
}

template <typename T>
T &ABList<T>::back()
{
	return *--end();
}

template <typename T>
const T &ABList<T>::back() const
{
	return *--end();
}

#pragma mark -

template <typename T>
int ABList<T>::getSize() const
{
	return _size;
}

template <typename T>
bool ABList<T>::isEmpty() const
{
	return getSize() == 0;
}

template <typename T>
void ABList<T>::clear()
{
	remove(begin(), end());
}

#pragma mark -

template <typename T>
void ABList<T>::pushFront(const T &aData)
{
	insert(begin(), aData);
}

template <typename T>
void ABList<T>::pushBack(const T &aData)
{
	insert(end(), aData);
}

template <typename T>
void ABList<T>::popFront()
{
	remove(ABIterator(begin()));
}

template <typename T>
void ABList<T>::popBack()
{
	remove(ABIterator(--end()));
}

template <typename T>
typename ABList<T>::ABIterator ABList<T>::insert(ABIterator anInterator, const T &aData)
{
//	if ()
//	{
//		throw runtime_error("");
//	}
	ABNodeList<T> *next = anInterator.getCurrent();
	
	ABNodeList<T> *previous = next -> getPrevious();
	
	ABNodeList<T> *node = new ABNodeList<T>(aData, next, previous);
	previous -> setNext(node);
	next -> setPrevious(node);
	++_size;
	
	return ABIterator(node);
}

template <typename T>
typename ABList<T>::ABIterator ABList<T>::remove(ABIterator anInterator)
{
	if (isEmpty())
	{
		throw runtime_error("List is empty!");
	}
	ABNodeList<T> *node = anInterator.getCurrent();
	
	ABNodeList<T> *next = node -> getNext();
	ABNodeList<T> *previous = node -> getPrevious();
	
	previous -> setNext(next);
	next -> setPrevious(previous);
	--_size;

	delete node;
	
	return ABIterator(next);
}

template <typename T>
typename ABList<T>::ABIterator ABList<T>::remove(ABIterator aStart, ABIterator anEnd)
{
	ABIterator iterator;
	for (iterator = aStart; iterator != anEnd;)
	{
		iterator = remove(iterator);
	}
	return anEnd;
}

#pragma mark -

template class ABList<int>;
template class ABList<int *>;
template class ABList<ABEdge *>;
template class ABList<ABEdge>;
template class ABList<ABVertex *>;
template class ABList<ABVertex>;

#pragma mark -

void ABListUnitTests(ABList<int *> aList)
{
	int j;
	for (j = 0; j < 10; ++j)
	{
		int *i = new int(j);
		aList.pushBack(i);
	}
	
	ABList<int *>::ABConstIterator constI;
	for (constI = aList.begin(); constI != aList.end(); ++constI)
	{
		cout << **constI << endl;
	}
	
	ABList<int *>::ABIterator i;
	for (i = aList.begin(); i != aList.end();)
	{
		delete *i;
		i = aList.remove(i);
	}
}
