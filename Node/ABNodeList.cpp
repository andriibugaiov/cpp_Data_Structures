//
//  ABNodeList.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABNodeList.h"

#include "ABEdge.h"
#include "ABVertex.h"
#include "ABNodeHeapTree.h"

template <typename T>
ABNodeList<T>::ABNodeList(ABNodeList<T> *aNext, ABNodeList<T> *aPrevious) : _next(aNext), _previous(aPrevious)
{
	
}

template <typename T>
ABNodeList<T>::ABNodeList(const T& aData, ABNodeList<T> *aNext, ABNodeList<T> *aPrevious) : ABNode<T>(aData), _next(aNext), _previous(aPrevious)
{
}

template <typename T>
void ABNodeList<T>::setNext(ABNodeList<T> *aNext)
{
	_next = aNext;
}

template <typename T>
void ABNodeList<T>::setPrevious(ABNodeList<T> *aPrevious)
{
	_previous = aPrevious;
}

template <typename T>
ABNodeList<T>* ABNodeList<T>::getNext() const
{
	return _next;
}

template <typename T>
ABNodeList<T>* ABNodeList<T>::getPrevious() const
{
	return _previous;
}

#pragma mark -

template class ABNodeList<long long>;
template class ABNodeList<int>;
template class ABNodeList<int *>;
template class ABNodeList<ABEdge *>;
template class ABNodeList<ABEdge>;
template class ABNodeList<ABVertex *>;
template class ABNodeList<ABVertex>;
template class ABNodeList<ABNodeHeapTree<long long>>;
