//
//  ABBinarySearchTree.h
//  workplace
//
//  Created by Andrii Bugaiov on 2015-05-22.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#ifndef __workplace__ABBinarySearchTree__
#define __workplace__ABBinarySearchTree__

#include "ABBinaryTree.h" 

class Cmp
{
public:
    bool operator()(const int &lhs, const int &rhs) const
    {
        return lhs < rhs;
    }
};

// mark -

template <typename Key = int, typename Comparator = std::less<Key>>
class ABBinarySearchTree : public ABBinaryTree<Key>
{
    void insert(ABBinaryNode<Key> *&node, Key &key, int &data)
    {
        if (!node)
            node = new ABBinaryNode<Key>(key, data);
        else if (cmp(key, node -> _key))
            insert(node -> _left, key, data);
        else if (cmp(node -> _key, key))
            insert(node -> _right, key, data);
        else
            ++node -> _count;
    }
    
    ABBinaryNode<Key> *find(ABBinaryNode<Key> *node, Key &key)
    {
        if (!node)
            return node;
        
        if (cmp(key, node -> _key))
            return find(node -> _left, key);
        else if (cmp(node -> _key, key))
            return find(node -> _right, key);
        else
            return node;
    }
    
    ABBinaryNode<Key> *findMin(ABBinaryNode<Key> *node)
    {
        if (node)
            while (node -> _left)
                node = node -> _left;
        return node;
    }
    
    ABBinaryNode<Key> *findMax(ABBinaryNode<Key> *node)
    {
        if (node)
            while (node -> _right)
                node = node -> _right;
        return node;
    }
    
    int remove(ABBinaryNode<Key> *&node, Key &key)
    {
        if (!node)
            return INT32_MAX;
        
        if (cmp(key, node -> _key))
            return remove(node -> _left, key);
        else if (cmp(node -> _key, key))
            return remove(node -> _right, key);
        else if (node -> _left && node -> _right)
        {
            ABBinaryNode<Key> *temp = removeMin(node -> _right);
            int data = node -> _data;
            node -> _data = temp -> _data;
            node -> _key = temp -> _key;
            delete temp;
            return data;
        }
        else
        {
            ABBinaryNode<Key> *temp = remove(node);
            int data = temp -> _data;
            delete temp;
            return data;
        }
    }
    
    // node here is not nullptr
    ABBinaryNode<Key> *removeMin(ABBinaryNode<Key> *&node)
    {
        if (node -> _left)
            return removeMin(node -> _left);
        return remove(node);
    }
    
    // node here is not nullptr
    // one child at least is nullptr
    ABBinaryNode<Key> *remove(ABBinaryNode<Key> *&node)
    {
        ABBinaryNode<Key> *temp = node;
        
        if (node -> _left)
            node = node -> _left;
        else
            node = node -> _right;
        
        return temp;
    }
    
    Comparator cmp;
    
public:
    ABBinarySearchTree() : ABBinaryTree<Key>()
    {
    }
    
    // TODO:
    ABBinarySearchTree(const ABBinarySearchTree &bstree)
    {
        
    }
    
    // TODO:
    ABBinarySearchTree &operator=(const ABBinarySearchTree &rhs)
    {
        return *this;
    }

    
    // TODO:
    ~ABBinarySearchTree()
    {
    }
    
    void insert(Key &key, int &data)
    {
        insert(this -> _root, key, data);
    }
    
    int find(Key &key)
    {
        ABBinaryNode<Key> *node = find(this -> _root, key);
        return node ? node -> _data : INT32_MAX;
    }
    
    int remove(Key &key)
    {
        int data = remove(this -> _root, key);
        return data;
    }
};


#endif /* defined(__workplace__ABBinarySearchTree__) */
