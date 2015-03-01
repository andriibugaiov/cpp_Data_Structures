//
//  ABDirectedGraph.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-24.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABDirectedGraph__
#define __workplace__ABDirectedGraph__

#include "ABGraph.h"
#include "ABList.h"
#include "ABVector.h"

class ABVertex;
class ABEdge;

class ABDirectedGraph : public ABGraph
{
	ABVector<ABVertex> *_vertecies;
	ABVector<ABEdge> *_edges;
	ABList<ABVertex *> *_ordered_vertecies;
public:
	
	ABDirectedGraph();
	~ABDirectedGraph();
	
	ABVector<ABVertex> &getVertecies();
	ABVector<ABEdge> &getEdges();
	ABList<ABVertex *> &getOrderedVertecies();
	
	void loadGraph(const char *aFileName);
	void display();
	
	friend void ABDirectedGraphUnitTests(ABDirectedGraph &aGraph);
};

#endif /* defined(__workplace__ABDirectedGraph__) */
