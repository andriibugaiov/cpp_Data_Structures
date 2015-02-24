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
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

#define EDGES_NUMBER 5105043
#define VERTECIES_NUMBER 875714

ABDirectedGraph::ABDirectedGraph() : ABGraph(), _vertecies(nullptr), _edges(nullptr)
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
	if (getVertecies().getSize() != VERTECIES_NUMBER || getEdges().getSize() != EDGES_NUMBER ||
		getVertecies().getCapacity() != VERTECIES_NUMBER || getEdges().getCapacity() != EDGES_NUMBER)
	{
		throw runtime_error("Test failed.");
	}
#endif
}

#pragma mark -

static int dfs_order_number = 0;
static ABVertex *dfs_vertex_leader = nullptr;
static ABList<ABVertex *> *ordered_vertecies = nullptr;

void ABDirectedGraph::runDFSAlgorithmWithEntryVertex(ABVertex *aVertex)
{
	if (dfs_vertex_leader == nullptr)
	{
		// just to let others know that the vertex has been explored
		// but the order number has not been assigned yet
		(*aVertex).setDFSOrderNumber(0);
		
		for (ABList<ABEdge *>::ABIterator pEdgeListIterator = (*aVertex).getReversedEdges().begin(); pEdgeListIterator != (*aVertex).getReversedEdges().end(); ++pEdgeListIterator)
		{
			if ((*(*pEdgeListIterator)).getHead() != aVertex)
			{
				throw runtime_error("Test failed.");
			}
			
			// traverse graph in reversed order
			ABVertex *tail = (*(*pEdgeListIterator)).getTail();
			if (!(*tail).isExploredDFS())
			{
				runDFSAlgorithmWithEntryVertex(tail);
			}
		}
		
		++dfs_order_number;
		(*aVertex).setDFSOrderNumber(dfs_order_number);
		(*ordered_vertecies).pushFront(aVertex);
	}
	else
	{
		(*aVertex).setDFSVertexLeader(dfs_vertex_leader);
		
		for (ABList<ABEdge *>::ABIterator pEdgeListIterator = (*aVertex).getEdges().begin(); pEdgeListIterator != (*aVertex).getEdges().end(); ++pEdgeListIterator)
		{
			ABVertex *head = (*(*pEdgeListIterator)).getHead();
			if (!(*head).isExploredDFSVertexLeader())
			{
				runDFSAlgorithmWithEntryVertex(head);
			}
		}
	}
}

#pragma mark -

void ABDirectedGraph::orderVerteciesInReversedGraph()
{
#if 1
	ABVector<ABVertex>::ABIterator vertexVectorIterator;
	for (vertexVectorIterator = getVertecies().begin(); vertexVectorIterator != getVertecies().end(); ++vertexVectorIterator)
	{
		if (!(*vertexVectorIterator).isExploredDFS())
		{
			runDFSAlgorithmWithEntryVertex(&(*vertexVectorIterator));
		}
	}
#else
	for (int i = getVertecies().getSize() - 1; i >= 0; --i)
	{
		ABVertex *vetrex = &getVertecies()[i];
		if (!(*vetrex).isExploredDFS())
		{
			runOrderingDFSAlgorithmWithEntryVertex(vetrex);
		}
	}
#endif
	
#if 1 // tests
	ABList<ABVertex *>::ABIterator pVertexListIterator = (*ordered_vertecies).begin();
	++pVertexListIterator;
	for (; pVertexListIterator != (*ordered_vertecies).end(); ++pVertexListIterator)
	{
		--pVertexListIterator;
		if (!(*(*pVertexListIterator)).isExploredDFS())
		{
			throw runtime_error("Test failed.");
		}
		int orderNumberPrevious = (*(*pVertexListIterator)).getDFSOrderNumber();
		
		++pVertexListIterator;
		if (!(*(*pVertexListIterator)).isExploredDFS())
		{
			throw runtime_error("Test failed.");
		}
		int orderNumberNext = (*(*pVertexListIterator)).getDFSOrderNumber();
		
		if (orderNumberPrevious != orderNumberNext + 1)
		{
			throw runtime_error("Test failed.");
		}
	}
	
	if ((*ordered_vertecies).getSize() != VERTECIES_NUMBER || dfs_order_number != VERTECIES_NUMBER ||
		(*(*ordered_vertecies).front()).getDFSOrderNumber() != VERTECIES_NUMBER ||
		(*(*ordered_vertecies).back()).getDFSOrderNumber() != 1)
	{
		throw runtime_error("Test failed.");
	}
#endif
}

#pragma mark -

void ABDirectedGraph::findStronglyConnectedComponents()
{
	ABList<ABVertex *>::ABIterator pVertexListIterator;
	for (pVertexListIterator = (*ordered_vertecies).begin(); pVertexListIterator != (*ordered_vertecies).end();)
	{
		if (!(*(*pVertexListIterator)).isExploredDFSVertexLeader())
		{
			dfs_vertex_leader = *pVertexListIterator;
			runDFSAlgorithmWithEntryVertex(*pVertexListIterator);
		}
		pVertexListIterator = (*ordered_vertecies).remove(pVertexListIterator);
	}
	
	ABVector<ABVertex>::ABIterator vertexVectorIterator;
	
#if 1 // tests
	for (vertexVectorIterator = getVertecies().begin(); vertexVectorIterator != getVertecies().end(); ++vertexVectorIterator)
	{
		if (!(*vertexVectorIterator).isExploredDFSVertexLeader())
		{
			throw runtime_error("Test failed.");
		}
	}
#endif
	
	for (vertexVectorIterator = getVertecies().begin(); vertexVectorIterator != getVertecies().end(); ++vertexVectorIterator)
	{
		++(*(*vertexVectorIterator).getDFSVertexLeader())._entryCount;
	}
	
	
	int max_scc_count[5] = {0};
	
	for (vertexVectorIterator = getVertecies().begin(); vertexVectorIterator != getVertecies().end(); ++vertexVectorIterator)
	{
		int entryCount = (*vertexVectorIterator)._entryCount;
		for (int i = 0; i < 5; ++i)
		{
			if (entryCount > max_scc_count[i])
			{
				for (int j = 3; j >= i; --j)
				{
					max_scc_count[j + 1] = max_scc_count[j];
				}
				max_scc_count[i] = entryCount;
				break;
			}
		}
	}
	
	for (int i = 0; i < 5; ++i)
	{
		cout << max_scc_count[i] << ",";
	}
	cout << endl;
}

void ABDirectedGraph::runKosarajusTwoPassAlgorithm()
{
	dfs_order_number = 0;
	if (ordered_vertecies == nullptr)
	{
		ordered_vertecies = new ABList<ABVertex *>();
	}
	dfs_vertex_leader = nullptr;
	
	// "1st pass"
	orderVerteciesInReversedGraph();
	
	// "2nd pass"
	findStronglyConnectedComponents();
	
	dfs_order_number = 0;
	delete ordered_vertecies;
	ordered_vertecies = nullptr;
	dfs_vertex_leader = nullptr;
}

#pragma mark -

void ABDirectedGraph::display()
{
}

#pragma mark - 

void ABDirectedGraphUnitTests(ABDirectedGraph &aGraph)
{
}
