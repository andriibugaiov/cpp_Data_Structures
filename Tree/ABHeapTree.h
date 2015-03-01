//
//  ABHeapTree.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-27.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#ifndef __workplace__ABHeapTree__
#define __workplace__ABHeapTree__

template <typename T>
class ABVector;

template <typename T>
class ABNodeHeapTree;

template <typename T>
class ABHeapTree
{
    ABVector<ABNodeHeapTree<T>> _vector;
    
    void percolateUp(int anIndex);
    void percolateDown(int anIndex);
	
	ABNodeHeapTree<T> removeRootNode();
	
	int search(const T &aData);
public:
    ABHeapTree();
    
    int getSize() const;
    bool isEmpty() const;
    
    void insert(const T &aData, int aKey);
    T removeRoot();
	
	void increaseKey(const T &aData, int aDelta);
	void decreaseKey(const T &aData, int aDelta);
	
	friend void ABHeapTreeUnitTests(ABHeapTree<int> &aTree);
};


#endif /* defined(__workplace__ABHeapTree__) */
