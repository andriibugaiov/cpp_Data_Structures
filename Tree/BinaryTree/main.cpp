
#include <iostream>
#include <iomanip>

#include <fstream>

#include <string>
#include <sstream>

#include <algorithm>

using namespace std;

template <typename Key>
class BinaryNode
{
public:
    Key _key;
    int _data;

    int _count;

    BinaryNode *_left;
    BinaryNode *_right;

	BinaryNode(BinaryNode<Key> *sentinel = nullptr)
	{
		_count = 1;
		
		_left = sentinel;
		_right = sentinel;
	}
	
    BinaryNode(Key &key, int &data, BinaryNode<Key> *sentinel = nullptr)
    {
        _key = key;
        _data = data;

        _count = 1;

        _left = sentinel;
        _right = sentinel;
    }
    
    virtual ~BinaryNode()
    {
    }
};

// mark -

template <typename Key>
class BinaryTree
{
    void display(std::ostream &ostream, BinaryNode<Key> *node, int current, int offset = 7)
    {
        if (node != _sentinel)
        {
            display(ostream, node -> _right, current + offset);
            ostream << std::setw(current)
			<< "(" << node -> _key << " : "
			<< node -> _data << " : "
			<< node -> _count << ")"
			<< std::endl << std::endl;
            display(ostream, node -> _left, current + offset);
        }
    }

protected:
    
    bool isRoot(BinaryNode<Key> *node)
    {
        return (node == _root);
    }
	
	virtual void empty(BinaryNode<Key> *&node)
	{
		if (node != _sentinel)
		{
			empty(node -> _left);
			empty(node -> _right);
			delete node;
			node = nullptr;
		}
	}

	BinaryNode<Key> *_root;
	BinaryNode<Key> *_sentinel;
	
public:

    BinaryTree(bool sentinel = false)
    {
		if (sentinel)
		{
			_sentinel = new BinaryNode<Key>();
			_sentinel -> _left = _sentinel;
			_sentinel -> _right = _sentinel;
		}
		else
			_sentinel = nullptr;
		
		_root = _sentinel;
    }

    virtual ~BinaryTree()
    {
        empty();
		if (_sentinel)
			delete _sentinel;
    }

    void display(std::ostream &ostream)
    {
        display(ostream, _root, 0);
    }

    virtual void empty()
    {
        empty(_root);
		_root = _sentinel;
    }

    bool isEmpty()
    {
        return _root == _sentinel;
    }
   
// mark - encoding/decoding
	
// mark - from
	
	void popNode(ostream &ostream, char *idStack, BinaryNode<Key> **stack, int &sp)
	{
		char popNodeId = idStack[sp - 1];
		idStack[sp - 1] = '\0';
		BinaryNode<Key> *popNode = stack[sp - 1];
		stack[sp - 1] = nullptr;
		--sp;
		
		ostream << popNodeId
		<< "," << popNode -> _key
		<< "," << popNode -> _data << endl;
		
		delete popNode;
	}
	
	void fromInfixToPostfix(istream &istream, ostream &ostream)
	{
		BinaryNode<Key> *stack[100];
		char idStack[100];
		int sp = 0;
		stack[sp] = nullptr;
		idStack[sp] = '\0';

		char id = istream.get();
		while (!istream.eof())
		{
//			cout << id << endl;
			istream.ignore(1);
			
			if (id == '(')
			{
				stack[sp] = nullptr;
				idStack[sp] = id;
				sp++;
			}
			else if (id == ')')
			{
				while (idStack[sp - 1] != '(')
					popNode(ostream, idStack, stack, sp);
				
				idStack[sp - 1] = '\0';
				stack[sp - 1] = nullptr;
				--sp;
			}
			else
			{
				Key key;
				istream >> key;
				istream.ignore(1);
				
				int data;
				istream >> data;
				istream.ignore(1);
				
				if (id == 'T')
				{
					ostream << id
					<< "," << key
					<< "," << data << endl;
				}
				else
				{
					stack[sp] = new BinaryNode<Key>(key, data);;
					idStack[sp] = id;
					sp++;
				}
			}
			id = istream.get();
		}
		
		while (sp)
			popNode(ostream, idStack, stack, sp);
	}
	
	void fromInfix(istream &istream)
	{
		stringstream ss(ios::in | ios::out);
		
		fromInfixToPostfix(istream, ss);
//		cout << endl << ss.str() << endl;
		fromPostfix(ss);
	}
	
	void fromPostfix(istream &istream)
	{
		BinaryNode<Key> *stack[100];
		int sp = 0;
		stack[sp] = nullptr;
		
		char id = istream.get();
		while (!istream.eof())
		{
			istream.ignore(1);
			
			Key key;
			istream >> key;
			istream.ignore(1);
			
			int data;
			istream >> data;
			istream.ignore(1);
			
			BinaryNode<Key> *node = new BinaryNode<Key>(key, data);
			switch (id)
			{
				case 'T':
				{
					break;
				}
				case 'B':
				{
					node -> _right = stack[--sp];
					node -> _left = stack[--sp];
					break;
				}
				case 'L':
				{
					node -> _left = stack[--sp];
					break;
				}
				case 'R':
				{
					node -> _right = stack[--sp];
					break;
				}
				default:
					throw runtime_error("Unknown binary node id.");
					break;
			}
			stack[sp++] = node;
			id = istream.get();
		}
		
		if (sp != 1)
			throw runtime_error("Decoding algorithm failure.");
		else
			_root = stack[--sp];
	}
	
// mark - to
	
	char nodeId(BinaryNode<Key> *node)
	{
		char id = '-';
		if (!node -> _left && !node -> _right)
			id = 'T'; // Terminating Leaf
		else if (node -> _left && node -> _right)
			id = 'B'; // Binary Node
		else if (node -> _left && !node -> _right)
			id = 'L'; // Left Unary Node
		else if (!node -> _left && node -> _right)
			id = 'R'; // Right Unary Node
		return id;
	}
	
	// inordered binary tree traversal
	void toInfix(ostream &ostream, BinaryNode<Key> *node)
	{
		if (!node)
			return;
		
		char id = nodeId(node);
		
		if (id == 'B' || id == 'L')
			ostream << "(" << endl;
		
		toInfix(ostream, node -> _left);
		
		if (id == 'L')
			ostream << ")" << endl;
		
		ostream << id << ","
		<< node -> _key << ","
		<< node -> _data << endl;
		
		if (id == 'R')
			ostream << "(" << endl;
		
		toInfix(ostream, node -> _right);
		
		if (id == 'B' || id == 'R')
			ostream << ")" << endl;
	}
	
	// postordered binary tree traversal
	void toPostfix(ostream &ostream, BinaryNode<Key> *node)
	{
		if (!node)
			return;
		
		toPostfix(ostream, node -> _left);
		toPostfix(ostream, node -> _right);
		
		char id = nodeId(node);
		ostream << id << ","
		<< node -> _key << ","
		<< node -> _data << endl;
	}
	
	void toInfix(ostream &ostream)
	{
		toInfix(ostream, _root);
	}
	
	void toPostfix(ostream &ostream)
	{
		toPostfix(ostream, _root);
	}
	
// mark -
	
    void encode(bool isPostfix = true)
    {
        ofstream ofs("Encoded_BinaryTree.txt", ios::trunc);
        if (ofs.is_open())
        {
			if (isPostfix)
	            toPostfix(ofs);
			else
				toInfix(ofs);
            ofs.close();
        }
        else
            cout << "Failed to open file" << endl;
    }
	
    void decode(bool isPostfix = true)
    {
        ifstream ifs("Encoded_BinaryTree.txt");
        if (ifs.is_open())
        {
            empty();
			if (isPostfix)
				fromPostfix(ifs);
			else
				fromInfix(ifs);
            ifs.close();
        }
        else
            cout << "Failed to open file" << endl;
    }
	
// mark - encoding/decoding
	
};

// mark -

template <typename Key, typename Comparator = std::less<Key>>
class BinarySearchTree : public BinaryTree<Key>
{
    int remove(BinaryNode<Key> *&node, Key &key)
    {
        if (node == this -> _sentinel)
            return INT32_MAX;

        if (_cmp(key, node -> _key))
            return remove(node -> _left, key);
        else if (_cmp(node -> _key, key))
            return remove(node -> _right, key);
        else if (node -> _left != this -> _sentinel &&
				 node -> _right != this -> _sentinel)
        {
            BinaryNode<Key> *temp = removeMin(node -> _right);
            int data = node -> _data;
            node -> _data = temp -> _data;
            node -> _key = temp -> _key;
            delete temp;
            return data;
        }
        else
        {
            BinaryNode<Key> *temp = remove(node);
            int data = temp -> _data;
            delete temp;
            return data;
        }
    }

    // node here is not NULL
    BinaryNode<Key> *removeMin(BinaryNode<Key> *&node)
    {
        if (node -> _left != this -> _sentinel)
            return removeMin(node -> _left);
        return remove(node);
    }

    // node here is not NULL
    // one child at least is NULL
    BinaryNode<Key> *remove(BinaryNode<Key> *&node)
    {
        BinaryNode<Key> *temp = node;
        if (node -> _left != this -> _sentinel)
            node = node -> _left;
        else
            node = node -> _right;
        return temp;
    }

protected:
	
	virtual void rotateWithLeftChild(BinaryNode<Key> *&node)
	{
		BinaryNode<Key> *left = node -> _left;
		node -> _left = left -> _right;
		left -> _right = node;
		
		node = left;
	}
	
	virtual void rotateWithRightChild(BinaryNode<Key> *&node)
	{
		BinaryNode<Key> *right = node -> _right;
		node -> _right = right -> _left;
		right -> _left = node;
		
		node = right;
	}
	
	virtual void insert(BinaryNode<Key> *&node, Key &key, int &data)
	{
		if (node == this -> _sentinel)
			node = new BinaryNode<Key>(key, data);
		else if (_cmp(key, node -> _key))
			insert(node -> _left, key, data);
		else if (_cmp(node -> _key, key))
			insert(node -> _right, key, data);
		else
			++node -> _count;
	}
	
    virtual BinaryNode<Key> *find(BinaryNode<Key> *node, Key &key)
    {
        if (node == this -> _sentinel)
            return node;
        
        if (_cmp(key, node -> _key))
            return find(node -> _left, key);
        else if (_cmp(node -> _key, key))
            return find(node -> _right, key);
        else
            return node;
    }
	
	BinaryNode<Key> *findMin(BinaryNode<Key> *node)
	{
		if (node != this -> _sentinel)
			while (node -> _left)
				node = node -> _left;
		return node;
	}
	
	BinaryNode<Key> *findMax(BinaryNode<Key> *node)
	{
		if (node != this -> _sentinel)
			while (node -> _right)
				node = node -> _right;
		return node;
	}
	
    Comparator _cmp;
	
public:
	
    BinarySearchTree(bool sentinel = false) : BinaryTree<Key>(sentinel)
    {
    }

    virtual ~BinarySearchTree()
    {
    }

    virtual void insert(Key &key, int &data)
    {
        insert(this -> _root, key, data);
    }

    virtual int find(Key &key)
    {
        BinaryNode<Key> *node = find(this -> _root, key);
        return (node != this -> _sentinel ? node -> _data : INT32_MAX);
    }

    virtual int remove(Key &key)
    {
        int data = remove(this -> _root, key);
        return data;
    }
};

// mark -

void binarySearchTree()
{
    BinarySearchTree<int> bstree;
    
    int keys[] = {10, 11, 15, 8, 3, 5, 9, 18, 2};
    int size = sizeof(keys) / sizeof(keys[0]);
    
    int T = size;
    while (T--)
    {
        int key = keys[T];
        int data = 0;
        bstree.insert(key, data);
    }
    
    cout << "Printing tree..." << endl << endl;
    bstree.display(cout);
	
// mark -
    
    bstree.encode(false);
    bstree.decode(false);
	
	bstree.toPostfix(cout);
	
	ofstream oinfix("Infix.txt", ios::trunc);
	bstree.toInfix(oinfix);
	oinfix.close();
	
	cout << endl;
	
	ifstream iinfix("Infix.txt");
	if (iinfix.is_open())
		bstree.fromInfixToPostfix(iinfix, cout);
	iinfix.close();
	
// mark -
	
    cout << "Printing tree..." << endl << endl;
    bstree.display(cout);
}

// mark -

template <typename Key>
class AVLBinaryNode : public BinaryNode<Key>
{
    AVLBinaryNode()
    {
    }
    
public:
    int _height;
    
    AVLBinaryNode(Key &key, int &data, BinaryNode<Key> *sentinel = nullptr) : BinaryNode<Key>(key, data, sentinel)
    {
        _height = 0;
    }
    
    virtual ~AVLBinaryNode()
    {
    }
    
    AVLBinaryNode<Key> *getLeft()
    {
        return static_cast<AVLBinaryNode<Key> *>(this -> _left);
    }
    
    AVLBinaryNode<Key> *getRight()
    {
        return static_cast<AVLBinaryNode<Key> *>(this -> _right);
    }
};

// mark -

template <typename Key, typename Comparator = std::less<Key>>
class AVLBinarySearchTree : public BinarySearchTree<Key, Comparator>
{
    AVLBinaryNode<Key> *getRoot()
    {
        return static_cast<BinaryNode<Key> *>(this -> _root);
    }
    
    int height(AVLBinaryNode<Key> *node)
    {
        if (node != this -> _sentinel)
            return node -> _height;
        return -1;
    }
	
protected:
	
	virtual void rotateWithLeftChild(BinaryNode<Key> *&node)
	{
		BinarySearchTree<Key, Comparator>::rotateWithLeftChild(node);

		AVLBinaryNode<Key> *pNode = static_cast<AVLBinaryNode<Key> *>(node);
		
		pNode -> getRight() -> _height = max(height(pNode -> getRight() -> getLeft()),
											 height(pNode -> getRight() -> getRight())) + 1;
		pNode -> _height = max(height(pNode -> getLeft()), height(pNode -> getRight())) + 1;
	}
	
	virtual void rotateWithRightChild(BinaryNode<Key> *&node)
	{
		BinarySearchTree<Key, Comparator>::rotateWithRightChild(node);

		AVLBinaryNode<Key> *pNode = static_cast<AVLBinaryNode<Key> *>(node);
		pNode -> getLeft() -> _height = max(height(pNode -> getLeft() -> getLeft()),
											height(pNode -> getLeft() -> getRight())) + 1;
		pNode -> _height = max(height(pNode -> getLeft()),
							   height(pNode -> getRight())) + 1;
	}
	
    virtual void insert(BinaryNode<Key> *&node, Key &key, int &data)
    {
		AVLBinaryNode<Key> *pNode = static_cast<AVLBinaryNode<Key> *>(node);
		
        if (pNode == this -> _sentinel)
           node = pNode = new AVLBinaryNode<Key>(key, data, this -> _sentinel);
        else if (this -> _cmp(key, pNode -> _key))
        {
            insert(pNode -> _left, key, data);
            
            if (height(pNode -> getLeft()) - height(pNode -> getRight()) == 2)
            {
                if (this -> _cmp(key, pNode -> _left -> _key))
                {
                    rotateWithLeftChild(node);
                }
                else if (this -> _cmp(pNode -> _left -> _key, key))
                {
                    rotateWithRightChild(pNode -> _left);
                    rotateWithLeftChild(node);
                }
            }
        }
        else if (this -> _cmp(pNode -> _key, key))
        {
            insert(pNode -> _right, key, data);
            
            if (height(pNode -> getRight()) - height(pNode -> getLeft()) == 2)
            {
                if (this -> _cmp(key, pNode -> _right -> _key))
                {
                    rotateWithLeftChild(pNode -> _right);
                    rotateWithRightChild(node);
                }
                else if (this -> _cmp(pNode -> _right -> _key, key))
                {
                    rotateWithRightChild(node);
                }
            }
        }
        else
            ++pNode -> _count;
        pNode -> _height = max(height(pNode -> getLeft()), height(pNode -> getRight())) + 1;
    }
    
public:
	
    AVLBinarySearchTree():BinarySearchTree<Key, Comparator>(true)
    {
    }
    
    virtual ~AVLBinarySearchTree()
    {
    }

    virtual int remove(Key &key)
    {
        // TODO:
        return 0;
    }
};

// mark -

void avlBinarySearchTree()
{
	BinarySearchTree<int> *bstree = new AVLBinarySearchTree<int>();
    
    int keys[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 9, 8};
    int size = sizeof(keys) / sizeof(keys[0]);
    
    int T = -1;
    while (++T < size)
    {
        int key = keys[T];
        int data = 0;
        bstree -> insert(key, data);
        
        cout << "Printing tree..." << endl << endl;
        bstree -> display(cout);
    }
	
	delete bstree;
}

// mark -

template <typename Key, typename Comparator = less<Key>>
class TopDownSplayBinarySearchTree : public BinarySearchTree<Key, Comparator>
{
	void splay(BinaryNode<Key> *&node, Key &key)
	{
		BinaryNode<Key> *maxLeft, *minRight;
		BinaryNode<Key> head(this -> _sentinel);
		maxLeft = minRight = &head;
		
		this -> _sentinel -> _key = key;
		
		while (true)
		{
			if (this -> _cmp(key, node -> _key))
			{
				if (this -> _cmp(key, node -> _left -> _key))
					BinarySearchTree<Key, Comparator>::rotateWithLeftChild(node);
				
				// if node's left child is equal to sentinel,
				// then the above rotation will not be performed
				
				// else, the rotaion is performed and
				// the node becomes its left child
				
				// if the new node's left child is equal to sentinel,
				// then the cycle is broken
				
				if (node -> _left == this -> _sentinel)
					break;
				
				minRight -> _left = node;
				minRight = minRight -> _left;
				node = node -> _left;
				// there is no need to set minRight's left
				// child to point to sentinel here
			}
			else if (this -> _cmp(node -> _key, key))
			{
				if (this -> _cmp(node -> _right -> _key, key))
					BinarySearchTree<Key, Comparator>::rotateWithRightChild(node);
					
				if (node -> _right == this -> _sentinel)
					break;
				
				maxLeft -> _right = node;
				maxLeft = maxLeft -> _right;
				node = node -> _right;
			}
			else
				break;
		}
		
		// when the while cycle terminates, to cases are possible
		// - node may point to the dyplicate node (keys are equal)
		// - node may point to the node which has the next node (left,
		// when key is less then node's key, or right, when key is
		// greater then node's key) on the search path equal to sentinel
		
		maxLeft -> _right = node -> _left;
		minRight -> _left = node -> _right;
		node -> _left = head._right;
		node -> _right = head._left;
	}
		
public:
	
	TopDownSplayBinarySearchTree() : BinarySearchTree<Key, Comparator>(true)
	{
	}
	
	virtual ~TopDownSplayBinarySearchTree()
	{
	}
	
	virtual void insert(Key &key, int &data)
	{
		static BinaryNode<Key> *newNode = nullptr;
		
		if (!newNode)
			newNode = new BinaryNode<Key>(this -> _sentinel);
		newNode -> _key = key;
		newNode -> _data = data;
		
		if (this -> _root == this -> _sentinel)
		{
			this -> _root = newNode;
			newNode = nullptr;
		}
		else
		{
			splay(this -> _root, key);
			if (this -> _cmp(key, this -> _root -> _key))
			{
				newNode -> _left = this -> _root -> _left;
				newNode -> _right = this -> _root;
				this -> _root -> _left = this -> _sentinel;
				this -> _root = newNode;
				newNode = nullptr;
			}
			else if (this -> _cmp(this -> _root -> _key, key))
			{
				newNode -> _left = this -> _root;
				newNode -> _right = this -> _root -> _right;
				this -> _root -> _right = this -> _sentinel;
				this -> _root = newNode;
				newNode = nullptr;
			}
			else
				++this -> _root -> _count;
			
		}
	}
	
	virtual int find(Key &key)
	{
		splay(this -> _root, key);
		
		int data = INT32_MAX;
		
		if (this -> _root != this -> _sentinel)
		if (!(this -> _cmp(key, this -> _root -> _key) ||
			  this -> _cmp(this -> _root -> _key, key)))
			data = this -> _root -> _data;

		return data;
	}
	
	virtual int remove(Key &key)
	{
		splay(this -> _root, key);
		
		int data = INT32_MAX;
		
		if (this -> _root != this -> _sentinel)
			if (!(this -> _cmp(key, this -> _root -> _key) ||
				  this -> _cmp(this -> _root -> _key, key)))
			{
				data = this -> _root -> _data;
				
				BinaryNode<Key> *newRoot = nullptr;
				if (this -> _root -> _left == this -> _sentinel)
				{
					newRoot = this -> _root -> _right;
				}
				else
				{
					newRoot = this -> _root -> _left;
					splay(newRoot, key);
					
					if (newRoot -> _right != this -> _sentinel)
						throw runtime_error("Error");

					newRoot -> _right = this -> _root -> _right;
				}
				delete this -> _root;
				this -> _root = newRoot;
			}
		
		return data;
	}
};

// mark -

void topDownSplayBinarySearchTree()
{
	BinarySearchTree<int> *stree = new TopDownSplayBinarySearchTree<int>();
	
	int keys[] = {3, 2, 1, 4, 5, 5, 3,  6, 7, 16, 15, 14, 13, 12, 11, 10, 9, 8};
	int size = sizeof(keys) / sizeof(keys[0]);
	
	int T = -1;
	while (++T < size)
	{
		int key = keys[T];
		int data = 0;
		stree -> insert(key, data);
		
		cout << "Printing tree..." << endl << endl;
		stree -> display(cout);
	}
	
	int key = 16;
	cout << "Finding key..." << key << endl << endl;
	stree -> find(key);
	cout << "Printing tree..." << endl << endl;
	stree -> display(cout);
	
	delete stree;
}

// mark -

template <typename Key>
class SplayBinaryNode : public BinaryNode<Key>
{
public:
    BinaryNode<Key> *_parent;
    
    SplayBinaryNode(Key &key, int &data, BinaryNode<Key> *sentinel = nullptr) : BinaryNode<Key>(key, data, sentinel)
    {
        _parent = sentinel;
    }
    
    virtual ~SplayBinaryNode()
    {
    }
    
    SplayBinaryNode<Key> *getLeft()
    {
        return static_cast<SplayBinaryNode<Key> *>(this -> _left);
    }
    
    SplayBinaryNode<Key> *getRight()
    {
        return static_cast<SplayBinaryNode<Key> *>(this -> _right);
    }

    SplayBinaryNode<Key> *getParent()
    {
        return static_cast<SplayBinaryNode<Key> *>(this -> _parent);
    }
};

// mark -

template <typename Key, typename Comparator = less<Key>>
class SplayBinarySearchTree : public BinarySearchTree<Key, Comparator>
{
    SplayBinaryNode<Key> *getRoot()
    {
        return static_cast<SplayBinaryNode<Key> *>(this -> _root);
    }
    
    SplayBinaryNode<Key> *rotateWithRightChild(SplayBinaryNode<Key> *node)
    {
        SplayBinaryNode<Key> *parent = node -> getParent();
        SplayBinaryNode<Key> *right = node -> getRight();
        
        node -> _right = right -> getLeft();
        if (node -> getRight() != this -> _sentinel)
            node -> getRight() -> _parent = node;
        
        right -> _left = node;
        right -> getLeft() -> _parent = right;
        
        right -> _parent = parent;
        if(right -> getParent() != this -> _sentinel)
        {
            if (right -> getParent() -> _left == node)
                right -> getParent() -> _left = right;
            else if (right -> getParent() -> _right == node)
                right -> getParent() -> _right = right;
            else
                throw runtime_error("Error!");
        }
        else
            this -> _root = right;
        
        return right;
    }
    
    SplayBinaryNode<Key> *rotateWithLeftChild(SplayBinaryNode<Key> *node)
    {
        SplayBinaryNode<Key> *parent = node -> getParent();
        SplayBinaryNode<Key> *left = node -> getLeft();
        
        node -> _left = left -> getRight();
        if (node -> getLeft() !=  this -> _sentinel)
            node -> getLeft() -> _parent = node;
        
        left -> _right = node;
        left -> getRight() -> _parent = left;
        
        left -> _parent = parent;
        if (left -> getParent() != this -> _sentinel)
        {
            if (left -> getParent() -> _left == node)
                left -> getParent() -> _left = left;
            else if (left -> getParent() -> _right == node)
                left -> getParent() -> _right = left;
            else
                throw runtime_error("Error!");
        }
        else
            this -> _root = left;
        
        return left;
    }
    
    void splay(SplayBinaryNode<Key> *node)
    {
        while (!this -> isRoot(node))
        {
            // parent is not NULL
            SplayBinaryNode<Key> *parent = node -> getParent();
            if (this -> isRoot(parent))
            {
                if (parent -> _left == node)
                {
                    parent = rotateWithLeftChild(parent);
                    if (node != parent)
                       throw runtime_error("Error!");
                }
                else if (parent -> _right == node)
                {
                    parent = rotateWithRightChild(parent);
                    if (node != parent)
                        throw runtime_error("Error!");
                }
                else
                    throw runtime_error("Error!");
            }
            else
            {
                // gParent is not NULL
                SplayBinaryNode<Key> *gParent = parent -> getParent();
                if (gParent -> _left == parent) // left
                {
                    if (parent -> _left == node) // left
                    {
                        gParent = rotateWithLeftChild(gParent);
                        if (parent != gParent)
                            throw runtime_error("Error!");
                        
                        parent = rotateWithLeftChild(parent);
                        if (node != parent)
                            throw runtime_error("Error!");
                    }
                    else if (parent -> _right == node) // right
                    {
                        parent = rotateWithRightChild(parent);
                        if (node != parent)
                            throw runtime_error("Error!");
                        
                        // parent is node
                        gParent = rotateWithLeftChild(gParent);
                        if (parent != gParent)
                            throw runtime_error("Error!");
                    }
                    else
                        throw runtime_error("Error!");
                }
                else if (gParent -> _right == parent) // right
                {
                    if (parent -> _left == node) // left
                    {
                        parent = rotateWithLeftChild(parent);
                        if (node != parent)
                            throw runtime_error("Error!");
                        
                        // parent is node
                        gParent = rotateWithRightChild(gParent);
                        if (parent != gParent)
                            throw runtime_error("Error!");
                    }
                    else if (parent -> _right == node) // right
                    {
                        gParent = rotateWithRightChild(gParent);
                        if (parent != gParent)
                            throw runtime_error("Error!");
                        
                        parent = rotateWithRightChild(parent);
                        if (node != parent)
                            throw runtime_error("Error!");
                    }
                }
                else
                    throw runtime_error("Error!");
            }
        }
    }
    
public:
    
    SplayBinarySearchTree() : BinarySearchTree<Key, Comparator>(true)
    {
    }
    
    virtual ~SplayBinarySearchTree()
    {
    }
    
    virtual void insert(Key &key, int &data)
    {
        BinaryNode<Key> *parent = this -> _sentinel;
        SplayBinaryNode<Key> *node = getRoot();
        
        while (node != this -> _sentinel)
        {
            if (this -> _cmp(key, node -> _key))
            {
                parent = node;
                node = node -> getLeft();
            }
            else if (this -> _cmp(node -> _key, key))
            {
                parent = node;
                node = node -> getRight();
            }
            else
            {
                ++node -> _count;
                break;
            }
        }
        
        if (parent == this -> _sentinel && node == this -> _sentinel)
            this -> _root = new SplayBinaryNode<Key>(key, data, this -> _sentinel);
        else if (node == this -> _sentinel)
        {
            node = new SplayBinaryNode<Key>(key, data, this -> _sentinel);
            if (this -> _cmp(key, parent -> _key))
                parent -> _left = node;
            else if (this -> _cmp(parent -> _key, key))
                parent -> _right = node;
            else
                throw runtime_error("Error!");
            node -> _parent = parent;
        }
        
        if (node != this -> _sentinel)
            splay(node);
    }
    
    virtual int find(Key &key)
    {
        BinaryNode<Key> *node = BinarySearchTree<Key, Comparator>::find(this -> _root, key);
        SplayBinaryNode<Key> *cNode = static_cast<SplayBinaryNode<Key> *>(node);
        
        if (cNode != this -> _sentinel)
            splay(cNode);
        
        return (cNode != this -> _sentinel) ? cNode -> _data : INT32_MAX;
    }
    
    virtual int remove(Key &key)
    {
        // TODO:
        return 0;
    }
};

// mark -

void splayBinarySearchTree()
{
    BinarySearchTree<int> *stree = new SplayBinarySearchTree<int>();

    int keys[] = {3, 2, 1, 4, 5, 5, 3,  6, 7, 16, 15, 14, 13, 12, 11, 10, 9, 8};
    int size = sizeof(keys) / sizeof(keys[0]);

    int T = -1;
    while (++T < size)
    {
        int key = keys[T];
        int data = 0;
        stree -> insert(key, data);

        cout << "Printing tree..." << endl << endl;
        stree -> display(cout);
    }

    int key = 16;
    cout << "Finding key..." << key << endl << endl;
    stree -> find(key);
    cout << "Printing tree..." << endl << endl;
    stree -> display(cout);

    delete stree;
}

// mark -

int main()
{
//	topDownSplayBinarySearchTree();
	splayBinarySearchTree();
//	avlBinarySearchTree();
    return 0;
}































// -
