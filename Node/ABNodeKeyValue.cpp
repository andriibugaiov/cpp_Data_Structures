//
//  ABNodeKeyValue.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-27.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#include "ABNodeKeyValue.h"

#include "ABEdge.h"
#include "ABVertex.h"

template <typename T>
ABNodeKeyValue<T>::ABNodeKeyValue(int aKey) : ABNode<T>(), _key(aKey)
{
    
}

template <typename T>
ABNodeKeyValue<T>::ABNodeKeyValue(const T &aData, int aKey) : ABNode<T>(aData), _key(aKey)
{
    
}

template <typename T>
int ABNodeKeyValue<T>::getKey() const
{
    return _key;
}

template <typename T>
void ABNodeKeyValue<T>::setKey(int aKey)
{
    _key = aKey;
}

#pragma mark -

template <typename T>
bool ABNodeKeyValue<T>::operator<(const ABNodeKeyValue<T> &anOther)
{
    return getKey() < anOther.getKey();
}

template <typename T>
bool ABNodeKeyValue<T>::operator>(const ABNodeKeyValue<T> &anOther)
{
    return getKey() > anOther.getKey();
}

template <typename T>
bool ABNodeKeyValue<T>::operator==(const ABNodeKeyValue<T> &anOther)
{
	// TODO:
	return getKey() == anOther.getKey() && (this -> getData() == anOther.getData());
}

#pragma mark -

template class ABNodeKeyValue<long long>;
template class ABNodeKeyValue<int>;
template class ABNodeKeyValue<int *>;
template class ABNodeKeyValue<ABEdge *>;
template class ABNodeKeyValue<ABVertex *>;
