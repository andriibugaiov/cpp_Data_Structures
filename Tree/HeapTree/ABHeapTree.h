//
//  ABHeapTree.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-02-27.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#ifndef __workplace__ABHeapTree__
#define __workplace__ABHeapTree__

#define HEAP_TREE_INITIAL_CAPACITY 8

template <typename T>
class ABVector;

template <typename T>
class ABNodeKeyValue;

template <typename T>
class ABHeapTree
{
    ABVector<ABNodeKeyValue<T>> _vector;
    
    void percolateUp(int anIndex);
    void percolateDown(int anIndex);
		
	int search(const T &aData);
public:
    ABHeapTree(int aCapacity = HEAP_TREE_INITIAL_CAPACITY);
	ABHeapTree(ABVector<T> &aData, ABVector<int> &aKeys);
	
	void clear();
	
    int getSize() const;
    bool isEmpty() const;
	
    void insert(const T &aData, int aKey);
    
    T removeRoot(int *oaKey = nullptr);
    const T &lookUpRoot(int *oaKey = nullptr) const;
	
	void increaseKey(const T &aData, int aDelta);
	void decreaseKey(const T &aData, int aDelta);
	
	friend void ABHeapTreeUnitTests(ABHeapTree<T> &aTree);
};


#endif /* defined(__workplace__ABHeapTree__) */
