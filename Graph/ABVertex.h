//
//  ABVertex.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABVertex__
#define __workplace__ABVertex__

#include "ABList.h"

class ABEdge;
class ABVertex
{
	ABList<ABEdge *> _edges;
public:
	// TODO:
	//	ABList<int> _contracted_vertecies_ids;
	int _vertex_id;
	int _entryCount;
	
	ABVertex(int aVertexId = -1) : _vertex_id(aVertexId), _entryCount(0)
	{
	}
	
	ABList<ABEdge *> &getEdges()
	{
		return _edges;
	}
};

#endif /* defined(__workplace__ABVertex__) */
