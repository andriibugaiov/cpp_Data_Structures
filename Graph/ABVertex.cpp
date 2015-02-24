//
//  ABVertex.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABVertex.h"

ABVertex::ABVertex(int aVertexId) : _vertex_id(aVertexId), _entryCount(0), _bfs_layer_number(-1), _dfs_order_number(-1), _dfs_vertex_leader(nullptr)
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

void ABVertex::setBFSLayerNumber(int aBFSLayerNumber)
{
	_bfs_layer_number = aBFSLayerNumber;
}

bool ABVertex::isExploredBFS()
{
	return getBFSLayerNumber() != -1;
}

#pragma mark - 

int ABVertex::getDFSOrderNumber()
{
	return _dfs_order_number;
}

void ABVertex::setDFSOrderNumber(int aDFSOrderNumber)
{
	_dfs_order_number = aDFSOrderNumber;
}

bool ABVertex::isExploredDFS()
{
	return getDFSOrderNumber() != -1;
}

#pragma mark - 

ABVertex *ABVertex::getDFSVertexLeader()
{
	return _dfs_vertex_leader;
}

void ABVertex::setDFSVertexLeader(ABVertex *aDFSVertexLeader)
{
	_dfs_vertex_leader = aDFSVertexLeader;
}

bool ABVertex::isExploredDFSVertexLeader()
{
	return getDFSVertexLeader() != nullptr;
}
