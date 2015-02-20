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

class ABVertex;
class ABEdge;

class ABGraph
{
	ABList<ABVertex> _vertecies;
	ABList<ABEdge> _edges;
	
	// algorithms helpers
	void contractVerteciesForEdge(ABEdge *anEdge);
	
public:
	ABList<ABVertex> &getVertecies();
	ABList<ABEdge> &getEdges();
	
	void loadGraph(const char *aFileName);
	void display();
	
	//algorithms
	int minCutContractionAlgorithm();
};

// TODO: implement adapter class
void ABGraphUnitTests(ABGraph &aGraph);

#endif /* defined(__workplace__ABGraph__) */
