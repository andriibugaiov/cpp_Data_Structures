//
//  ABList.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__List__
#define __workplace__List__

template <typename T>
class ABNodeList;

template <typename T>
class ABList
{
	int _size;
	
	// empty objects to simplify logic
	ABNodeList<T> *_pre_head;
	ABNodeList<T> *_post_tail;
		
	void initialize();
	
public:
	ABList();
	ABList(const ABList<T>& anOther);
	~ABList();
	
	class ABConstIterator
	{
	protected:
		// TODO:
		// ABList<T> *_list;
		ABNodeList<T> *_current;

		ABNodeList<T> *getCurrent() const;
		void setCurrent(ABNodeList<T> *aCurrent);
		
		ABConstIterator(ABNodeList<T> *aCurrent);
	public:
		ABConstIterator();
		
		const T &operator*() const;
		ABConstIterator &operator++();
		ABConstIterator operator++(int);
		ABConstIterator &operator--();
		ABConstIterator operator--(int);
		
		bool operator==(const ABConstIterator & anOther) const;
		bool operator!=(const ABConstIterator & anOther) const;
		
		// in order to let ABList access protected constractors of ABConstIterator
		friend class ABList<T>;
	};
	
	class ABIterator : public ABConstIterator
	{
	protected:
		ABIterator(ABNodeList<T> *aCurrent);
	public:
		ABIterator();
		
		T &operator*();
		const T &operator*() const;
		ABIterator &operator++();
		ABIterator operator++(int);
		ABIterator &operator--();
		ABIterator operator--(int);

		// in order to let ABList access protected constractors of ABIterator
		friend class ABList<T>;
	};
	
	void clear();
	
	int getSize() const;
	bool isEmpty() const;
	
	const ABList<T> &operator=(const ABList<T> &anOther);
	
	T &front();
	const T &front() const;
	T &back();
	const T &back() const;
	
	void pushFront(const T &aData);
	void popFront();
	void pushBack(const T &aData);
	void popBack();
	
	ABIterator begin();
	ABConstIterator begin() const;
	ABIterator end();
	ABConstIterator end() const;
	ABIterator insert(ABIterator anInterator, const T &aData);
	ABIterator remove(ABIterator anInterator);
	ABIterator remove(ABIterator aStart, ABIterator anEnd);
	
	friend void ABListUnitTests(ABList<T> &aList);
};

#endif /* defined(__workplace__ABList__) */
