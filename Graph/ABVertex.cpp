//
//  ABVertex.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABVertex.h"
#include <limits.h>

ABVertex::ABVertex(int aVertexId) : _vertex_id(aVertexId), _counter(0), _bfs_layer_number(-1), _dfs_order_number(-1), _dfs_vertex_leader(nullptr), _greedy_score(-1)
{
}

int ABVertex::getVertexId()
{
	return _vertex_id;
}

ABList<ABEdge *> &ABVertex::getEdges()
{
	return _edges;
}

ABList<ABEdge *> &ABVertex::getReversedEdges()
{
	return _reversed_edges;
}

#pragma mark -

int ABVertex::getBFSLayerNumber()
{
	return _bfs_layer_number;
}

int ABVertex::getDFSOrderNumber()
{
	return _dfs_order_number;
}

ABVertex *ABVertex::getDFSVertexLeader()
{
	return _dfs_vertex_leader;
}

int ABVertex::getGreedyScore()
{
	return _greedy_score;
}

#pragma mark -

void ABVertex::setBFSLayerNumber(int aBFSLayerNumber)
{
	_bfs_layer_number = aBFSLayerNumber;
}


void ABVertex::setDFSOrderNumber(int aDFSOrderNumber)
{
	_dfs_order_number = aDFSOrderNumber;
}

void ABVertex::setDFSVertexLeader(ABVertex *aDFSVertexLeader)
{
	_dfs_vertex_leader = aDFSVertexLeader;
}

void ABVertex::setGreedyScore(int aGreedyScore)
{
	_greedy_score = aGreedyScore;
}

#pragma mark -

bool ABVertex::isExploredBFSLayerNumber()
{
	return getBFSLayerNumber() != -1;
}

bool ABVertex::isExploredDFSOrderNumber()
{
	return getDFSOrderNumber() != -1;
}

bool ABVertex::isExploredDFSVertexLeader()
{
	return getDFSVertexLeader() != nullptr;
}

bool ABVertex::isExploredDSPGreedyScore()
{
	return getGreedyScore() == INT_MIN;
}

#pragma mark -

bool ABVertex::operator==(const ABVertex &anOther)
{
	return this == &anOther;
}
