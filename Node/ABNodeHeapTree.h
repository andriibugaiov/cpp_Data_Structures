//
//  ABNodeHeapTree.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-27.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#ifndef __workplace__ABNodeHeapTree__
#define __workplace__ABNodeHeapTree__

#include "ABNode.h"

template <typename T>
class ABNodeHeapTree : public ABNode<T>
{
    int _key;
public:
    ABNodeHeapTree(int aKey = -1);
    ABNodeHeapTree(const T &aData, int aKey = -1);
    
    int getKey() const;
    void setKey(int aKey);
    
    bool operator<(const ABNodeHeapTree<T> &anOther);
    bool operator>(const ABNodeHeapTree<T> &anOther);
	bool operator==(const ABNodeHeapTree<T> &anOther);
};

#endif /* defined(__workplace__ABNodeHeapTree__) */
