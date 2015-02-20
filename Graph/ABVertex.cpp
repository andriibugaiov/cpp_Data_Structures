//
//  ABVertex.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABVertex.h"

ABVertex::ABVertex(int aVertexId) : _vertex_id(aVertexId), _entryCount(0)
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
