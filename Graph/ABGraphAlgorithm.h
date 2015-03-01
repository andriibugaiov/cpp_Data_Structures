//
//  ABGraphAlgorithm.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-25.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABGraphAlgorithm__
#define __workplace__ABGraphAlgorithm__

class ABVertex;
class ABEdge;
class ABUndirectedGraph;
class ABDirectedGraph;

#pragma mark - Depth First Search Algorithm

/*
	Explores graph vertecies digging into the graph.
 	Used as a preprocessing step in Kosarajus Two Pass Algorithm.
*/

void ABDFSOrderNumberAlgorithmWithEntryVertex(ABDirectedGraph &aGraph, ABVertex *aVertex = nullptr);

#pragma mark - Kosarajus Two Pass Algorithm

/* 
	Identifies strongly connceted components in directed graph.
 */
void ABKosarajusTwoPassAlgorithm(ABDirectedGraph &aGraph);

#pragma mark - Kargen Contraction Algorithm 

/*
	Identifies minimum cut in undirected graph.
*/
int ABKargerContractionAlgorithm(ABUndirectedGraph &aGraph);

#pragma mark - Breadth First Search Algorithm 

/*
	Explores graph vertecies in so called beadth layers.
 	Identifies the shortest path from a given vertex in undirected graph having weights of the edges equal to one.
*/
void ABBFSAlgorithmWithEntryVertex(ABUndirectedGraph &aGraph, ABVertex *aVertex = nullptr);

#pragma mark - Dijkstras Shortest Path Algorithm

/*
	Identifies all the shortest path from the given vertex.
 */
void ABDijkstrasShortestPathAlgorithm(ABUndirectedGraph &aGraph, ABVertex *aVertex = nullptr);

#endif /* defined(__workplace__ABGraphAlgorithm__) */
