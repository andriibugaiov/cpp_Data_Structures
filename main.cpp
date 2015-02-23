//
//  main.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include <iostream>

#include "ABGraph.h"


#define KOSARAJUS_TWO_PASS_ALGORITHM "/Users/andriibugaiov/My_Projects/Algorithms_DataStructures/cpp_Data_Structures/Graph/KosarajusTwoPassAlgorithm_StronglyConnectedComponentsSearch.txt"
#define BREADTH_FIRST_SEARCH_ALGORITHM "/Users/andriibugaiov/My_Projects/Algorithms_DataStructures/cpp_Data_Structures/Graph/BreadthFirstSearchAlgorithm.txt"
#define KARGER_CONTRACTION_ALGORITHM "/Users/andriibugaiov/My_Projects/Algorithms_DataStructures/cpp_Data_Structures/Graph/KargerContractionAlgorithm_MinCutSearch.txt"

using namespace std;

int main()
{
	ABGraph g;

#if 1
	const char *fileName = KOSARAJUS_TWO_PASS_ALGORITHM;
	g.loadGraph(fileName, ABGraphTypeDirected);
	g.runKosarajusTwoPassAlgorithm();
#endif
	
#if 0
	const char *fileName = BREADTH_FIRST_SEARCH_ALGORITHM;
	g.loadGraph(fileName, ABGraphTypeUndirected);
	ABGraphUnitTests(g);
	g.runBFSAlgorithmWithEntryVertexId(1);
#endif

#if 0
	const char *fileName = KARGER_CONTRACTION_ALGORITHM;
	int minCut = INT32_MAX;
	int i;
	for (i = 0; i < 40; ++i)
 	{
		g.loadGraph(fileName, ABGraphTypeUndirected);
		ABGraphUnitTests(g);
		
		int result = g.runKargerContractionAlgorithm();
		minCut = result < minCut ? result : minCut;
	}
	cout << minCut << endl;
#endif
	
	return 0;
}
