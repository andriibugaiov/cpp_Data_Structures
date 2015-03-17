//
//  ABNodeTwoSum.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-16.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABNodeTwoSum__
#define __workplace__ABNodeTwoSum__

#include "ABNodeKeyValue.h"

class ABNodeTwoSum : public ABNodeKeyValue<long long>
{
public:
	ABNodeTwoSum(int aKey = -1);
	ABNodeTwoSum(const long long &aData, int aKey = -1);
	
	bool operator<(const ABNodeTwoSum &anOther);
	bool operator>(const ABNodeTwoSum &anOther);
	bool operator==(const ABNodeTwoSum &anOther);
	bool operator!=(const ABNodeTwoSum &anOther);
};

long long _hash(ABNodeTwoSum &aNode);

#endif /* defined(__workplace__ABNodeTwoSum__) */
