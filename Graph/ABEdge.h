//
//  ABEdge.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

// TODO: (Graph) rework after assignment submission

#ifndef __workplace__ABEdge__
#define __workplace__ABEdge__

class ABVertex;
class ABEdge
{
public:
	// TODO:
	int _entryCount;
	bool _active;
	
	ABVertex *_head;
	ABVertex *_tail;
	
	ABEdge(ABVertex *aHead = nullptr, ABVertex *aTail = nullptr) : _head(aHead), _tail(aTail)
	{
		_entryCount = 0;
		_active = true;
	}
};


#endif /* defined(__workplace__ABEdge__) */
