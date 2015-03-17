//
//  ABNodeTwoSum.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-16.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABNodeTwoSum.h"

#include <stdexcept>
#include <iostream>

using namespace std;

ABNodeTwoSum::ABNodeTwoSum(int aKey) : ABNodeKeyValue<long long> (aKey)
{
	
}

ABNodeTwoSum::ABNodeTwoSum(const long long &aData, int aKey) : ABNodeKeyValue<long long> (aData, aKey)
{
	
}

bool ABNodeTwoSum::ABNodeTwoSum::operator<(const ABNodeTwoSum &anOther)
{
	throw runtime_error("Error! operator is not defined");
	return true;
}

bool ABNodeTwoSum::operator>(const ABNodeTwoSum &anOther)
{
	throw runtime_error("Error! operator is not defined");
	return true;
}

bool ABNodeTwoSum::operator==(const ABNodeTwoSum &anOther)
{
	return getKey() == anOther.getKey() && (this -> getData() == anOther.getData());
}

bool ABNodeTwoSum::operator!=(const ABNodeTwoSum &anOther)
{
	return !(*this == anOther);
}

#pragma mark -

long long _hash(ABNodeTwoSum &aNode)
{
	return aNode.getKey();
}
