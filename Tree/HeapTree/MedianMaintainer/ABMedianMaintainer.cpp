//
//  ABMedianMaintainer.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-04.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABMedianMaintainer.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

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

long long ABMediansSumComputingAlgorithm(ABMedianMaintainer &aMedianMaintainer, const char *aFileName)
{
	ifstream filestream(aFileName);
	if(!filestream)
	{
		throw runtime_error("Failed to open file.");
	}
	
	long long sum = 0;
	int value;
	while (filestream >> value)
	{
		aMedianMaintainer.add(value);
		sum += aMedianMaintainer.getMedian();
	}
	filestream.close();
	
	return sum;
}
