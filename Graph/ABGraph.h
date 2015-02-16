//
//  ABGraph.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-15.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

// TODO: (Graph) rework after assignment submission

#ifndef __workplace__ABGraph__
#define __workplace__ABGraph__

#include "ABEdge.h"
#include "ABVertex.h"
#include "ABVector.h"

#define FILE_NAME "/Users/andriibugaiov/My_Projects/Algorithms_DataStructures/cpp_Data_Structures/Graph/KargerMinCut.txt"

#include "time.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

class ABGraph
{
public:
	ABVector<ABVertex> _vertecies;
	ABVector<ABEdge> _edges;
	
 	void loadGraph()
	{
		{
			const char* filename = FILE_NAME;
			ifstream filestream(filename);
			if(!filestream)
			{
				throw runtime_error("Failed to open file.");
			}
			
			string line;
			while (getline(filestream, line))
			{
				istringstream sstream(line);
				int vertexId;
				sstream >> vertexId;
				
				// ***********************
				
				ABVector<ABVertex>::ABIterator vI;
				
				// { vector search
				ABVertex *vertex = nullptr;
				
				for (vI = _vertecies.begin(); vI != _vertecies.end(); ++vI)
				{
					if ((*vI)._vertex_id == vertexId)
					{
						vertex = vI;
						break;
					}
				}
				// }
				
				if (!vertex)
				{
					_vertecies.pushBack(ABVertex(vertexId));
					vI = _vertecies.end();
					vertex = --vI;
				}
				
				// ***********************
				
				int adjacentVertexId;
				while (sstream >> adjacentVertexId)
				{
					// { vector search
					ABVertex *adjacentVertex = nullptr;
					
					for (vI = _vertecies.begin(); vI != _vertecies.end(); ++vI)
					{
						if ((*vI)._vertex_id == adjacentVertexId)
						{
							adjacentVertex = vI;
							break;
						}
					}
					// }
					
					if (!adjacentVertex)
					{
						_vertecies.pushBack(ABVertex(adjacentVertexId));
						vI = _vertecies.end();
						adjacentVertex = --vI;
					}
					
					
					ABList<ABEdge *>::ABIterator lI;
					
					// { list search
					ABEdge *edge = nullptr;
					
					for (lI = (*adjacentVertex)._edges.begin(); lI != (*adjacentVertex)._edges.end(); ++lI)
					{
						if ((*(*lI))._tail == vertex
							/* && (*(*lI))._head == adjacentVertex */
							/* || ( ) */)
						{
							edge = *lI;
							break;
						}
					}
					// }
					
					if (!edge)
					{
						_edges.pushBack(ABEdge(vertex, adjacentVertex));
						
						ABVector<ABEdge>::ABIterator vEdgeI;
						vEdgeI = _edges.end();
						edge = --vEdgeI;
					}
					
					(*vertex)._edges.pushBack(edge);
				}
			}
			
			filestream.close();
		}
	}
	
	void display()
	{
		ABVector<ABVertex>::ABIterator vI;
		for (vI = _vertecies.begin(); vI != _vertecies.end(); ++vI)
		{
			cout << (*vI)._vertex_id << " - ";
			ABList<ABEdge *>::ABIterator lI;
			for (lI = (*vI)._edges.begin(); lI != (*vI)._edges.end(); ++lI)
			{
				ABEdge *edge = *lI;
				cout << " (" << (*(*edge)._head)._vertex_id << ", " << (*(*edge)._tail)._vertex_id << ") ";
			}
			cout << endl;
		}
	}

	int minCutContractionAlgorithm()
	{
		int activeVerteciesCount = _vertecies.getSize();
		
		srand((unsigned)time(NULL));
		while (activeVerteciesCount > 2)
		{
			int activeEdgesCount = 0;
			ABVector<ABEdge>::ABIterator vEdgeI;
			for (vEdgeI = _edges.begin(); vEdgeI != _edges.end(); ++vEdgeI)
			{
			 	if ((*vEdgeI)._active)
				{
					++activeEdgesCount;
				}
			}
			
			int rIndex = rand() % activeEdgesCount;
			int index = 0;
			for (vEdgeI = _edges.begin(); vEdgeI != _edges.end(); ++vEdgeI)
			{
				ABEdge *edge = vEdgeI;
				if ((*edge)._active)
				{
					if (index == rIndex)
					{
						ABVertex *head = (*edge)._head;
						ABVertex *tail = (*edge)._tail;
						
						contractVertecies(head, tail, edge);
						--activeVerteciesCount;
						
						break;
					}
					++index;
				}
			}
		}
		
		ABVector<ABVertex>::ABIterator vI;
		activeVerteciesCount = 0;
		for (vI = _vertecies.begin(); vI != _vertecies.end(); ++vI)
		{
			if ((*vI)._active)
			{
				++activeVerteciesCount;
			}
		}
		if (activeVerteciesCount != 2)
		{
			throw runtime_error("Test failed.");
		}
		
		int minCut = 0;
		ABVector<ABEdge>::ABIterator vEdgeI;
		for (vEdgeI = _edges.begin(); vEdgeI != _edges.end(); ++vEdgeI)
		{
			ABEdge *edge = vEdgeI;
			if ((*edge)._active)
			{
				++minCut;
			}
		}
		return minCut;
	}
	
	void contractVertecies(ABVertex *aHead, ABVertex *aTail, ABEdge *anEdge)
	{
		(*aTail)._active = false;
		
		(*aHead)._contracted_vertecies_ids.pushBack((*aTail)._vertex_id);
	
		
		ABList<ABEdge *>::ABIterator lI;
		for (lI = (*aTail)._edges.begin(); lI != (*aTail)._edges.end();)
		{
			if (*lI != anEdge)
			{
				if ((*(*lI))._head == aTail)
				{
					(*(*lI))._head = aHead;
				}
				else if ((*(*lI))._tail == aTail)
				{
					(*(*lI))._tail = aHead;
				}
				(*aHead)._edges.pushBack(*lI);
			}
			lI = (*aTail)._edges.remove(lI);
		}
		
		for (lI = (*aHead)._edges.begin(); lI != (*aHead)._edges.end();)
		{
			if (*lI == anEdge || ((*(*lI))._head == aHead && (*(*lI))._tail == aHead))
			{
				(*(*lI))._active = false;
				(*(*lI))._head = nullptr;
				(*(*lI))._tail = nullptr;
				
				lI = (*aHead)._edges.remove(lI);
			}
			else
			{
				++lI;
			}
		}
	}
};

// TODO: implement adapter class
void ABGraphUnitTests();

#endif /* defined(__workplace__ABGraph__) */
