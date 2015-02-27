//
//  ABGraph.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABGraph__
#define __workplace__ABGraph__

class ABGraph
{
public:
	virtual void loadGraph(const char *aFileName) = 0;
	virtual void display() = 0;
};

// TODO: implement adapter class
void ABGraphUnitTests(ABGraph &aGraph);

#endif /* defined(__workplace__ABGraph__) */
