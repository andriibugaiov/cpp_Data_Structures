//
//  ABGraph.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABGraph.h"

void ABGraphUnitTests()
{
	ABGraph g;
	g.loadGraph();
	g.display();

	ABVector<ABVertex>::ABIterator vI;
	ABVector<ABEdge>::ABIterator vEdgeI;

	for (vI = g._vertecies.begin(); vI != g._vertecies.end(); ++vI)
	{
		ABList<ABEdge *>::ABIterator lI;
		for (lI = (*vI)._edges.begin(); lI != (*vI)._edges.end(); ++lI)
		{
			for (vEdgeI = g._edges.begin(); vEdgeI != g._edges.end(); ++vEdgeI)
			{
				if (*lI == vEdgeI &&
					(*(*lI))._head == (*vEdgeI)._head &&
					(*(*lI))._tail == (*vEdgeI)._tail &&
					((*vEdgeI)._head == vI || (*vEdgeI)._tail == vI))
				{
					(*vEdgeI)._entryCount++;
					
					if ((*vEdgeI)._head == vI)
					{
						++(*(*vEdgeI)._tail)._entryCount;
					}
					else if ((*vEdgeI)._tail == vI)
					{
						++(*(*vEdgeI)._head)._entryCount;
					}
				}
			}
		}
	}
	
	for (vEdgeI = g._edges.begin(); vEdgeI != g._edges.end(); ++vEdgeI)
	{
		if ((*vEdgeI)._entryCount != 2)
		{
			throw runtime_error("Test failed.");
		}
	}
	
	for (vI = g._vertecies.begin(); vI != g._vertecies.end(); ++vI)
	{
		if ((*vI)._edges.getSize() != (*vI)._entryCount)
		{
			throw runtime_error("Test failed.");
		}
	}
}
