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
	int _length;
	
	ABVertex *_head;
	ABVertex *_tail;
public:
	// tests specific data
	int _counter;
	
	ABEdge(ABVertex *aHead = nullptr, ABVertex *aTail = nullptr, int aLength = -1);
	
	int getLength();
	ABVertex *getHead();
	ABVertex *getTail();
	
	void setLength(int aLength);
	void setHead(ABVertex *aHead);
	void setTail(ABVertex *aTail);
	
	ABVertex *getAdjacentVertexForVertex(ABVertex *aVertex);
	
	bool operator==(const ABEdge &anOther);
};

#endif /* defined(__workplace__ABEdge__) */
