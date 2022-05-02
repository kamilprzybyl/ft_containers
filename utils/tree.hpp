#ifndef TREE_HPP
#define TREE_HPP

#include "../utils/iterator_traits.hpp"
#include "../utils/iterator.hpp"
#include "../utils/utility.hpp"
#include "../utils/algorithm.hpp"
#include <stddef.h>

#ifndef nullptr
# define nullptr NULL
#endif

template<class T>
struct tree_node
{
	typedef T		value_type;
	value_type		value;
	tree_node		*parent;
	tree_node		*left;
	tree_node		*right;
	bool			is_black;
};


template<typename T, typename container, typename value>
class	tree_iterator {
public:
	typedef	T		tree_node;

	typedef				value							value_type;
	typedef				value_type&						reference;
	typedef				value_type*						pointer;
	typedef				value_type						iterator_category;
	typedef				ptrdiff_t						difference_type;
	typedef	typename	ft::bidirectional_iterator_tag	iterator_catgeory;

private:
	tree_node	_current;

public:
	tree_iterator() : _current() {}
	tree_iterator(const tree_iterator<typename container::node *, container, typename container::value_type> & in) : _current(in.base()) { }
	tree_iterator(tree_node const &in) : _current(in) {}
	virtual ~tree_iterator() {}

	tree_node		&base() { return _current; }
	const tree_node	&base() const { return _current; }

	tree_iterator &operator++()
	{
		if (_current->right != nullptr){
			_current = _current->right;
			while (_current->left) {
				_current = _current->left;
			}
		}
		else {
			tree_node	c = _current;
			_current = _current->parent;
			while (_current->right == c)
			{
				c = _current;
				_current = _current->parent;
			}
		}
		return *this;
	}

	tree_iterator operator++(int)
	{
		tree_iterator tmp = *this;
		++(*this);
		return tmp;
	}

	tree_iterator &operator--()
	{
		if (_current->left != nullptr) {
			_current = _current->left;
			while (_current->right) {
				_current = _current->right;
			}
			
		}
		else {
			tree_node	c = _current;
			_current = _current->parent;
			while (_current->left == c) {
				c = _current;
				_current = _current->parent;
			}
		}
		return *this;
	}

	tree_iterator operator--(int)
	{
		tree_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	tree_iterator	operator-(int const &i) const
	{
		tree_iterator ret = *this;
		for (int j = 0; j < i; j++) {
			ret--;
		}
		return ret;
	}

	tree_iterator	operator+(int const &i) const {
		tree_iterator ret = *this;
		for (int j = 0; j < i; j++) {
			ret++;
		}
		return ret;
	}

	pointer	operator->() { return &(this->operator*()); }
	pointer	operator->() const { return &(this->operator*()); }
	
	bool operator==(tree_iterator const &x) const
		{ return _current == x._current; }
	bool operator!=(tree_iterator const &x) const
		{ return !(*this == x); }

	value_type	&operator*()
		{ return _current->value; }
	value_type	&operator*() const
		{ return _current->value; }
};


template < class T, class Compare = std::less<T>,
		   class Allocator = std::allocator<T> >
class tree
{
public:
	typedef	T																	value_type;
	typedef	Compare																value_compare;
	typedef	Allocator															allocator_type;

	typedef typename Allocator::template rebind<tree_node<value_type> >::other	tree_node_allocator_type;
	typedef	tree_node<value_type>												node;
	typedef	tree_iterator<node *, tree, T>										iterator;
	typedef	tree_iterator<const node *, tree, const T>							const_iterator;
	typedef	ft::reverse_iterator<iterator>										reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>								const_reverse_iterator;
	typedef	size_t																size_type;

private:
	value_compare				_comp;
	allocator_type				_a;
	tree_node_allocator_type	_a_node;
	node						*_root;
	node						_dummy;
	size_type					_size;

// private:
public:
	/*
	void	printTree(const std::string& prefix, node* node, bool left) const
	{
		if( node != NULL )
		{
			std::cout << prefix;

			std::cout << (left ? "├──" : "└──" );

			if (!node->is_black) {
				std::cout << "\033[0;31m";
				std::cout << node->value;
				std::cout << "\033[0m\n";
			}
			else {
				std::cout << node->value;
			}
			std::cout << std::endl;

			printTree(prefix + (left ? "│   " : "    "), node->left, true);
			printTree(prefix + (left ? "│   " : "    "), node->right, false);
		}
	}

	void print()
	{
		this->printTree("", _root, false);
	}
	*/

	node *create_node(const value_type& v)
	{
		node *new_node = _a_node.allocate(1);
		_a.construct(&new_node->value, v);
		new_node->parent = &_dummy;
		new_node->left = nullptr;
		new_node->right = nullptr;
		new_node->is_black = 0;

		return new_node;
	}

	node	*min(node *root) const
	{
		while (root && root->left && root != &_dummy) {
			root = root->left;
		}
		return root;
	}

	void	deleteTree(node *root)
	{
		if (root == nullptr) {
			return ;
		}

		deleteTree(root->left);
		deleteTree(root->right);

		_a.destroy(&root->value);
		_a_node.deallocate(root, 1);
	}

	bool	equals(value_type const &first, value_type const &second) const
		{ return (!_comp(first, second) && !_comp(second, first)); }

	node	*search(node *root, const value_type &v) const
	{
		if (!root) {
			return nullptr;
		}
		if (equals(root->value, v)) {
			return root;
		}
		if (_comp(v, root->value) && root->left == nullptr) {
			return root;
		}
		if (!_comp(v, root->value) && root->right == nullptr) {
			return root;
		}
		if (!_comp(v, root->value)) {
			return search(root->right, v);
		}
		return search(root->left, v);
	}

	void	rightRotate(node *x)
	{
		node	*y = x->left;
		if (x == _root) {
			_root = y;
			_root->parent = &_dummy;
			_dummy.left = _root;
		}
		if (x->parent && x->parent != &_dummy)
		{
			if (x->parent->left == x) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
		}
		y->parent = x->parent;
		x->parent = y;
		x->left = y->right;
		if (x->left) {
			x->left->parent = x;
		}
		y->right = x;
	}

	void	leftRotate(node *x)
	{
		node *y = x->right;
		if (x == _root) {
			_root = y;
			_root->parent = &_dummy;
			_dummy.left = _root;
		}
		if (x->parent && x->parent != &_dummy)
	{
			if (x->parent->left == x) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
		}
		y->parent = x->parent;
		x->parent = y;
		x->right = y->left;
		if (x->right) {
			x->right->parent = x;
		}
		y->left = x;
	}

	//	2. Recolor and rotate nodes to fix violation (covers 4 scenarios)
	void	rb_insert_fixup(node *z)
	{
		node *y;
		while (z->parent && z->parent != &_dummy && !z->parent->is_black)
		{
			if (z->parent == z->parent->parent->left)
			{
				y = z->parent->parent->right;			// z's uncle
				if (y && !y->is_black) {				// case 1: z's uncle is red
					z->parent->is_black = 1;
					y->is_black = 1;
					z->parent->parent->is_black = 0;
					z = z->parent->parent;
				}
				else if (z == z->parent->right) {		// case 2: z's uncle is black (triangle)
					 
					z = z->parent;
					leftRotate(z);
				}
				else {									// case 3: z's uncle is black (line)
					// recolor the original parent and grandparent (switch colors)
					z->parent->is_black = 1;
					z->parent->parent->is_black = 0;
					rightRotate(z->parent->parent);		// rotate z's grandparent
				}
			}
			else
			{
				y = z->parent->parent->left;
				if (y && !y->is_black) {
					z->parent->is_black = 1;
					y->is_black = 1;
					z->parent->parent->is_black = 0;
					z = z->parent->parent;
				}
				else if (z == z->parent->left) {
					z = z->parent;
					rightRotate(z);
				}
				else {
					z->parent->is_black = 1;
					z->parent->parent->is_black = 0;
					leftRotate(z->parent->parent);
				}
			}
		}
		_root->is_black = 1;							// case 0: color z black
	}

	//	1. Insert Z and color it red (simple insertion)
	void	rb_insert(node *z)
	{
		node *y = nullptr;
		node *x = _root;

		while (x != nullptr)
		{
			y = x;
			if (_comp(z->value, x->value)) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		z->parent = y;
		if (y == nullptr) {
			_root = z;
			_root->is_black = 1;
			_root->parent = &_dummy;
			_dummy.left = _root;
		}
		else if (_comp(z->value, y->value)) {
			y->left = z;
		}
		else {
			y->right = z;
		}

		rb_insert_fixup(z);
	}

	// returns pointer to sibling
	node	*sibling(node *x)
	{
		if (x == nullptr || x->parent == nullptr) {
			return nullptr;
		}
		if (x == x->parent->left) {
			return x->parent->right;
		}
		return x->parent->left;
	}

	// find node that do not have a left child
	// in the subtree of the given node
	node	*successor(node *x)
	{
		node *tmp = x;

		while (tmp->left != nullptr) {
			tmp = tmp->left;
		}
		return tmp;
	}

	// find node that replaces a deleted node in the tree
	node	*replace(node *x)
	{
		// when has 2 children
		if (x->left != nullptr && x->right != nullptr)
			return successor(x->right);

		// when leaf
		if (x->left == nullptr && x->right == nullptr)
			return nullptr;

		// when has a 1 child
		if (x->right == nullptr)
			return x->left;
		else
			return x->right;
	}

	void	doubleBlackFixup(node *v)
	{
		if (v == _root) {
			return ;
		}

		node *sibling = this->sibling(v);

		if (sibling == nullptr)
		{
			doubleBlackFixup(v->parent);
		}
		else
		{
			if (!sibling->is_black)
			{
				v->parent->is_black = 0;
				sibling->is_black = 1;
				if (sibling == sibling->parent->left) {
					rightRotate(v->parent);
				}
				else {
					leftRotate(v->parent);
				}
				doubleBlackFixup(v);
			}
			else
			{
				if ((sibling->left && !sibling->left->is_black) || (sibling->right && !sibling->right->is_black))
				{
					if (sibling->left != nullptr && !sibling->left->is_black)
					{
						if (sibling == sibling->parent->left) {
							sibling->left->is_black = sibling->is_black;
							sibling->is_black = v->parent->is_black;
							rightRotate(v->parent);
						}
						else {
							sibling->left->is_black = v->parent->is_black;
							rightRotate(sibling);
							leftRotate(v->parent);
						}
					}
					else
					{
						if (sibling->parent && sibling == sibling->parent->left) {
							sibling->right->is_black = v->parent->is_black;
							leftRotate(sibling);
							rightRotate(v->parent);
						}
						else {
							sibling->right->is_black = sibling->is_black;
							sibling->is_black = v->parent->is_black;
							leftRotate(v->parent);
						}
					}
					v->parent->is_black = 1;
				}
				else {
					sibling->is_black = 0;
					if (v->parent->is_black) {
						doubleBlackFixup(v->parent);
					}
					else {
						v->parent->is_black = 1;
					}
				}
			}
		}
	}

	void	rb_erase(node *v)
	{
		node *u  = replace(v);
		bool uvBlack = ((u == nullptr || u->is_black) && (v->is_black));

		if (u == nullptr) // leaf
		{
			if (v == _root)
			{
				_root = nullptr;
				_dummy.left = &_dummy;
			}
			else
			{
				if (uvBlack == true) {
					doubleBlackFixup(v);
				}
				else {
					if (sibling(v) != nullptr) {
						sibling(v)->is_black = 0;
					}
				}

				if (v == v->parent->left) {
					v->parent->left = nullptr;
				}
				else {
					v->parent->right = nullptr;
				}
			}
			_a.destroy(&v->value);
			_a_node.deallocate(v, 1);
			return ;
		}

		if (v->left == nullptr || v->right == nullptr) // only one child
		{
			if (v == _root)
			{
				_root = u;
				_root->parent = &_dummy;
				u->left = nullptr;
				u->right = nullptr;
				u->is_black = 1;
				_a.destroy(&v->value);
				_a_node.deallocate(v, 1);
			}
			else
			{
				if (v == v->parent->left) {
					v->parent->left = u;
				}
				else {
					v->parent->right = u;
				}
				_a.destroy(&v->value);
				_a_node.deallocate(v, 1);
				u->parent = v->parent;
				if (uvBlack == true) {
					doubleBlackFixup(u);
				}
				else {
					u->is_black = 1;
				}
			}
			return ;
		}
		else {	// two children
			if (v == _root) {
				_root = u;
			}
			if (v->parent && v->parent->left == v) {
				v->parent->left = u;
			} else if (v->parent && v->parent->right == v) {
				v->parent->right = u;
			}
			if (v->right) {
				v->right->parent = u;
			}
			if (v->left) {
				v->left->parent = u;
			}
			if (u->parent && u == u->parent->left) {
				u->parent->left = v;
			}
			if (u->parent && u == u->parent->right) {
				u->parent->right = v;
			}
			ft::swap(u->parent, v->parent);
			ft::swap(u->left, v->left);
			ft::swap(u->right, v->right);
			ft::swap(u->is_black, v->is_black);
			rb_erase(v);
		}
	}

public:
	tree(const value_compare& comp, const allocator_type& a)
		: _comp(comp),
		  _a(a),
		  _a_node(a),
		  _root(nullptr),
		  _dummy(),
		  _size(0)
	{
		_dummy.left = &_dummy;
		_dummy.right = nullptr;
	}

	tree(const tree &x)
		: _comp(x._comp),
		  _a(x._a),
		  _a_node(x._a_node),
		  _root(),
		  _dummy(),
		  _size(0)
	{
		const_iterator it = x.begin();
		while (it != x.end())
		{
			insert(*it);
			++it;
		}
	}

	tree	&operator=(const tree & x) {
		if (this != &x) {
			this->clear();
			_size = 0;
			_comp = x._comp;
			_a = x._a;
			_a_node = x._a_node;
			_root = nullptr;
			const_iterator it = x.begin();
			while (it != x.end())
			{
				insert(*it);
				++it;
			}
		}
		return *this;
	}

	~tree() {}

	iterator begin()
		{return iterator(min(_dummy.left));}
	const_iterator begin() const
		{return const_iterator(min(_dummy.left));}
	iterator end()
		{return iterator(&_dummy);}
	const_iterator end() const
		{return const_iterator(&_dummy);}

	size_type size() const {return _size;}
	size_type max_size() const {return _a_node.max_size();}

	ft::pair<iterator, bool> insert(const value_type& v)
	{
		node	*z;

		z = search(_root, v);
		if (z && equals(v, z->value))
			return ft::make_pair(iterator(z), false);
		z = create_node(v);
		_dummy.left = _root;
		rb_insert(z);
		_size++;

		return ft::make_pair(iterator(z), true);
	}

	size_type 	erase (const value_type& v)
	{
		node	*z = search(_root, v);
		if (!z || !equals(v, z->value))
			return 0;
		rb_erase(z);
		_size--;
		return 1;
	}

	void 		swap (tree& x)
	{
		if (this != &x)
		{
			ft::swap(_dummy.left, x._dummy.left);
			ft::swap(_root, x._root);
			ft::swap(_a, x._a);
			ft::swap(_a_node, x._a_node);
			ft::swap(_comp, x._comp);
			ft::swap(_size, x._size);
			_root->parent = &_dummy;
			x._root->parent = &x._dummy;
		}
	}

	void	clear()
	{
		deleteTree(_root);
		_dummy.left = &_dummy;
		_root = nullptr;
		_size = 0;
	}

	iterator find(const value_type& v)
	{
		node *res = search(_root, v);
		if (!res || !equals(res->value, v))
			return end();
		return iterator(res);
	}

	const_iterator find(const value_type& v) const
	{
		node *res = search(_root, v);
		if (!res || !equals(res->value, v))
			return end();
		return const_iterator(res);
	}
};


#endif