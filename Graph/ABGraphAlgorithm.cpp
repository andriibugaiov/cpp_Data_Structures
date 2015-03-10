//
//  ABGraphAlgorithm.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-25.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABGraphAlgorithm.h"

#include "ABHeapTree.h"
#include "ABVector.h"
#include "ABList.h"

#include "ABVertex.h"
#include "ABEdge.h"
#include "ABUndirectedGraph.h"
#include "ABDirectedGraph.h"

#include <stdexcept>
#include <iostream>

#include "time.h"

using namespace std;

#define TESTS_ENABLED

#pragma mark - Kosarajus Two Pass Algorithm

void ABDFSVertexLeaderAlgorithmWithEntryVertex(ABDirectedGraph &aGraph, ABVertex *aVertex);
void ABOrderVerteciesInReversedGraph(ABDirectedGraph &aGraph);
void ABFindStronglyConnectedComponents(ABDirectedGraph &aGraph);

void ABFindLargestSCC(ABDirectedGraph &aGraph);

#pragma mark -

static int dfs_order_number = 0;
static ABVertex *dfs_vertex_leader = nullptr;

#pragma mark - Depth First Search Algorithm

void ABDFSOrderNumberAlgorithmWithEntryVertex(ABDirectedGraph &aGraph, ABVertex *aVertex)
{
// TODO:
#if 0
	ABList<ABVertex *> stack;
	
	ABVertex *pairedVertex = nullptr;
	ABVertex *vertex = aVertex == nullptr ? &aGraph.getVertecies()[0] : aVertex;
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
			if (!(*pairedVertex).isExploredDFSOrderNumber())
			{
				(*pairedVertex).setDFSOrderNumber(0);
				stack.pushBack(pairedVertex);
			}
		}
	}
#else
	ABVertex *vertex = aVertex == nullptr ? &aGraph.getVertecies()[0] : aVertex;
	
	(*vertex).setDFSOrderNumber(0);
	
	for (ABList<ABEdge *>::ABIterator pEdgeListIterator = (*vertex).getReversedEdges().begin(); pEdgeListIterator != (*vertex).getReversedEdges().end(); ++pEdgeListIterator)
	{
		// traverse graph in reversed order
		ABVertex *tail = (*(*pEdgeListIterator)).getTail();
		if (!(*tail).isExploredDFSOrderNumber())
		{
			ABDFSOrderNumberAlgorithmWithEntryVertex(aGraph, tail);
		}
	}
	
	++dfs_order_number;
	(*vertex).setDFSOrderNumber(dfs_order_number);
	aGraph.getOrderedVertecies().pushFront(vertex);
#endif
}

void ABOrderVerteciesInReversedGraph(ABDirectedGraph &aGraph)
{
	dfs_order_number = 0;

	ABVector<ABVertex>::ABIterator vertexVectorIterator;
	for (vertexVectorIterator = aGraph.getVertecies().begin(); vertexVectorIterator != aGraph.getVertecies().end(); ++vertexVectorIterator)
	{
		if (!(*vertexVectorIterator).isExploredDFSOrderNumber())
		{
			ABDFSOrderNumberAlgorithmWithEntryVertex(aGraph, &(*vertexVectorIterator));
		}
	}
}

#pragma mark -

void ABDFSVertexLeaderAlgorithmWithEntryVertex(ABDirectedGraph &aGraph, ABVertex *aVertex)
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

void ABFindStronglyConnectedComponents(ABDirectedGraph &aGraph)
{
	dfs_vertex_leader = nullptr;
	
	ABList<ABVertex *>::ABIterator pVertexListIterator;
	for (pVertexListIterator = aGraph.getOrderedVertecies().begin(); pVertexListIterator != aGraph.getOrderedVertecies().end();)
	{
		if (!(*(*pVertexListIterator)).isExploredDFSVertexLeader())
		{
			dfs_vertex_leader = *pVertexListIterator;
			ABDFSVertexLeaderAlgorithmWithEntryVertex(aGraph, *pVertexListIterator);
		}
		pVertexListIterator = aGraph.getOrderedVertecies().remove(pVertexListIterator);
	}
}

void ABFindLargestSCC(ABDirectedGraph &aGraph)
{
	ABVector<ABVertex>::ABIterator vertexVectorIterator;
	for (vertexVectorIterator = aGraph.getVertecies().begin(); vertexVectorIterator != aGraph.getVertecies().end(); ++vertexVectorIterator)
	{
		++(*(*vertexVectorIterator).getDFSVertexLeader())._counter;
	}
	
	int max_scc_vertecies_count[5] = {0};
	for (vertexVectorIterator = aGraph.getVertecies().begin(); vertexVectorIterator != aGraph.getVertecies().end(); ++vertexVectorIterator)
	{
		int entryCount = (*vertexVectorIterator)._counter;
		int i;
		for (i = 4; i >= 0; --i)
		{
			if (max_scc_vertecies_count[i] < entryCount)
			{
				int j;
				for (j = 1; j <= i; ++j)
				{
					max_scc_vertecies_count[j - 1] = max_scc_vertecies_count[j];
				}
				max_scc_vertecies_count[i] = entryCount;
				break;
			}
		}
	}
	
	int i;
	for (i = 0; i < 5; ++i)
	{
		cout << max_scc_vertecies_count[i] << ",";
	}
	cout << endl;
	// 211,313,459,968,434821,
}

void ABKosarajusTwoPassAlgorithm(ABDirectedGraph &aGraph)
{
	// "1st pass"
	ABOrderVerteciesInReversedGraph(aGraph);
	
	// "2nd pass"
	ABFindStronglyConnectedComponents(aGraph);
	
	ABFindLargestSCC(aGraph);
}

#pragma mark - Kargen Contraction Algorithm

void ABContractVerteciesForEdge(ABUndirectedGraph &aGraph, ABEdge *anEdge);

#pragma mark -

void ABContractVerteciesForEdge(ABUndirectedGraph &aGraph, ABEdge *anEdge)
{
	ABVertex *head = (*anEdge).getHead();
	// vertex to be contracted
	ABVertex *tail = (*anEdge).getTail();
	
	// from "aHead"; remove self-loops; remove "anEdge"
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
	
	// from "aTail" to "aHead"; avoid adding self-loops; avoid adding "anEdge"
	// from "_edges"; remove self-loops; remove "anEdge"
	for (pEdgeListIterator = (*tail).getEdges().begin(); pEdgeListIterator != (*tail).getEdges().end();)
	{
		if ((*(*pEdgeListIterator)).getHead() == head || (*(*pEdgeListIterator)).getTail() == head)
		{
			ABList<ABEdge>::ABIterator edgeListIterator;
			for (edgeListIterator = aGraph.getEdges().begin(); edgeListIterator != aGraph.getEdges().end(); ++edgeListIterator)
			{
				if (&(*edgeListIterator) == *pEdgeListIterator)
				{
					aGraph.getEdges().remove(edgeListIterator);
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
	
	// from "_vertecies"; remove "tail"
	ABList<ABVertex>::ABIterator vertexListIterator;
	for (vertexListIterator = aGraph.getVertecies().begin(); vertexListIterator != aGraph.getVertecies().end(); ++vertexListIterator)
	{
		if (&(*vertexListIterator) == tail)
		{
			aGraph.getVertecies().remove(vertexListIterator);
			break;
		}
	}
}

int ABKargerContractionAlgorithm(ABUndirectedGraph &aGraph)
{
	srand((unsigned)time(NULL));
	while (aGraph.getVertecies().getSize() > 2)
	{
		if (!aGraph.getEdges().getSize())
		{
			throw runtime_error("Edges size count cannot be zero.");
		}
		
		int randomIndex = rand() % aGraph.getEdges().getSize();
		
		ABList<ABEdge>::ABIterator edgeListIterator = aGraph.getEdges().begin();
		while (randomIndex--)
		{
			++edgeListIterator;
		}
		ABEdge *edge = &(*edgeListIterator);
		ABContractVerteciesForEdge(aGraph, edge);
	}
	
	int minCutCrossingEdgesNumber = aGraph.getEdges().getSize();
	return minCutCrossingEdgesNumber;
}

#pragma mark - Breadth First Search Algorithm

void ABBFSAlgorithmWithEntryVertex(ABUndirectedGraph &aGraph, ABVertex *aVertex)
{
	ABList<ABVertex *> queue;
	
	ABVertex *adjacentVertex = nullptr;
	ABVertex *vertex = aVertex == nullptr ? &aGraph.getVertecies().front() : aVertex;
	(*vertex).setBFSLayerNumber(0);
	queue.pushBack(vertex);
	
	while (!queue.isEmpty())
	{
		vertex = queue.front();
		queue.popFront();
		
		ABList<ABEdge *>::ABIterator pEdgeListIterator;
		for (pEdgeListIterator = (*vertex).getEdges().begin(); pEdgeListIterator != (*vertex).getEdges().end(); ++pEdgeListIterator)
		{
			adjacentVertex = (*(*pEdgeListIterator)).getAdjacentVertexForVertex(vertex);
			if (!(*adjacentVertex).isExploredBFSLayerNumber())
			{
				(*adjacentVertex).setBFSLayerNumber((*vertex).getBFSLayerNumber() + 1);
				queue.pushBack(adjacentVertex);
			}
		}
	}
}

#pragma mark - Dijkstras Shortest Path Algorithm

void ABLoadHeapTree(ABUndirectedGraph &aGraph, ABHeapTree<ABVertex *> &aTree, ABVertex *aVertex);

#pragma mark -

void ABLoadHeapTree(ABUndirectedGraph &aGraph, ABHeapTree<ABVertex *> &aTree, ABVertex *aVertex)
{
	int plusInfinity = INT_MAX;
	ABList<ABVertex>::ABIterator vertexListIterator = aGraph.getVertecies().begin();
	for (; vertexListIterator != aGraph.getVertecies().end(); ++vertexListIterator)
	{
		if (aVertex == &(*vertexListIterator))
		{
			(*aVertex).setGreedyScore(0);
			aTree.insert(aVertex, (*aVertex).getGreedyScore());
		}
		else
		{
			(*vertexListIterator).setGreedyScore(plusInfinity);
			aTree.insert(&(*vertexListIterator), (*vertexListIterator).getGreedyScore());
		}
	}
}

void ABDijkstrasShortestPathAlgorithm(ABUndirectedGraph &aGraph, ABVertex *aVertex)
{
#ifdef TESTS_ENABLED
	// in order to ensure that the graph is connected
	ABBFSAlgorithmWithEntryVertex(aGraph);
	ABList<ABVertex>::ABIterator vertexListIterator = aGraph.getVertecies().begin();
	for (; vertexListIterator != aGraph.getVertecies().end(); ++vertexListIterator)
	{
		if (!(*vertexListIterator).isExploredBFSLayerNumber())
		{
			throw runtime_error("Error!");
		}
	}
#endif
    
	ABHeapTree<ABVertex *> heap;
	ABVertex *vertex = aVertex == nullptr ? &aGraph.getVertecies().front() : aVertex;

	int shortestPaths[aGraph.getVertecies().getSize()];
	for (int i = 0; i < aGraph.getVertecies().getSize(); ++i)
	{
		shortestPaths[i] = -1;
	}
	
    int minusInfinity = INT_MIN;
	ABLoadHeapTree(aGraph, heap, vertex);
	while (!heap.isEmpty())
	{
        int greedyScore = -1;
		vertex = heap.removeRoot(&greedyScore);
		shortestPaths[(*vertex).getVertexId() - 1] = greedyScore;
		
		ABList<ABEdge *>::ABIterator pEdgeListIterator;
		for (pEdgeListIterator = (*vertex).getEdges().begin(); pEdgeListIterator != (*vertex).getEdges().end(); ++pEdgeListIterator)
		{
			ABEdge *edge = *pEdgeListIterator;
			ABVertex *adjacentVertex = (*edge).getAdjacentVertexForVertex(vertex);
			if (!(*adjacentVertex).isExploredDSPGreedyScore())
			{
				int oldGreedyScore = (*adjacentVertex).getGreedyScore();
				int newGreedyScore = greedyScore + (*edge).getLength();
				if (newGreedyScore < oldGreedyScore)
				{
					(*adjacentVertex).setGreedyScore(newGreedyScore);
					// TODO: runs in O(n) because of the search in heap (decrease efficiency from O(m*log(n)) to O(m*n))
					// to do better, keep reference on the node in heap that contains 'adjacent vertex'
					heap.decreaseKey(adjacentVertex, oldGreedyScore - newGreedyScore);
				}
			}
		}
		(*vertex).setGreedyScore(minusInfinity);
	}

#ifdef TESTS_ENABLED
	for (int i = 0; i < aGraph.getVertecies().getSize(); ++i)
	{
		if (shortestPaths[i] == -1)
		{
			throw runtime_error("Graph is connected. Shortest path cannot be -1.");
		}
	}
#endif
    
	int verteciesIds[] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
	for (int i = 0; i < sizeof(verteciesIds)/sizeof(verteciesIds[0]); ++i)
	{
        // 'index' = 'vetexId' - 1
		cout << shortestPaths[verteciesIds[i] - 1] << ",";
	}
	cout << endl;
	// 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068
}
