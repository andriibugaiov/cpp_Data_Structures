//
//  ABDirectedGraph.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-24.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABDirectedGraph.h"

#include "ABEdge.h"
#include "ABVertex.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

// TODO:
#define EDGES_NUMBER 5105043
#define VERTECIES_NUMBER 875714

ABDirectedGraph::ABDirectedGraph() : ABGraph(), _vertecies(nullptr), _edges(nullptr), _ordered_vertecies(nullptr)
{
}

ABDirectedGraph::~ABDirectedGraph()
{
	if (_vertecies != nullptr)
	{
		delete _vertecies;
	}
	if (_edges != nullptr)
	{
		delete _edges;
	}
	if (_ordered_vertecies != nullptr)
	{
		delete _ordered_vertecies;
	}
}

ABVector<ABVertex> &ABDirectedGraph::getVertecies()
{
	if (_vertecies == nullptr)
	{
		_vertecies = new ABVector<ABVertex>(VERTECIES_NUMBER);
	}
	return *_vertecies;
}

ABVector<ABEdge> &ABDirectedGraph::getEdges()
{
	if (_edges == nullptr)
	{
		_edges = new ABVector<ABEdge>(EDGES_NUMBER);
	}
	return *_edges;
}

ABList<ABVertex *> &ABDirectedGraph::getOrderedVertecies()
{
	if (_ordered_vertecies == nullptr)
	{
		_ordered_vertecies = new ABList<ABVertex *>();
	}
	return *_ordered_vertecies;
}

#pragma mark -

void ABDirectedGraph::loadGraph(const char *aFileName)
{
	ifstream filestream(aFileName);
	if(!filestream)
	{
		throw runtime_error("Failed to open file.");
	}
	
	getVertecies().clear();
	getVertecies().reserve(VERTECIES_NUMBER);

	getEdges().clear();
	getEdges().reserve(EDGES_NUMBER);
	
	
	int vertexId = -1;
	ABVertex *vertex = nullptr;
	
	string line;
	while (getline(filestream, line))
	{
		istringstream sstream(line);
		sstream >> vertexId;
		
		while (vertexId > getVertecies().getSize())
		{
			getVertecies().pushBack(ABVertex(getVertecies().getSize() + 1));
		}
		vertex = &getVertecies()[vertexId - 1];
		
		int adjacentVertexId;
		while (sstream >> adjacentVertexId)
		{
			ABVertex *adjacentVertex = nullptr;
			
			while (adjacentVertexId > getVertecies().getSize())
			{
				getVertecies().pushBack(ABVertex(getVertecies().getSize() + 1));
			}
			adjacentVertex = &getVertecies()[adjacentVertexId - 1];
			
			getEdges().pushBack(ABEdge(adjacentVertex /* head */, vertex /* tail */));
			ABEdge *edge = &getEdges().last();
			
			(*vertex).getEdges().pushBack(edge);
			(*adjacentVertex).getReversedEdges().pushBack(edge);
		}
	}
	filestream.close();
	
#if 1 // tests
	if (getVertecies().getSize() != VERTECIES_NUMBER ||
		getVertecies().getCapacity() != VERTECIES_NUMBER ||
		getEdges().getSize() != EDGES_NUMBER ||
		getEdges().getCapacity() != EDGES_NUMBER)
	{
		throw runtime_error("Test failed.");
	}
#endif
}

#pragma mark -

void ABDirectedGraph::display()
{
	// TODO:
}

#pragma mark - 

void ABDirectedGraphUnitTests(ABDirectedGraph &aGraph)
{
	// TODO:
}
