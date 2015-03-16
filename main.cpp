//
//  main.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include <iostream>

#include "ABGraphAlgorithm.h"
#include "ABUndirectedGraph.h"

#include "ABHeapTreeAlgorithm.h"
#include "ABHeapTree.h"

#include "ABHashTableAlgorithm.h"
#include "ABHashTable.h"

using namespace std;

int main()
{
    
#if 0
    ABUndirectedGraph g;
    const char *fileName = DIJKSTRAS_SHORTEST_PATH_ALGORITHM;
    g.loadGraph(fileName);
    ABDijkstrasShortestPathAlgorithm(g);
#endif
    
	ABMedianMaintainer mm;
	const char *fileName = MEDIAN_MAINTENANCE_PROBLEM;
	long long mediansSum = ABMediansSumComputingAlgorithm(mm, fileName);
	cout << "The sum of the medians modulo 10000 is - " << mediansSum % 10000 << endl;
	
	fileName = TWO_SUM_PROBLEM;
	int counter = ABTwoSumComputingAlgorithm(fileName);
	cout << "The two-sum count is - " << counter << endl;
	
	return 0;
}
