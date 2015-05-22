//
//  ABBinaryNode.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-05-22.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#ifndef __workplace__ABBinaryNode__
#define __workplace__ABBinaryNode__

#include "ABBinarySearchTree.h"

// TODO:
//template <typename Key>
//class ABBinaryTree;

//template <typename Key, typename Comparator = std::less<Key>>
//class ABBinarySearchTree;

template <typename Key>
class ABBinaryNode
{
    ABBinaryNode()
    {
        _count = 0;
        _left = nullptr;
        _right = nullptr;
    }

public:
    // TODO:
    Key _key;
    int _data;
    
    long long _count;
    
    ABBinaryNode<Key> *_left;
    ABBinaryNode<Key> *_right;
    
    ABBinaryNode(Key &key, int &data)
    {
        _key = key;
        _data = data;
        
        _count = 1;
        _left = nullptr;
        _right = nullptr;
    }

    // TODO:
//    friend class ABBinaryTree<Key>;
//    friend class ABBinarySearchTree<Key>;
};

#endif /* defined(__workplace__ABBinaryNode__) */
