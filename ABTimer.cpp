//
//  ABTimer.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-18.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#include "ABTimer.h"

#include <iostream>
#include <time.h>

using namespace std;

void ABTimer(void (*aTask)(void *), void *anArgument)
{
	clock_t begin, end;
	double time_spent;
	
	begin = clock();
	
	aTask(anArgument);
	
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	cout << "Time spent - " << time_spent << endl;
}
