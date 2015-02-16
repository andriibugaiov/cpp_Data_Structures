//
//  ABNode.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABNode.h"

#include "ABEdge.h"

template <typename T>
ABNode<T>::ABNode()
{
	
}

template <typename T>
ABNode<T>::ABNode(const T &aData) : _data(aData)
{
}

template <typename T>
T & ABNode<T>::getData()
{
	return _data;
}

#pragma mark -

template class ABNode<int>;
template class ABNode<int *>;
template class ABNode<ABEdge *>;

