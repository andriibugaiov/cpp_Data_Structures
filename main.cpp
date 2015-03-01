//
//  main.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include <iostream>

#include "ABUndirectedGraph.h"
#include "ABDirectedGraph.h"

#include "ABGraphAlgorithm.h"

#define KOSARAJUS_TWO_PASS_ALGORITHM "KosarajusTwoPassAlgorithm_StronglyConnectedComponentsSearch.txt"
#define BREADTH_FIRST_SEARCH_ALGORITHM "BreadthFirstSearchAlgorithm.txt"
#define KARGER_CONTRACTION_ALGORITHM "KargerContractionAlgorithm_MinCutSearch.txt"
#define DIJKSTRAS_SHORTEST_PATH_ALGORITHM "DijkstrasShortestPathAlgorithm.txt"

using namespace std;

int main()
{
#if 1
	ABUndirectedGraph g;
	const char *fileName = DIJKSTRAS_SHORTEST_PATH_ALGORITHM;
	g.loadGraph(fileName);
	ABUndirectedGraphUnitTests(g);
	ABDijkstrasShortestPathAlgorithm(g);
#endif
	
#if 0
	ABDirectedGraph g;
	const char *fileName = KOSARAJUS_TWO_PASS_ALGORITHM;
	g.loadGraph(fileName);
	ABKosarajusTwoPassAlgorithm(g);
#endif
	
#if 0
	ABUndirectedGraph g;
	const char *fileName = BREADTH_FIRST_SEARCH_ALGORITHM;
	g.loadGraph(fileName);
	ABUndirectedGraphUnitTests(g);
	ABBFSAlgorithmWithEntryVertex(g);
#endif

#if 0
	ABUndirectedGraph g;
	const char *fileName = KARGER_CONTRACTION_ALGORITHM;
	int minCutCrossingEdgesNumber = INT32_MAX;
	int i;
	for (i = 0; i < 40; ++i)
 	{
		g.loadGraph(fileName);
//		ABUndirectedGraphUnitTests(g);
		
		int result = ABKargerContractionAlgorithm(g);
		minCutCrossingEdgesNumber = result < minCutCrossingEdgesNumber ? result : minCutCrossingEdgesNumber;
	}
	cout << minCutCrossingEdgesNumber << endl;
#endif
	
	return 0;
}
