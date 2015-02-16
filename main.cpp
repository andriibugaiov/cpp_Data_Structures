//
//  main.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include <iostream>

#include "ABGraph.h"

using namespace std;

int main()
{
	ABGraphUnitTests();
	
	int minCut = INT32_MAX;
	int i;
	for (i = 0; i < 4000; ++i)
 	{
		ABGraph g;
		g.loadGraph();
		
		int result = g.minCutContractionAlgorithm();
		minCut = result < minCut ? result : minCut;
	}
	cout << minCut << endl;
	
	return 0;
}
