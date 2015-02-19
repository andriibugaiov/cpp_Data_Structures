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
public:
	// TODO:
	ABVertex *_head;
	ABVertex *_tail;
	int _entryCount;
	
	ABEdge(ABVertex *aHead = nullptr, ABVertex *aTail = nullptr) : _head(aHead), _tail(aTail), _entryCount(0)
	{
	}
};


#endif /* defined(__workplace__ABEdge__) */
