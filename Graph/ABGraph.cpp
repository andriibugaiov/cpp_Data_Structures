//
//  ABGraph.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABGraph.h"

#include "ABEdge.h"
#include "ABVertex.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "time.h"

#define EDGES_NUMBER 5105043
#define VERTECIES_NUMBER 875714

using namespace std;

ABGraphType ABGraph::getGraphType()
{
	return _graph_type;
}

ABList<ABVertex> &ABGraph::getVertecies()
{
	return *_vertecies;
}

ABList<ABEdge> &ABGraph::getEdges()
{
	return *_edges;
}

ABGraph::ABGraph() : _graph_type(ABGraphTypeNone), _edges(nullptr), _vertecies(nullptr), __vertecies(nullptr), __orderedVertecies(nullptr), __edges(nullptr)
{
}

ABGraph::~ABGraph()
{
	if (_vertecies != nullptr)
	{
		delete _vertecies;
	}
	if (_edges != nullptr)
	{
		delete _edges;
	}
	
	if (__vertecies != nullptr)
	{
		delete __vertecies;
	}
	if (__orderedVertecies != nullptr)
	{
		delete __orderedVertecies;
	}
	if (__edges != nullptr)
	{
		delete __edges;
	}
}

#pragma mark -

void ABGraph::loadUndirectedGraph(const char *aFileName)
{
	ifstream filestream(aFileName);
	if(!filestream)
	{
		throw runtime_error("Failed to open file.");
	}
	
	
	if (_vertecies == nullptr)
	{
		_vertecies = new ABList<ABVertex>();
	}
	else
	{
		getVertecies().clear();
	}
	
	if (_edges == nullptr)
	{
		_edges = new ABList<ABEdge>();
	}
	else
	{
		getEdges().clear();
	}
	
	
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
	_graph_type = ABGraphTypeUndirected;
}

void ABGraph::loadDirectedGraph(const char *aFileName)
{
	ifstream filestream(aFileName);
	if(!filestream)
	{
		throw runtime_error("Failed to open file.");
	}
	
	
	if (__vertecies == nullptr)
	{
		__vertecies = new ABVector<ABVertex>(VERTECIES_NUMBER);
	}
	else
	{
		(*__vertecies).clear();
		(*__vertecies).reserve(VERTECIES_NUMBER);
	}
	
	if (__edges == nullptr)
 	{
		__edges = new ABVector<ABEdge>(EDGES_NUMBER);
	}
	else
	{
		(*__edges).clear();
		(*__edges).reserve(EDGES_NUMBER);
	}
	
	
	int vertexId = -1;
	ABVertex *vertex = nullptr;
	
	string line;
	while (getline(filestream, line))
	{
		istringstream sstream(line);
		sstream >> vertexId;
		
		while (vertexId > (*__vertecies).getSize())
		{
			(*__vertecies).pushBack(ABVertex((*__vertecies).getSize() + 1));
		}
		vertex = &(*__vertecies)[vertexId - 1];
		
		int adjacentVertexId;
		while (sstream >> adjacentVertexId)
		{
			ABVertex *adjacentVertex = nullptr;
			
			while (adjacentVertexId > (*__vertecies).getSize())
			{
				(*__vertecies).pushBack(ABVertex((*__vertecies).getSize() + 1));
			}
			adjacentVertex = &(*__vertecies)[adjacentVertexId - 1];
			
			(*__edges).pushBack(ABEdge(adjacentVertex /* head */, vertex /* tail */));
			ABEdge *edge = &(*__edges).last();
			
			(*vertex).getEdges().pushBack(edge);
			(*adjacentVertex).__edges.pushBack(edge);
		}
	}
	
	filestream.close();
	_graph_type = ABGraphTypeDirected;
	
#if 1 // tests
	if ((*__vertecies).getSize() != VERTECIES_NUMBER || (*__edges).getSize() != EDGES_NUMBER ||
		(*__vertecies).getCapacity() != VERTECIES_NUMBER || (*__edges).getCapacity() != EDGES_NUMBER)
	{
		throw runtime_error("Test failed.");
	}
#endif
}

void ABGraph::loadGraph(const char *aFileName, ABGraphType aGraphType)
{
	switch (aGraphType)
	{
		case ABGraphTypeDirected:
		{
			loadDirectedGraph(aFileName);
			break;
		}
		case ABGraphTypeUndirected:
		{
			loadUndirectedGraph(aFileName);
			break;
		}
		default:
		{
			throw runtime_error("Cannot load graph of this type.");
	    	break;
		}
	}
}

void ABGraph::display()
{
	if (getGraphType() != ABGraphTypeUndirected)
	{
		throw runtime_error("The functionality is not supported for the graph of this type.");
	}
	
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

void ABGraph::contractVerteciesForEdge(ABEdge *anEdge)
{
	ABVertex *head = (*anEdge).getHead();
	ABVertex *tail = (*anEdge).getTail(); // vertex to be contracted
	
	// from "aHead"
	// remove self-loops
	// remove "anEdge"
	ABList<ABEdge *>::ABIterator pEdgeListIterator;
	for (pEdgeListIterator = (*head).getEdges().begin(); pEdgeListIterator != (*head).getEdges().end();)
	{
		if ((*(*pEdgeListIterator)).getHead() == tail || (*(*pEdgeListIterator)).getTail() == tail)
		{
			pEdgeListIterator = (*head).getEdges().remove(pEdgeListIterator);
		}
		else
		{
			++pEdgeListIterator;
		}
	}
	
	// from "aTail" to "aHead"
	// avoid adding self-loops
	// avoid adding "anEdge"
	
	// from "_edges"
	// remove self-loops
	// remove "anEdge"
	for (pEdgeListIterator = (*tail).getEdges().begin(); pEdgeListIterator != (*tail).getEdges().end();)
	{
		if ((*(*pEdgeListIterator)).getHead() == head || (*(*pEdgeListIterator)).getTail() == head)
		{
			ABList<ABEdge>::ABIterator edgeListIterator;
			for (edgeListIterator = getEdges().begin(); edgeListIterator != getEdges().end(); ++edgeListIterator)
			{
				if (&(*edgeListIterator) == *pEdgeListIterator)
				{
					getEdges().remove(edgeListIterator);
					break;
				}
			}
		}
		else
		{
			if ((*(*pEdgeListIterator)).getHead() == tail)
			{
				(*(*pEdgeListIterator)).setHead(head);
			}
			else if ((*(*pEdgeListIterator)).getTail() == tail)
			{
				(*(*pEdgeListIterator)).setTail(head);
			}
			(*head).getEdges().pushBack(*pEdgeListIterator);
		}
		pEdgeListIterator = (*tail).getEdges().remove(pEdgeListIterator);
	}
	
	// from "_vertecies"
	// remove "tail"
	ABList<ABVertex>::ABIterator vertexListIterator;
	for (vertexListIterator = getVertecies().begin(); vertexListIterator != getVertecies().end(); ++vertexListIterator)
	{
		if (&(*vertexListIterator) == tail)
		{
			getVertecies().remove(vertexListIterator);
			break;
		}
	}
}

int ABGraph::runKargerContractionAlgorithm()
{
	if (getGraphType() != ABGraphTypeUndirected)
	{
		throw runtime_error("The functionality is not supported for the graph of this type.");
	}
	
	srand((unsigned)time(NULL));
	while (getVertecies().getSize() > 2)
	{
		if (!getEdges().getSize())
		{
			throw runtime_error("Edges count cannot be zero.");
		}
		
		int randomIndex = rand() % getEdges().getSize();
		
		ABList<ABEdge>::ABIterator edgeListIterator = getEdges().begin();
		while (randomIndex--)
		{
			++edgeListIterator;
		}
		ABEdge *edge = &(*edgeListIterator);
		contractVerteciesForEdge(edge);
	}
	
#if 1 // tests
	if ( getVertecies().getSize() != 2 ||
		getVertecies().front().getEdges().getSize() != getEdges().getSize() ||
		getVertecies().back().getEdges().getSize() != getEdges().getSize())
	{
		throw runtime_error("Test failed.");
	}
#endif
	
	int minCut = getEdges().getSize();
	return minCut;
}

#pragma mark -

void ABGraph::runBFSAlgorithmWithEntryVertex(ABVertex *aVertex)
{
	ABList<ABVertex *> queue;
	
	ABVertex *pairedVertex = nullptr;
	ABVertex *vertex = aVertex;
	(*vertex).setBFSLayerNumber(0);
	queue.pushBack(vertex);
	
	while (!queue.isEmpty())
	{
		vertex = queue.front();
		queue.popFront();
		
		ABList<ABEdge *>::ABIterator pEdgeListIterator;
		for (pEdgeListIterator = (*vertex).getEdges().begin(); pEdgeListIterator != (*vertex).getEdges().end(); ++pEdgeListIterator)
		{
			pairedVertex = (*(*pEdgeListIterator)).pairedVertexForVertex(vertex);
			if (!(*pairedVertex).isExploredBFS())
			{
				(*pairedVertex).setBFSLayerNumber((*vertex).getBFSLayerNumber() + 1);
				queue.pushBack(pairedVertex);
			}
		}
	}
	
#if 0 // tests
	ABList<ABVertex>::ABIterator vertexListIterator;
	for (vertexListIterator = getVertecies().begin(); vertexListIterator != getVertecies().end(); ++vertexListIterator)
	{
		if (!(*vertexListIterator).isExploredBFS())
		{
			throw runtime_error("Test failed.");
		}
		else
		{
			cout << "Id: " << (*vertexListIterator).getVertexId()
			     << " Layer number: " << (*vertexListIterator).getBFSLayerNumber() << endl;
		}
	}
#endif
}

void ABGraph::runBFSAlgorithmWithEntryVertexId(int aVertexId)
{
	if (getGraphType() != ABGraphTypeUndirected)
	{
		throw runtime_error("The functionality is not supported for the graph of this type.");
	}
	
	ABVertex *vertex = nullptr;
	
	// { List search
	ABList<ABVertex>::ABIterator vertexListIterator;
	for (vertexListIterator = getVertecies().begin(); vertexListIterator != getVertecies().end(); ++vertexListIterator)
	{
		if ((*vertexListIterator).getVertexId() == aVertexId)
		{
			vertex = &(*vertexListIterator);
			break;
		}
	}
	// }

	runBFSAlgorithmWithEntryVertex(vertex);
}

#pragma mark - 

static int dfs_order_number = 0;
static ABVertex *dfs_vertex_leader = nullptr;

void ABGraph::runOrderingDFSAlgorithmWithEntryVertex(ABVertex *aVertex)
{
	// just to let others know that the vertex has been explored
	// but the order number has not been assigned yet
	(*aVertex).setDFSOrderNumber(0);
	
	for (ABList<ABEdge *>::ABIterator pEdgeListIterator = (*aVertex).__edges.begin(); pEdgeListIterator != (*aVertex).__edges.end(); ++pEdgeListIterator)
	{
		if ((*(*pEdgeListIterator)).getHead() != aVertex)
		{
			throw runtime_error("Test failed.");
		}
		
		// traverse graph in reversed order
		ABVertex *tail = (*(*pEdgeListIterator)).getTail();
		if (!(*tail).isExploredDFS())
		{
			runOrderingDFSAlgorithmWithEntryVertex(tail);
		}
	}
	
	++dfs_order_number;
	(*aVertex).setDFSOrderNumber(dfs_order_number);
	(*__orderedVertecies).pushFront(aVertex);
}

void ABGraph::orderVerteciesInReversedGraph()
{
	if (__orderedVertecies == nullptr)
	{
		__orderedVertecies = new ABList<ABVertex *>();
	}
	else
	{
		(*__orderedVertecies).clear();
	}
	
#if 1
	ABVector<ABVertex>::ABIterator vertexVectorIterator;
	for (vertexVectorIterator = (*__vertecies).begin(); vertexVectorIterator != (*__vertecies).end(); ++vertexVectorIterator)
	{
		if (!(*vertexVectorIterator).isExploredDFS())
		{
			runOrderingDFSAlgorithmWithEntryVertex(&(*vertexVectorIterator));
		}
	}
#else
	for (int i = (*__vertecies).getSize() - 1; i >= 0; --i)
	{
		ABVertex *vetrex = &(*__vertecies)[i];
		if (!(*vetrex).isExploredDFS())
		{
			runOrderingDFSAlgorithmWithEntryVertex(vetrex);
		}
	}
#endif
	
#if 1 // tests
	ABList<ABVertex *>::ABIterator pVertexListIterator = (*__orderedVertecies).begin();
	++pVertexListIterator;
	for (; pVertexListIterator != (*__orderedVertecies).end(); ++pVertexListIterator)
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
	
	if ((*__orderedVertecies).getSize() != VERTECIES_NUMBER || dfs_order_number != VERTECIES_NUMBER ||
		(*(*__orderedVertecies).front()).getDFSOrderNumber() != VERTECIES_NUMBER ||
		(*(*__orderedVertecies).back()).getDFSOrderNumber() != 1)
	{
		throw runtime_error("Test failed.");
	}
#endif
}

#pragma mark - 

void ABGraph::runDFSAlgorithmWithEntryVertex(ABVertex *aVertex)
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

void ABGraph::findStronglyConnectedComponents()
{
	int max_scc_count[5] = {0};
	
	ABList<ABVertex *>::ABIterator pVertexListIterator;
	for (pVertexListIterator = (*__orderedVertecies).begin(); pVertexListIterator != (*__orderedVertecies).end();)
	{
		if (!(*(*pVertexListIterator)).isExploredDFSVertexLeader())
		{
			dfs_vertex_leader = *pVertexListIterator;
			runDFSAlgorithmWithEntryVertex(*pVertexListIterator);
		}
		pVertexListIterator = (*__orderedVertecies).remove(pVertexListIterator);
	}

	ABVector<ABVertex>::ABIterator vertexVectorIterator;
	
#if 1 // tests
	for (vertexVectorIterator = (*__vertecies).begin(); vertexVectorIterator != (*__vertecies).end(); ++vertexVectorIterator)
	{
		if (!(*vertexVectorIterator).isExploredDFSVertexLeader())
		{
			throw runtime_error("Test failed.");
		}
	}
#endif
	
	for (vertexVectorIterator = (*__vertecies).begin(); vertexVectorIterator != (*__vertecies).end(); ++vertexVectorIterator)
	{
		++(*(*vertexVectorIterator).getDFSVertexLeader())._entryCount;
	}
	
	for (vertexVectorIterator = (*__vertecies).begin(); vertexVectorIterator != (*__vertecies).end(); ++vertexVectorIterator)
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

void ABGraph::runKosarajusTwoPassAlgorithm()
{
	if (getGraphType() != ABGraphTypeDirected)
	{
		throw runtime_error("The functionality is not supported for the graph of this type.");
	}
	
	orderVerteciesInReversedGraph();
	findStronglyConnectedComponents();
}

#pragma mark -

void ABGraphUnitTests(ABGraph &aGraph)
{	
	if (aGraph.getGraphType() == ABGraphTypeDirected)
	{
		
	}
	else if (aGraph.getGraphType() == ABGraphTypeUndirected)
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
						(*edgeListIterator)._entryCount++;
						
						if ((*edgeListIterator).getHead() == &(*vertexListIterator))
						{
							++(*(*edgeListIterator).getTail())._entryCount;
						}
						else if ((*edgeListIterator).getTail() == &(*vertexListIterator))
						{
							++(*(*edgeListIterator).getHead())._entryCount;
						}
					}
				}
			}
		}
		
		for (edgeListIterator = aGraph.getEdges().begin(); edgeListIterator != aGraph.getEdges().end(); ++edgeListIterator)
		{
			if ((*edgeListIterator)._entryCount != 2)
			{
				throw runtime_error("Test failed.");
			}
		}
		
		for (vertexListIterator = aGraph.getVertecies().begin(); vertexListIterator != aGraph.getVertecies().end(); ++vertexListIterator)
		{
			if ((*vertexListIterator).getEdges().getSize() != (*vertexListIterator)._entryCount)
			{
				throw runtime_error("Test failed.");
			}
		}
	}
	else
	{
		cout << "No tests provided for the graph of this type." << endl;
	}
}
