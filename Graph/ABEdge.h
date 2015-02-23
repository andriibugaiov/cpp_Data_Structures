//
//  ABEdge.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABEdge__
#define __workplace__ABEdge__

class ABVertex;
class ABEdge
{
	ABVertex *_head;
	ABVertex *_tail;
public:
	int _entryCount;
	
	ABEdge(ABVertex *aHead = nullptr, ABVertex *aTail = nullptr);
	
	ABVertex *getHead();
	ABVertex *getTail();
	void setHead(ABVertex *aHead);
	void setTail(ABVertex *aTail);
	
	ABVertex *pairedVertexForVertex(ABVertex *aVertex);
};


#endif /* defined(__workplace__ABEdge__) */
