//
//  ABHeapTree.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-27.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#include "ABHeapTree.h"
#include "ABVector.h"
#include "ABNodeHeapTree.h"
#include "ABNode.h"

#include "ABVertex.h"
#include "ABEdge.h"

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
void ABHeapTree<T>::percolateUp(int anIndex)
{
    ABNodeHeapTree<T> node = _vector[anIndex];
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
    
    ABNodeHeapTree<T> node = _vector[anIndex];
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
    ABNodeHeapTree<T> emptyNode;
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
    ABNodeHeapTree<T> node(aData, aKey);
    _vector.pushBack(node);
    percolateUp(getSize());
}

template <typename T>
T ABHeapTree<T>::removeRoot()
{
    if (isEmpty())
    {
        throw runtime_error("Tree is empty!");
    }
    
    ABNodeHeapTree<T> node = _vector[1];
    _vector[1] = _vector[getSize()];
    _vector[getSize()] = node;
    
    node = _vector.popBack();
    percolateDown(1);
    return node.getData();
}

template <typename T>
ABNodeHeapTree<T> ABHeapTree<T>::removeRootNode()
{
	if (isEmpty())
	{
		throw runtime_error("Tree is empty!");
	}
	
	ABNodeHeapTree<T> node = _vector[1];
	_vector[1] = _vector[getSize()];
	_vector[getSize()] = node;
	
	node = _vector.popBack();
	percolateDown(1);
	return node;
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
template class ABHeapTree<ABEdge>;
template class ABHeapTree<ABVertex *>;
template class ABHeapTree<ABVertex>;

#pragma mark -

void ABHeapTreeUnitTests(ABHeapTree<int> &aTree)
{
	int i;
	for (i = 0; i < 100; ++i)
	{
		int key = rand() % 100;
		int data = i;
		aTree.insert(data, key);
	}
	
	ABNodeHeapTree<int> dataNode = aTree.removeRootNode();
	for (i = 0; i < 99; ++i)
	{
		ABNodeHeapTree<int> nextDataNode = aTree.removeRootNode();
		if (dataNode.getKey() > nextDataNode.getKey())
		{
			throw runtime_error("Test fail!");
		}
		dataNode = nextDataNode;
	}
}
