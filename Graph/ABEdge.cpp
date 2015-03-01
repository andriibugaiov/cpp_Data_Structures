//
//  ABEdge.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABEdge.h"

ABEdge::ABEdge(ABVertex *aHead, ABVertex *aTail, int aLength) : _head(aHead), _tail(aTail), _length(aLength), _counter(0)
{
}

int ABEdge::getLength()
{
	return _length;
}

ABVertex *ABEdge::getHead()
{
	return _head;
}

ABVertex *ABEdge::getTail()
{
	return _tail;
}

void ABEdge::setLength(int aLength)
{
	_length = aLength;
}

void ABEdge::setHead(ABVertex *aHead)
{
	_head = aHead;
}

void ABEdge::setTail(ABVertex *aTail)
{
	_tail = aTail;
}

ABVertex *ABEdge::getAdjacentVertexForVertex(ABVertex *aVertex)
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

#pragma mark -

bool ABEdge::operator==(const ABEdge &anOther)
{
	return this == &anOther;
}
