//
//  ABNodeHeapTree.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-27.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#include "ABNodeHeapTree.h"

#include "ABEdge.h"
#include "ABVertex.h"

template <typename T>
ABNodeHeapTree<T>::ABNodeHeapTree(int aKey) : ABNode<T>(), _key(aKey)
{
    
}

template <typename T>
ABNodeHeapTree<T>::ABNodeHeapTree(const T &aData, int aKey) : ABNode<T>(aData), _key(aKey)
{
    
}

template <typename T>
int ABNodeHeapTree<T>::getKey() const
{
    return _key;
}

template <typename T>
void ABNodeHeapTree<T>::setKey(int aKey)
{
    _key = aKey;
}

#pragma mark -

template <typename T>
bool ABNodeHeapTree<T>::operator<(const ABNodeHeapTree<T> &anOther)
{
    return getKey() < anOther.getKey();
}

template <typename T>
bool ABNodeHeapTree<T>::operator>(const ABNodeHeapTree<T> &anOther)
{
    return getKey() > anOther.getKey();
}

template <typename T>
bool ABNodeHeapTree<T>::operator==(const ABNodeHeapTree<T> &anOther)
{
	// TODO:
	return getKey() == anOther.getKey() && (this -> getData() == anOther.getData());
}

#pragma mark -

template class ABNodeHeapTree<long long>;
template class ABNodeHeapTree<int>;
template class ABNodeHeapTree<int *>;
template class ABNodeHeapTree<ABEdge *>;
template class ABNodeHeapTree<ABVertex *>;
