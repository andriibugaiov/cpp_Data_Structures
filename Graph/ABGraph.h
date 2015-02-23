//
//  ABGraph.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABGraph__
#define __workplace__ABGraph__

#include "ABList.h"
#include "ABVector.h"

typedef enum {
	ABGraphTypeNone,
	ABGraphTypeUndirected,
	ABGraphTypeDirected
} ABGraphType;

class ABVertex;
class ABEdge;

// TODO: rework ABGraph architecture
class ABGraph
{
	ABGraphType _graph_type;
	
	ABList<ABVertex> *_vertecies; // undirected
	ABList<ABEdge> *_edges; // undirected
	
	// algorithms helpers
	void loadUndirectedGraph(const char *aFileName); // undirected
	void loadDirectedGraph(const char *aFileName); // directed
	
	void contractVerteciesForEdge(ABEdge *anEdge); // undirected
	void runBFSAlgorithmWithEntryVertex(ABVertex *aVertex); // undirected

	void runDFSAlgorithmWithEntryVertex(ABVertex *aVertex); // directed
	void runOrderingDFSAlgorithmWithEntryVertex(ABVertex *aVertex); // directed
	void orderVerteciesInReversedGraph(); // directed
	void findStronglyConnectedComponents(); // directed
public:
	ABVector<ABVertex> *__vertecies; // directed
	ABList<ABVertex *> *__orderedVertecies; // directed
	ABVector<ABEdge> *__edges; // directed
	
	ABGraph();
	~ABGraph();
	
	ABGraphType getGraphType();
	
	ABList<ABVertex> &getVertecies(); // undirected
	ABList<ABEdge> &getEdges(); // undirected
	
	void loadGraph(const char *aFileName, ABGraphType aGraphType);
	void display(); // undirected
	
	//algorithms
	int runKargerContractionAlgorithm(); // undirected
	void runBFSAlgorithmWithEntryVertexId(int aVertexId); // undirected
	
	void runKosarajusTwoPassAlgorithm(); // directed
};

// TODO: implement adapter class
void ABGraphUnitTests(ABGraph &aGraph);// undirected, directed

#endif /* defined(__workplace__ABGraph__) */
