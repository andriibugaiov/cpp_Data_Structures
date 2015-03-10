//
//  ABHeapTree.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-27.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#include "ABHeapTree.h"

#include "ABVector.h"
#include "ABNodeKeyValue.h"

#include "ABVertex.h"
#include "ABEdge.h"

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
void ABHeapTree<T>::percolateUp(int anIndex)
{
    ABNodeKeyValue<T> node = _vector[anIndex];
    int indexHole = anIndex;
    while ((indexHole / 2) != 0 && node < _vector[indexHole / 2])
    {
        _vector[indexHole] = _vector[indexHole / 2];
        indexHole = indexHole / 2;
    }
    _vector[indexHole] = node;
}

template <typename T>
void ABHeapTree<T>::percolateDown(int anIndex)
{
    if (anIndex > getSize())
    {
        return;
    }
    
    ABNodeKeyValue<T> node = _vector[anIndex];
    int indexHole = anIndex;
    int indexChild = 2 * indexHole;
    while (indexChild <= getSize())
    {
        if ((indexChild + 1) <= getSize() && _vector[indexChild + 1] < _vector[indexChild])
        {
            ++indexChild;
        }
        
        if (_vector[indexChild] < node)
        {
            _vector[indexHole] = _vector[indexChild];
        }
        else
        {
            break;
        }
        indexHole = indexChild;
        indexChild = 2 * indexHole;
    }
    _vector[indexHole] = node;
}

#pragma mark -

template <typename T>
ABHeapTree<T>::ABHeapTree()
{
    ABNodeKeyValue<T> emptyNode;
    _vector.pushBack(emptyNode);
}

template <typename T>
ABHeapTree<T>::ABHeapTree(ABVector<T> aData)
{
	ABNodeKeyValue<T> emptyNode;
	_vector.pushBack(emptyNode);
	
	// TODO:
}

template <typename T>
void ABHeapTree<T>::clear()
{
	_vector.clear();
	ABNodeKeyValue<T> emptyNode;
	_vector.pushBack(emptyNode);
}

template <typename T>
int ABHeapTree<T>::getSize() const
{
    return _vector.getSize() - 1;
}

template <typename T>
bool ABHeapTree<T>::isEmpty() const
{
    return getSize() == 0;
}

template <typename T>
void ABHeapTree<T>::insert(const T &aData, int aKey)
{
    ABNodeKeyValue<T> node(aData, aKey);
    _vector.pushBack(node);
    percolateUp(getSize());
}

template <typename T>
T ABHeapTree<T>::removeRoot(int *oaKey)
{
    if (isEmpty())
    {
        throw runtime_error("Tree is empty!");
    }
    
    ABNodeKeyValue<T> node = _vector[1];
    _vector[1] = _vector[getSize()];
    _vector[getSize()] = node;
    
    node = _vector.popBack();
    percolateDown(1);
    
    if (oaKey != nullptr)
    {
        *oaKey = node.getKey();
    }
    return node.getData();
}

template <typename T>
const T &ABHeapTree<T>::lookUpRoot(int *oaKey) const
{
	if (isEmpty())
	{
		throw runtime_error("Tree is empty!");
	}
    
    if (oaKey != nullptr)
    {
        *oaKey = _vector[1].getKey();
    }
	return _vector[1].getData();
}

#pragma make -

template <typename T>
int ABHeapTree<T>::search(const T &aData)
{
	int i;
	for (i = 1; i <= getSize(); ++i)
	{
		if (_vector[i].getData() == aData)
		{
			break;
		}
	}
	return i;
}

template <typename T>
void ABHeapTree<T>::increaseKey(const T &aData, int aDelta)
{
	int i = search(aData);
	if (i <= getSize())
	{
		_vector[i].setKey(_vector[i].getKey() + aDelta);
		percolateDown(i);
	}
}

template <typename T>
void ABHeapTree<T>::decreaseKey(const T &aData, int aDelta)
{
	int i = search(aData);
	if (i <= getSize())
	{
		_vector[i].setKey(_vector[i].getKey() - aDelta);
		percolateUp(i);
	}
}

#pragma mark -

template class ABHeapTree<int>;
template class ABHeapTree<int *>;
template class ABHeapTree<ABEdge *>;
template class ABHeapTree<ABVertex *>;

#pragma mark -

template <typename T>
void ABHeapTreeUnitTests(ABHeapTree<T> &aTree)
{
}
