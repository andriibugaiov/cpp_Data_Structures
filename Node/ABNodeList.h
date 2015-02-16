//
//  ListNode.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-01-28.
//  Copyright (c) 2015 MyCompany. All rights reserved.
//

#ifndef __workplace__ListNode__
#define __workplace__ListNode__

template <typename T>
class ABList;

template <typename T>
class ABNode;

template <typename T>
class ABNodeList : public ABNode<T> {
	ABNodeList<T> *_next;
	ABNodeList<T> *_previous;
	
	void setNext(ABNodeList<T> *aNext);
	void setPrevious(ABNodeList<T> *aPrevious);
	
	ABNodeList<T>* getNext() const;
	ABNodeList<T>* getPrevious() const;
	
	ABNodeList(ABNodeList<T> *aNext = nullptr, ABNodeList<T> *aPrevious = nullptr);
public:
	ABNodeList(const T& aData, ABNodeList<T> *aNext = nullptr, ABNodeList<T> *aPrevious = nullptr);
	
	// in order to let ABList access private acessors and constructor of ABNodeList
	friend class ABList<T>;
};

#endif /* defined(__workplace__ABNodeList__) */
