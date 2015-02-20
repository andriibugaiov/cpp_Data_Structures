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

using namespace std;

ABList<ABVertex> &ABGraph::getVertecies()
{
	return _vertecies;
}

ABList<ABEdge> &ABGraph::getEdges()
{
	return _edges;
}

#pragma mark -

void ABGraph::loadGraph(const char *aFileName)
{
	ifstream filestream(aFileName);
	if(!filestream)
	{
		throw runtime_error("Failed to open file.");
	}
	
	getVertecies().clear();
	getEdges().clear();
	
	string line;
	while (getline(filestream, line))
	{
		istringstream sstream(line);
		int vertexId;
		sstream >> vertexId;
		
		ABVertex *vertex = nullptr;
		
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

void ABGraph::display()
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

int ABGraph::minCutContractionAlgorithm()
{
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
	
	// tests
	if ( getVertecies().getSize() != 2 ||
		getVertecies().front().getEdges().getSize() != getEdges().getSize() ||
		getVertecies().back().getEdges().getSize() != getEdges().getSize())
	{
		throw runtime_error("Test failed.");
	}
	//
	
	int minCut = getEdges().getSize();
	return minCut;
}

#pragma mark -

void ABGraphUnitTests(ABGraph &aGraph)
{
//	g.display();

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
