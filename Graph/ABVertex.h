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
	int _vertex_id;
	ABList<ABEdge *> _edges;
public:
	int _entryCount;
	
	ABVertex(int aVertexId = -1);
	
	int getVertexId();
	ABList<ABEdge *> &getEdges();
};

#endif /* defined(__workplace__ABVertex__) */
