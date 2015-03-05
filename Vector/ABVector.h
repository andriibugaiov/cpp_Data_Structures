//
//  ABVector.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABVector__
#define __workplace__ABVector__

#define VECTOR_INITIAL_CAPACITY 8

template <typename T>
class ABVector
{
	int _size;
	int _capacity;
	T *_origin;
public:
	ABVector(int aCapacity = VECTOR_INITIAL_CAPACITY);
	ABVector(const ABVector<T> &anOther);
	~ABVector();
	
	void clear();
	void reserve(int aCapacity);
	
	int getSize() const;
	int getCapacity() const;
	bool isEmpty() const;
	
	const ABVector<T> &operator=(const ABVector &anOther);
	
	T &operator[](int aPosition);
	const T &operator[](int aPosition) const;
	T &last();
	const T &last() const;
	
	void pushBack(const T &aData);
	T popBack();
	void insert(int aPosition, const T &aData);
	T remove(int aPosition);
	
	typedef T *ABIterator;
	typedef const T *ABConstIterator;
	ABIterator begin();
	ABConstIterator begin() const;
	ABIterator end();
	ABConstIterator end() const;
	
	friend void ABVectorUnitTests(ABVector<T> &aVector);
};

#endif /* defined(__workplace__Vector__) */
