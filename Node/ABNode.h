//
//  ABNode.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABNode__
#define __workplace__ABNode__

template <typename T>
class ABNode
{
	T _data;
public:
	ABNode();
	ABNode(const T &aData);
	T &getData();
};

#endif /* defined(__workplace__ABNode__) */
