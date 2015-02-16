//
//  ABVertex.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

// TODO: (Graph) rework after assignment submission

#ifndef __workplace__ABVertex__
#define __workplace__ABVertex__

#include "ABList.h"

class ABEdge;
class ABVertex
{
public:
	// TODO:
	int _entryCount;
	bool _active;
	
	int _vertex_id;
	ABList<int> _contracted_vertecies_ids;
	
	ABList<ABEdge *> _edges;
	
	ABVertex(int aVertexId = -1) : _vertex_id(aVertexId)
	{
		_entryCount = 0;
		_active = true;
	}
};

#endif /* defined(__workplace__ABVertex__) */
