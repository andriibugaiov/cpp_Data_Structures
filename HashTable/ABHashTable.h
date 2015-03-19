//
//  ABHashTable.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-04.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABHashTable__
#define __workplace__ABHashTable__

#include "ABVector.h"
#include "ABList.h"

#define TWO_SUM_PROBLEM "TwoSumProblem.txt"

#define HASH_TABLE_INITIAL_CAPACITY 8

// TODO:
template <typename T>
class ABHashTable
{	
	int _size;
	ABVector<ABList<T>> _table;
	
	int nextPrime(int aCapacity);
	void rehash();
public:
	ABHashTable(int aCapacity = HASH_TABLE_INITIAL_CAPACITY);
	
	void display();
	
	int getSize() const;
    bool isEmpty() const;
	
	const ABList<T> &operator[](int aPosition) const;
    int hashPosition(/*const*/ T &aData);
    int getTableSize() const;
    
	bool search(/*const*/ T &aData);
	
	void insert(/*const*/ T &aData);
	void remove(/*const*/ T &aData);

	friend void ABHashTableUnitTests(ABHashTable<T> &aHashTable);
};

long long _hash(long long aValue);

#endif /* defined(__workplace__ABHashTable__) */
