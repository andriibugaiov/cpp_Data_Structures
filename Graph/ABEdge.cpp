//
//  ABEdge.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABEdge.h"

ABEdge::ABEdge(ABVertex *aHead, ABVertex *aTail) : _head(aHead), _tail(aTail), _counter(0)
{
}

ABVertex *ABEdge::getHead()
{
	return _head;
}

ABVertex *ABEdge::getTail()
{
	return _tail;
}

void ABEdge::setHead(ABVertex *aHead)
{
	_head = aHead;
}

void ABEdge::setTail(ABVertex *aTail)
{
	_tail = aTail;
}

ABVertex *ABEdge::getPairedVertexForVertex(ABVertex *aVertex)
{
	if (aVertex == getHead())
	{
		return getTail();
	}
	else if (aVertex == getTail())
	{
		return getHead();
	}
	return nullptr;
}
