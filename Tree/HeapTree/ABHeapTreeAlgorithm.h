//
//  ABHeapTreeAlgorithm.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-16.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#ifndef __workplace__ABHeapTreeAlgorithm__
#define __workplace__ABHeapTreeAlgorithm__

#include "ABHeapTree.h"

#include "ABVector.h"

#define MEDIAN_MAINTENANCE_PROBLEM "MedianMaintenanceProblem.txt"

class ABMedianMaintainer
{
    ABHeapTree<int> _max_heap;
    ABHeapTree<int> _min_heap;
public:
    void add(int aValue);
    int getMedian();
};

long long ABMediansSumComputingAlgorithm(ABMedianMaintainer &aMedianMaintainer, const char *aFileName);

#endif /* defined(__workplace__ABHeapTreeAlgorithm__) */
