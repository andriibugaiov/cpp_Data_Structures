//
//  ABVector.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ABVector__
#define __workplace__ABVector__

template <typename T>
class ABVector
{
	int _size;
	int _capacity;
	T *_origin;
	
	void reserve(int aCapacity);
public:
	ABVector();
	ABVector(int aCapacity = 0);
	ABVector(const ABVector<T> &anOther);
	~ABVector();

	int getSize() const;
	int getCapacity() const;
	bool isEmpty() const;
	
	const ABVector<T> &operator=(const ABVector &anOther);
	T &operator[](int aPosition);
	const T &operator[](int aPosition) const;
	
	void pushBack(const T &aData);
	T popBack();
	
	void insert(int aPosition, const T &aData);
	T remove(int aPosition);
	
	typedef T * ABIterator;
	typedef const T * ABConstIterator;
	
	ABIterator begin();
	ABConstIterator begin() const;
	
	ABIterator end();
	ABConstIterator end() const;
};

#endif /* defined(__workplace__Vector__) */
