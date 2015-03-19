//
//  ABHeapTreeAlgorithm.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-16.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#include "ABHeapTreeAlgorithm.h"

#include "ABTimer.h"
#include <stdlib.h>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

class ABMedianMaintainer
{
	ABHeapTree<int> _max_heap;
	ABHeapTree<int> _min_heap;
public:
	void add(int aValue);
	int getMedian();
};

void ABMedianMaintainer::add(int aValue)
{
    if (_min_heap.isEmpty())
    {
        _min_heap.insert(aValue, aValue);
        return;
    }
    
    if (aValue > _min_heap.lookUpRoot())
    {
        _min_heap.insert(aValue, aValue);
    }
    else
    {
        _max_heap.insert(aValue, -aValue);
    }
    
    if (_min_heap.getSize() - _max_heap.getSize() > 1)
    {
        int value = _min_heap.removeRoot();
        _max_heap.insert(value, -value);
    }
    else if (_min_heap.getSize() - _max_heap.getSize() < -1)
    {
        int value = _max_heap.removeRoot();
        _min_heap.insert(value, value);
    }
}

int ABMedianMaintainer::getMedian()
{
    if (_min_heap.isEmpty() && _max_heap.isEmpty())
    {
        throw runtime_error("Heaps are empty!");
    }
    
    if (_min_heap.getSize() > _max_heap.getSize())
    {
        return _min_heap.lookUpRoot();
    }
    else
    {
        return _max_heap.lookUpRoot();
    }
    return 0;
}

#pragma mark -

long long ABMediansSumComputingAlgorithm(const char *aFileName)
{
    ifstream filestream(aFileName);
    if(!filestream)
    {
        throw runtime_error("Failed to open file.");
    }
	
	ABMedianMaintainer medianMaintainer;
    
    long long sum = 0;
    int value;
    while (filestream >> value)
    {
        medianMaintainer.add(value);
        sum += medianMaintainer.getMedian();
    }
    filestream.close();
    
    return sum;
}

#pragma mark -

void ABHeapStructureTest(ABHeapTree<int> &aHeap);
void ABHeapStructureTest(ABHeapTree<int> &aHeap)
{
	int value = aHeap.removeRoot();
	while (!aHeap.isEmpty())
	{
		int newValue = aHeap.removeRoot();
		if (newValue < value)
		{
			throw runtime_error("Heap is broken.");
		}
		value = newValue;
	}
}

void ABLinearHeapify(void *aVector);
void ABLinearHeapify(void *aVector)
{
	ABVector<int> *pV = (ABVector<int> *)aVector;
	ABHeapTree<int> h(*pV, *pV);
	
//	ABHeapStructureTest(h);
}

void ABHeapify(void *aVector);
void ABHeapify(void *aVector)
{
	ABVector<int> *pV = (ABVector<int> *)aVector;
	ABHeapTree<int> h((*pV).getSize());
	
	ABVector<int>::ABIterator iV = (*pV).begin();
	for (; iV != (*pV).end(); ++iV)
	{
		h.insert(*iV, *iV);
	}
	
//	ABHeapStructureTest(h);
}

#define N 50000000

void ABLinearHeapifyAlgorithm(const char *aFileName)
{
#if 0
	ifstream filestream(aFileName);
	if(!filestream)
	{
		throw runtime_error("Failed to open file.");
	}
	
	ABVector<int> v;
	int value;
	while (filestream >> value)
	{
		v.pushBack(value);
	}
	filestream.close();
#else
	srand((unsigned)time(NULL));
	
	ABVector<int> v(N);
	int i = 0;
	for (; i < N; ++i)
	{
		int value = N - i;
		v.pushBack(value);
	}
#endif
	ABTimer(ABLinearHeapify, &v);
	ABTimer(ABHeapify, &v);

}
