//
//  ABUndirectedGraph.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-24.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABUndirectedGraph__
#define __workplace__ABUndirectedGraph__

#include "ABGraph.h"
#include "ABList.h"

class ABVertex;
class ABEdge;

class ABUndirectedGraph : public ABGraph
{
	ABList<ABVertex> *_vertecies;
	ABList<ABEdge> *_edges;
public:
	ABUndirectedGraph();
	~ABUndirectedGraph();
	
	ABList<ABVertex> &getVertecies();
	ABList<ABEdge> &getEdges();
	
	void loadGraph(const char *aFileName);
	void display();
};

void ABUndirectedGraphUnitTests(ABUndirectedGraph &aGraph);

#endif /* defined(__workplace__ABUndirectedGraph__) */
