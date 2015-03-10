//
//  ABNodeKeyValue.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-27.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#ifndef __workplace__ABNodeKeyValue__
#define __workplace__ABNodeKeyValue__

#include "ABNode.h"

template <typename T>
class ABNodeKeyValue : public ABNode<T>
{
    int _key;
public:
    ABNodeKeyValue(int aKey = -1);
    ABNodeKeyValue(const T &aData, int aKey = -1);
    
    int getKey() const;
    void setKey(int aKey);
    
    bool operator<(const ABNodeKeyValue<T> &anOther);
    bool operator>(const ABNodeKeyValue<T> &anOther);
	bool operator==(const ABNodeKeyValue<T> &anOther);
};

#endif /* defined(__workplace__ABNodeKeyValue__) */
