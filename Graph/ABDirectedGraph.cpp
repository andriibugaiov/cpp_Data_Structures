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
		getEdges().getSize() != EDGES_NUMBER ||
		getVertecies().getCapacity() != VERTECIES_NUMBER ||
		getEdges().getCapacity() != EDGES_NUMBER)
	{
		throw runtime_error("Test failed.");
	}
#endif
}

#pragma mark -

static int dfs_order_number = 0;
static ABVertex *dfs_vertex_leader = nullptr;

void ABDirectedGraph::runDFSAlgorithmWithEntryVertexTEMP(ABVertex *aVertex)
{
#if 1
	ABList<ABVertex *> stack;

	ABVertex *pairedVertex = nullptr;
	ABVertex *vertex = aVertex;
	(*vertex).setDFSOrderNumber(0);
	stack.pushBack(vertex);

	while (!stack.isEmpty())
	{
		vertex = stack.back();
		stack.popBack();

		ABList<ABEdge *>::ABIterator pEdgeListIterator;
		for (pEdgeListIterator = (*vertex).getReversedEdges().begin(); pEdgeListIterator != (*vertex).getReversedEdges().end(); ++pEdgeListIterator)
		{
			// traverse graph in reversed order
			pairedVertex = (*(*pEdgeListIterator)).getTail();
			if (!(*pairedVertex).isExploredDFS())
			{
				(*pairedVertex).setDFSOrderNumber(0);
				stack.pushBack(pairedVertex);
			}
		}
	}
#else
	(*aVertex).setDFSOrderNumber(0);
	
	for (ABList<ABEdge *>::ABIterator pEdgeListIterator = (*aVertex).getReversedEdges().begin(); pEdgeListIterator != (*aVertex).getReversedEdges().end(); ++pEdgeListIterator)
	{
		// traverse graph in reversed order
		ABVertex *tail = (*(*pEdgeListIterator)).getTail();
		if (!(*tail).isExploredDFS())
		{
			runDFSAlgorithmWithEntryVertexTEMP(tail);
		}
	}
	
	++dfs_order_number;
	(*aVertex).setDFSOrderNumber(dfs_order_number);
	getOrderedVertecies().pushFront(aVertex);
#endif
}

void ABDirectedGraph::runDFSAlgorithmWithEntryVertex(ABVertex *aVertex)
{
	ABList<ABVertex *> stack;
	
	ABVertex *pairedVertex = nullptr;
	ABVertex *vertex = aVertex;
	(*vertex).setDFSVertexLeader(dfs_vertex_leader);
	stack.pushBack(vertex);
	
	while (!stack.isEmpty())
	{
		vertex = stack.back();
		stack.popBack();
		
		ABList<ABEdge *>::ABIterator pEdgeListIterator;
		for (pEdgeListIterator = (*vertex).getEdges().begin(); pEdgeListIterator != (*vertex).getEdges().end(); ++pEdgeListIterator)
		{
			pairedVertex = (*(*pEdgeListIterator)).getHead();
			if (!(*pairedVertex).isExploredDFSVertexLeader())
			{
				(*pairedVertex).setDFSVertexLeader(dfs_vertex_leader);
				stack.pushBack(pairedVertex);
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
			runDFSAlgorithmWithEntryVertexTEMP(&(*vertexVectorIterator));
		}
	}
#else
	for (int i = getVertecies().getSize() - 1; i >= 0; --i)
	{
		ABVertex *vetrex = &getVertecies()[i];
		if (!(*vetrex).isExploredDFS())
		{
			runDFSAlgorithmWithEntryVertexTEMP(vetrex);
		}
	}
#endif
	
#if 1 // tests
	ABList<ABVertex *>::ABIterator pVertexListIterator = getOrderedVertecies().begin();
	++pVertexListIterator;
	for (; pVertexListIterator != getOrderedVertecies().end(); ++pVertexListIterator)
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
	
	if (getOrderedVertecies().getSize() != VERTECIES_NUMBER ||
		dfs_order_number != VERTECIES_NUMBER ||
		(*getOrderedVertecies().front()).getDFSOrderNumber() != VERTECIES_NUMBER ||
		(*getOrderedVertecies().back()).getDFSOrderNumber() != 1)
	{
		throw runtime_error("Test failed.");
	}
#endif
}

#pragma mark -

void ABDirectedGraph::findStronglyConnectedComponents()
{
	ABList<ABVertex *>::ABIterator pVertexListIterator;
	for (pVertexListIterator = getOrderedVertecies().begin(); pVertexListIterator != getOrderedVertecies().end();)
	{
		if (!(*(*pVertexListIterator)).isExploredDFSVertexLeader())
		{
			dfs_vertex_leader = *pVertexListIterator;
			runDFSAlgorithmWithEntryVertex(*pVertexListIterator);
		}
		pVertexListIterator = getOrderedVertecies().remove(pVertexListIterator);
	}
	
	ABVector<ABVertex>::ABIterator vertexVectorIterator;
	for (vertexVectorIterator = getVertecies().begin(); vertexVectorIterator != getVertecies().end(); ++vertexVectorIterator)
	{
		++(*(*vertexVectorIterator).getDFSVertexLeader())._entryCount;
	}
	
	// TODO:
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
	dfs_vertex_leader = nullptr;
	
	// "1st pass"
	orderVerteciesInReversedGraph();
	
	// "2nd pass"
	findStronglyConnectedComponents();
}

#pragma mark -

void ABDirectedGraph::display()
{
}

#pragma mark - 

void ABDirectedGraphUnitTests(ABDirectedGraph &aGraph)
{
}
