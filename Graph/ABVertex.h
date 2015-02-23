//
//  ABVertex.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABVertex__
#define __workplace__ABVertex__

#include "ABList.h"

class ABEdge;

// TODO: rework ABVertex architecture
class ABVertex
{
	int _vertex_id;
	ABList<ABEdge *> _edges; // undirected
	
	// algorithms specific data
	int _bfs_layer_number; // undirected
	int _dfs_order_number; // directed
	ABVertex *_dfs_vertex_leader; // directed
public:
	ABList<ABEdge *> __edges; // directed
	
	// tests specific data
	int _entryCount; // undirected
	
	ABVertex(int aVertexId = -1);
	
	int getVertexId();
	ABList<ABEdge *> &getEdges();
	
	int getBFSLayerNumber(); // undirected
	void setBFSLayerNumber(int aBFSLayerNumber); // undirected
	bool isExploredBFS(); // undirected
	
	int getDFSOrderNumber(); // directed
	void setDFSOrderNumber(int aDFSOrderNumber); // directed
	bool isExploredDFS(); // directed
	
	ABVertex *getDFSVertexLeader(); // directed
	void setDFSVertexLeader(ABVertex *aDFSVertexLeader); // directed
	bool isExploredDFSVertexLeader(); // directed
};

#endif /* defined(__workplace__ABVertex__) */
