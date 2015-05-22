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

template <typename Key>
class ABBinaryNode
{
public:
    Key _key;
    int _data;
    
    int _count;
    
    ABBinaryNode *_left;
    ABBinaryNode *_right;
    
    ABBinaryNode(Key &key, int &data)
    {
        _key = key;
        _data = data;
        
        _count = 1;
        
        _left = nullptr;
        _right = nullptr;
    }
};

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
    
protected:
    ABBinaryNode<Key> *_root;
    
public:
    
    ABBinaryTree()
    {
        _root = nullptr;
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

template <typename Key, typename Comparator = std::less<Key>>
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
    
    // node here is not degenerated
    ABBinaryNode<Key> *removeMin(ABBinaryNode<Key> *&node)
    {
        if (node -> _left)
            return removeMin(node -> _left);
        return remove(node);
    }
    
    // node here is not NULL
    // one child at least is NULL
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
    
    ~ABBinarySearchTree()
    {
        // todo
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

#endif /* defined(__workplace__ABBinaryTree__) */
