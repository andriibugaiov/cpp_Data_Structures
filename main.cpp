//
//  main.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include <iostream>

#include "ABVector.h"

using namespace std;

int main()
{
	ABVector<int *> v(0);
	int j;
	for (j = 0; j < 10; ++j)
	{
		int *i = new int(j);
		v.pushBack(i);
	}
	
	const ABVector<int *> constV = v;
	ABVector<int *>::ABConstIterator constI;
	for (constI = constV.begin(); constI != constV.end(); ++constI)
	{
		cout << **constI << endl;
	}
	
	ABVector<int *>::ABIterator i;
	for (i = v.begin(); i != v.end(); ++i)
	{
		delete *i;
	}
	
	return 0;
}
