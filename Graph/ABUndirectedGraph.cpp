//
//  ABUndirectedGraph.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-24.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABUndirectedGraph.h"

#include "ABEdge.h"
#include "ABVertex.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

ABUndirectedGraph::ABUndirectedGraph() : ABGraph(), _edges(nullptr), _vertecies(nullptr)
{	
}

ABUndirectedGraph::~ABUndirectedGraph()
{
	if (_vertecies != nullptr)
	{
		delete _vertecies;
	}
	if (_edges != nullptr)
	{
		delete _edges;
	}
}

ABList<ABVertex> &ABUndirectedGraph::getVertecies()
{
	if (_vertecies == nullptr)
	{
		_vertecies = new ABList<ABVertex>();
	}
	return *_vertecies;
}

ABList<ABEdge> &ABUndirectedGraph::getEdges()
{
	if (_edges == nullptr)
	{
		_edges = new ABList<ABEdge>();
	}
	return *_edges;
}

#pragma mark -

void ABUndirectedGraph::loadGraph(const char *aFileName)
{
	ifstream filestream(aFileName);
	if(!filestream)
	{
		throw runtime_error("Failed to open file.");
	}
	
	getVertecies().clear();
	getEdges().clear();
	
	int vertexId = -1;
	ABVertex *vertex = nullptr;
	
	string line;
	while (getline(filestream, line))
	{
		istringstream sstream(line);
		int vertexIdTemp;
		sstream >> vertexIdTemp;
		
		if (vertexId != vertexIdTemp)
		{
			vertexId = vertexIdTemp;
			vertex = nullptr;
		}
		
		if (!vertex)
		{
			// TODO:
			// { List search
			ABList<ABVertex>::ABIterator vertexListIterator;
			for (vertexListIterator = getVertecies().begin(); vertexListIterator != getVertecies().end(); ++vertexListIterator)
			{
				if ((*vertexListIterator).getVertexId() == vertexId)
				{
					vertex = &(*vertexListIterator);
					break;
				}
			}
			// }
		}
		
		if (!vertex)
		{
			getVertecies().pushBack(ABVertex(vertexId));
			vertex = &getVertecies().back();
		}
		
		int adjacentVertexId;
		while (sstream >> adjacentVertexId)
		{
			ABVertex *adjacentVertex = nullptr;
			
			// { List search
			ABList<ABVertex>::ABIterator vertexListIterator;
			for (vertexListIterator = getVertecies().begin(); vertexListIterator != getVertecies().end(); ++vertexListIterator)
			{
				if ((*vertexListIterator).getVertexId() == adjacentVertexId)
				{
					adjacentVertex = &(*vertexListIterator);
					break;
				}
			}
			// }
			
			if (!adjacentVertex)
			{
				getVertecies().pushBack(ABVertex(adjacentVertexId));
				adjacentVertex = &getVertecies().back();
			}
			
			
			ABEdge *edge = nullptr;
			
			// { list search
			ABList<ABEdge *>::ABIterator pEdgeListIteratorI;
			for (pEdgeListIteratorI = (*adjacentVertex).getEdges().begin(); pEdgeListIteratorI != (*adjacentVertex).getEdges().end(); ++pEdgeListIteratorI)
			{
				if ((*(*pEdgeListIteratorI)).getTail() == vertex)
				{
					edge = *pEdgeListIteratorI;
					break;
				}
			}
			// }
			
			if (!edge)
			{
				getEdges().pushBack(ABEdge(vertex, adjacentVertex));
				edge = &getEdges().back();
			}
			
			(*vertex).getEdges().pushBack(edge);
		}
	}
	
	filestream.close();
}

#pragma mark -

void ABUndirectedGraph::display()
{
	ABList<ABVertex>::ABIterator vertexListIterator;
	for (vertexListIterator = getVertecies().begin(); vertexListIterator != getVertecies().end(); ++vertexListIterator)
	{
		cout << (*vertexListIterator).getVertexId() << " - ";
		ABList<ABEdge *>::ABIterator lI;
		for (lI = (*vertexListIterator).getEdges().begin(); lI != (*vertexListIterator).getEdges().end(); ++lI)
		{
			ABEdge *edge = *lI;
			cout << " (" << (*(*edge).getHead()).getVertexId() << ", " << (*(*edge).getTail()).getVertexId() << ") ";
		}
		cout << endl;
	}
}

#pragma mark - 

void ABUndirectedGraphUnitTests(ABUndirectedGraph &aGraph)
{
	ABList<ABVertex>::ABIterator vertexListIterator;
	ABList<ABEdge>::ABIterator edgeListIterator;
	
	for (vertexListIterator = aGraph.getVertecies().begin(); vertexListIterator != aGraph.getVertecies().end(); ++vertexListIterator)
	{
		ABList<ABEdge *>::ABIterator pEdgeListIterator;
		for (pEdgeListIterator = (*vertexListIterator).getEdges().begin(); pEdgeListIterator != (*vertexListIterator).getEdges().end(); ++pEdgeListIterator)
		{
			for (edgeListIterator = aGraph.getEdges().begin(); edgeListIterator != aGraph.getEdges().end(); ++edgeListIterator)
			{
				if (*pEdgeListIterator == &(*edgeListIterator) &&
					(*(*pEdgeListIterator)).getHead() == (*edgeListIterator).getHead() &&
					(*(*pEdgeListIterator)).getTail() == (*edgeListIterator).getTail() &&
					((*edgeListIterator).getHead() == &(*vertexListIterator) ||
					 (*edgeListIterator).getTail() == &(*vertexListIterator)))
				{
					(*edgeListIterator)._counter++;
					
					if ((*edgeListIterator).getHead() == &(*vertexListIterator))
					{
						++(*(*edgeListIterator).getTail())._counter;
					}
					else if ((*edgeListIterator).getTail() == &(*vertexListIterator))
					{
						++(*(*edgeListIterator).getHead())._counter;
					}
				}
			}
		}
	}
	
	for (edgeListIterator = aGraph.getEdges().begin(); edgeListIterator != aGraph.getEdges().end(); ++edgeListIterator)
	{
		if ((*edgeListIterator)._counter != 2)
		{
			throw runtime_error("Test failed.");
		}
	}
	
	for (vertexListIterator = aGraph.getVertecies().begin(); vertexListIterator != aGraph.getVertecies().end(); ++vertexListIterator)
	{
		if ((*vertexListIterator).getEdges().getSize() != (*vertexListIterator)._counter)
		{
			throw runtime_error("Test failed.");
		}
	}
}
