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
	return getKey() == anOther.getKey();
}

template <typename T>
bool ABNodeKeyValue<T>::operator!=(const ABNodeKeyValue<T> &anOther)
{
	return !(*this == anOther);
}


#pragma mark -

template class ABNodeKeyValue<long long>;
template class ABNodeKeyValue<int>;
template class ABNodeKeyValue<int *>;
template class ABNodeKeyValue<ABEdge *>;
template class ABNodeKeyValue<ABVertex *>;

#pragma mark - 

template <typename T>
long long _hash(ABNodeKeyValue<T> &aNode)
{
    return aNode.getKey();
}

template long long _hash<long long>(ABNodeKeyValue<long long> &aNode);
template long long _hash<int>(ABNodeKeyValue<int> &aNode);
template long long _hash<int *>(ABNodeKeyValue<int *> &aNode);
template long long _hash<ABEdge *>(ABNodeKeyValue<ABEdge *> &aNode);
template long long _hash<ABVertex *>(ABNodeKeyValue<ABVertex *> &aNode);

