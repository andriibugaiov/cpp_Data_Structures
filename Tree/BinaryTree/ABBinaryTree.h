//
//  ABBinaryTree.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-05-22.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#ifndef __workplace__ABBinaryTree__
#define __workplace__ABBinaryTree__

#include <iostream>
#include <iomanip>

#include "ABBinaryNode.h"

template <typename Key>
class ABBinaryTree
{
    void display(std::ostream &ostream, ABBinaryNode<Key> *node, int current, int offset = 7)
    {
        if (node)
        {   
            display(ostream, node -> _right, current + offset);
            ostream << std::setw(current) << "(" << node -> _key << " : " << "-" /*node -> _data*/ << ")" << std::endl << std::endl;
            display(ostream, node -> _left, current + offset);
        }
    }
    
    void empty(ABBinaryNode<Key> *&node)
    {
        if (node)
        {
            empty(node -> _left);
            empty(node -> _right);
            delete node;
            node = nullptr;
        }
    }
    
    // TODO:
    ABBinaryNode<Key> *copy(ABBinaryNode<Key> *node)
    {
        return nullptr;
    }
    
protected:
    ABBinaryNode<Key> *_root;
    
public:
    
    ABBinaryTree()
    {
        _root = nullptr;
    }
    
    // TODO:
    ABBinaryTree(const ABBinaryTree &btree)
    {
    }
    
    // TODO:
    ABBinaryTree &operator=(const ABBinaryTree &rhs)
    {
        return *this;
    }
    
    virtual ~ABBinaryTree()
    {
        empty();
    }
    
    void display(std::ostream &ostream)
    {
        display(ostream, _root, 0);
    }
    
    void empty()
    {
        empty(_root);
    }
    
    bool isEmpty()
    {
        return _root == nullptr;
    }
};

#endif /* defined(__workplace__ABBinaryTree__) */
