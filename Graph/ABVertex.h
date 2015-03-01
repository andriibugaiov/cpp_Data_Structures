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

class ABVertex
{
	int _vertex_id;
	ABList<ABEdge *> _edges; // undirected / directed
	ABList<ABEdge *> _reversed_edges; // directed
	
	// algorithms specific data
	int _bfs_layer_number; // undirected
	int _dfs_order_number; // directed
	ABVertex *_dfs_vertex_leader; // directed
	int _greedy_score; // undirected
public:
	// tests specific data
	int _counter; // undirected / directed
	
	ABVertex(int aVertexId = -1);
	
	int getVertexId();
	ABList<ABEdge *> &getEdges();
	ABList<ABEdge *> &getReversedEdges();
	
	int getBFSLayerNumber();
	int getDFSOrderNumber();
	ABVertex *getDFSVertexLeader();
	int getGreedyScore();
	
	void setBFSLayerNumber(int aBFSLayerNumber);
	void setDFSOrderNumber(int aDFSOrderNumber);
	void setDFSVertexLeader(ABVertex *aDFSVertexLeader);
	void setGreedyScore(int aScore);
	
	bool isExploredBFSLayerNumber();
	bool isExploredDFSOrderNumber();
	bool isExploredDFSVertexLeader();
	bool isExploredDSPGreedyScore();
	
	bool operator==(const ABVertex &anOther);
};

#endif /* defined(__workplace__ABVertex__) */
