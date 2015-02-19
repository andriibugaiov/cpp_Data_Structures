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
	const char *fileName = "/Users/andriibugaiov/My_Projects/Algorithms_DataStructures/cpp_Data_Structures/Graph/KargerMinCut.txt";
	
	ABGraph g;

	int minCut = INT32_MAX;
	int i;
	for (i = 0; i < 40; ++i)
 	{
		g.loadGraph(fileName);
//		ABGraphUnitTests(g);
		
		int result = g.minCutContractionAlgorithm();
		minCut = result < minCut ? result : minCut;
	}
	cout << minCut << endl;
	return 0;
}
