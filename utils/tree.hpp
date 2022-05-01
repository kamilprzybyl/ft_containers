#ifndef TREE_HPP
#define TREE_HPP

#include "../utils/iterator_traits.hpp"
#include "../utils/iterator.hpp"
#include "../utils/utility.hpp"
#include "../utils/algorithm.hpp"

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
	tree_iterator() : _current() { }
	tree_iterator(tree_node const &in) : _current(in) { }
	tree_iterator(const tree_iterator<typename container::node *, container, typename container::value_type> & in) : _current(in.base()) { }

	const tree_node	&base() const { return _current; }

	tree_node	&base() { return _current; }

	tree_iterator &operator++() {
		if (_current->right != nullptr) {
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

	tree_iterator operator++(int) {
		tree_iterator tmp = *this;
		++(*this);
		return tmp;
		// tree_iterator save = _current;
		// if (_current->right != nullptr) {
		// 	_current = _current->right;
		// 	while (_current->left) {
		// 		_current = _current->left;
		// 	}
		// }
		// else {
		// 	tree_node	c = _current;
		// 	_current = _current->parent;
		// 	while (_current->right == c)
		// 	{
		// 		c = _current;
		// 		_current = _current->parent;
		// 	}
		// }
		// return save;
	}

	tree_iterator &operator--() {
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

	tree_iterator operator--(int) {
		// tree_iterator save = _current;
		// if (_current->left != nullptr) {
		// 	_current = _current->left;
		// 	while (_current->right) {
		// 		_current = _current->right;
		// 	}
			
		// }
		// else {
		// 	tree_node	c = _current;
		// 	_current = _current->parent;
		// 	while (_current->left == c) {
		// 		c = _current;
		// 		_current = _current->parent;
		// 	}
		// }
		// return save;
		tree_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	tree_iterator	operator-(int const &i) const {
		tree_iterator ret = *this;
		for (int j = 0; j < i; j++)
		{
			ret--;
		}
		return ret;
	}

	tree_iterator	operator+(int const &i) const {
		tree_iterator ret = *this;
		for (int j = 0; j < i; j++)
		{
			ret++;
		}
		return ret;
	}

	pointer	operator->() { return &(this->operator*()); }
	pointer	operator->() const { return &(this->operator*()); }
	
	bool operator==(tree_iterator const &x) const {
		return _current == x._current;
	}
	bool operator!=(tree_iterator const &x) const {
		return !(*this == x);
	}
	value_type	&operator*() {
		return _current->value;
	}

	value_type	&operator*() const {
		return _current->value;
	}
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

private:
	node *create_node(const value_type& v)
	{
		node *new_node = _a_node.allocate(1);
		_a.construct(&new_node->value, v);
		new_node->parent = &_dummy;
		// new_node->parent = nullptr;
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

	node* clone(node* root)
	{
		if (root == nullptr) {
			return nullptr;
		}
	
		node* root_copy = create_node(root->value);
	
		root_copy->left = clone(root->left);
		root_copy->right = clone(root->right);
	
		return root_copy;
	}

	void	delete_tree(node *root)
	{
		if (root == nullptr) {
			return ;
		}

		delete_tree(root->left);
		delete_tree(root->right);

		_a.destroy(&root->value);
		_a_node.deallocate(root, 1);
	}

	bool	equals(value_type const &first, value_type const &second) const
	{
		return (!_comp(first, second) && !_comp(second, first));
	}

	node	*search(node *root, const value_type &v) const {
		if (!root)
			return nullptr;
		if (equals(root->value, v))
			return root;
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

	// node* deleteNode(node* root, const value_type& v)
	// {
	// 	if (root == NULL) 
	// 		return root;

	// 	if (v.first < root->value.first)
	// 		root->left = deleteNode(root->left, v);
	// 	else if (v.first > root->value.first)
	// 		root->right = deleteNode(root->right, v);
	// 	else {
	// 		if (root->left == NULL && root->right == NULL)
	// 		{
	// 			return nullptr;
	// 		}
	// 		else if (root->left == NULL)
	// 		{
	// 			node *temp = root->right;
	// 			temp->parent = root->parent;
	// 			_a_node.destroy(root);
	// 			_a_node.deallocate(root, 1);
	// 			return temp;
	// 		}
	// 		else if (root->right == NULL)
	// 		{
	// 			node *temp = root->left;
	// 			temp->parent = root->parent;
	// 			_a_node.destroy(root);
	// 			_a_node.deallocate(root, 1);
	// 			return temp;
	// 		}
	// 		else 
	// 		{
	// 			node* temp = min(root->right);
	// 			temp->parent = root->parent;
	// 			_a.construct(&temp->value, temp->value);
	// 			root->right = deleteNode(root->right, temp->value);
	// 		}
	// 	}
	// 	return root;
	// }

	void	rightRotate(node *x)
	{
		if (!x->left)
			return ;
		node	*y = x->left;
		if (x == _root) {
			_root = y;
			_root->parent = &_dummy;
			_dummy.left = _root;
		}
		if (x->parent && x->parent != &_dummy) {
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
		// node *y = x->left;		// y is soon to be parent of x
		// x->left = y->right;		
		// if (y->right != nullptr) {
		// 	y->right->parent = x;
		// }
		// y->parent = x->parent;
		// // if (x->parent == nullptr) {
		// if (x->parent == &_dummy) {
		// 	_root = y;
		// }
		// else if (x == x->parent->left) {
		// 	x->parent->left = y;
		// }
		// else {
		// 	x->parent->right = y;
		// }
		// y->right = x;
		// x->parent = y;
	}

	void	leftRotate(node *x)
	{
		if (!x || !x->right)
			return ;
		node *y = x->right;
		if (x == _root) {
			_root = y;
			_root->parent = &_dummy;
			_dummy.left = _root;
		}
		if (x->parent && x->parent != &_dummy) {
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
		// node *y = x->right;		// y is soon to be parent of x
		// x->right = y->left;		
		// if (y->left != nullptr) {
		// 	y->left->parent = x;
		// }
		// y->parent = x->parent;
		// // if (x->parent == nullptr) {
		// if (x->parent == &_dummy) {
		// 	_root = y;
		// }
		// else if (x == x->parent->left) {
		// 	x->parent->left = y;
		// }
		// else {
		// 	x->parent->right = y;
		// }
		// y->left = x;
		// x->parent = y;
	}

	//	2. Recolor and rotate nodes to fix violation (covers 4 scenarios)
	void	rb_insert_fixup(node *z)
	{
		node *y;
		while (z->parent && z->parent != &_dummy && !z->parent->is_black)
		{
			if (z->parent == z->parent->parent->left)
			{
				// std::cout << "left\n";
				y = z->parent->parent->right;			// z's uncle
				if (y && !y->is_black) {				// case 1: z's uncle is red
					// std::cout << "case 1\n";
					// recolor z's parent, grandparent and uncle
					z->parent->is_black = 1;
					y->is_black = 1;
					z->parent->parent->is_black = 0;
					z = z->parent->parent;
				}
				else if (z == z->parent->right) {		// case 2: z's uncle is black (triangle)
					 
					// std::cout << "case 2\n";
					z = z->parent;
					leftRotate(z);
				}
				else {									// case 3: z's uncle is black (line)
					// recolor the original parent and grandparent (switch colors)
					// std::cout << "case 3\n";
					z->parent->is_black = 1;
					z->parent->parent->is_black = 0;
					rightRotate(z->parent->parent);	// rotate z's grandparent
				}
			}
			else
			{
				// std::cout << "right\n";
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
		_root->is_black = 1;	// case 0: color z black
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
			y->left->parent = y;
		}
		else {
			y->right = z;
			y->right->parent = y;
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
		// if (!x)
		// 	return nullptr;

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

	void	doubleBlackFixup(node *x)
	{
		if (x == _root) {
			return ;
		}

		node *sibling = this->sibling(x);
		node *parent = x->parent; // ?????????

		if (sibling == nullptr)
		{
			doubleBlackFixup(parent);
		}
		else
		{
			// std::cout << "elsse\n";
			// std::cout << "sibling: " << sibling->value << std::endl;
			if (!sibling->is_black)
			{
				parent->is_black = 0;
				sibling->is_black = 1;
				if (sibling == sibling->parent->left) {
					rightRotate(parent);
				}
				else {
					leftRotate(parent);
				}
				doubleBlackFixup(x);
			}
			else
			{
				// std::cout << "is black\n";
				if ((sibling->left && !sibling->left->is_black) || (sibling->right && !sibling->right->is_black))
				{
					// std::cout << "!sibling->left->is_black || !sibling->right->is_black\n";
					if (sibling->left != nullptr && !sibling->left->is_black)
					{
						if (sibling == sibling->parent->left) {
							sibling->left->is_black = sibling->is_black;
							sibling->is_black = parent->is_black;
							rightRotate(parent);
						}
						else {
							sibling->left->is_black = parent->is_black;
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else
					{
						// std::cout << "one of the child is red\n";
						if (sibling->parent && sibling == sibling->parent->left) {
							sibling->right->is_black = parent->is_black;
							leftRotate(sibling);
							rightRotate(parent);
						}
						else {
							sibling->right->is_black = sibling->is_black;
							sibling->is_black = parent->is_black;
							leftRotate(parent);
						}
					}
					parent->is_black = 1;
				}
				else {
					sibling->is_black = 0;
					if (parent->is_black) {
						doubleBlackFixup(parent);
					}
					else {
						parent->is_black = 1;
					}
				}
			}
		}
	}

	void	deleteNode(node *v)
	{
		node *u  = replace(v);
		bool uvBlack = ((u == nullptr || u->is_black) && (v->is_black));
		node *parent = v->parent; // maybe delete it later on, loooks like it's useless

		// std::cout << "v: " << v->value << std::endl;
		// if (u)
		// 	std::cout << "u: " << u->value << std::endl;
		// else
		// 	std::cout << "u: nullptr" << std::endl;
		if (u == nullptr)
		{
			// std::cout << "leaf\n";
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
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
			}
			_a.destroy(&v->value);
			_a_node.deallocate(v, 1);
			return ;
		}

		if (v->left == nullptr || v->right == nullptr) // only one child
		{
			// std::cout << "one child\n";
			if (v == _root)
			{
				_root = u;
				_root->parent = &_dummy;
				u->left = nullptr;
				u->right = nullptr;
				u->is_black = 1;
				_a.destroy(&u->value);
				_a_node.deallocate(u, 1);
			}
			else
			{
				// print();
				// std::cout << "detach\n";
				if (v == v->parent->left) {
					// std::cout << "left\n";
					v->parent->left = u;
				}
				else {
					// std::cout << "right\n";
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
		else {
			// std::cout << "two children\n";
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
			// print();
			ft::swap(u->parent, v->parent);
			ft::swap(u->left, v->left);
			ft::swap(u->right, v->right);
			ft::swap(u->is_black, v->is_black);
			deleteNode(v);
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
		  _size(x._size)
	{
		// _root = clone(x._root);
		// _root->parent = &_dummy;
		// _dummy.left = _root;
	}

	tree	&operator=(const tree & x) {
		if (this != &x) {
			this->clear();
			_size = x._size;
			_comp = x._comp;
			_a = x._a;
			_a_node = x._a_node;
			_root = clone(x._root);
			// _root = x._root;
			// const_iterator it = x.begin();
			// while (it != x.end())
			// {
			// 	insert(*it);
			// 	++it;
			// }
			// insert(x.begin(), x.end());
			_root->parent = &_dummy;
			_dummy.left = _root;
		}
		return *this;
	}

	~tree() {
	}

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
		if (this->find(v) != end())
		{
			node *res = search(_root, v);
			return ft::make_pair(iterator(res), true);
		}
		node *z = create_node(v);
		// if (equals(v, z->value)) {
		// 	return (ft::make_pair(iterator(z), false));
		// }
		_dummy.left = _root;
		rb_insert(z);
		_size++;

		return ft::make_pair(iterator(z), true);
	}

	iterator	insert(iterator position, const value_type &val) {
		return insert(val).first;
		(void)position;
	}

	template<class InputIterator>
		void	insert(InputIterator first, InputIterator last) {
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

	size_type 	erase (const value_type& v)
	{
		// std::cout << "start\n";
		node	*res = search(_root, v);
		// std::cout << "value: " << res->value << std::endl;
		if (!res || !equals(v, res->value))
			return 0;
		// _root = deleteNode(_root, v);
		deleteNode(res);
		_size--;

		return 1;
	}
		void	erase(iterator first, iterator last) {
			while (first != last) {
				deleteNode(first++.base());
				_size--;
			}
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
		delete_tree(_root);
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

	void printBT(const std::string& prefix, node* node, bool isLeft) const
	{
		if( node != NULL )
		{
			std::cout << prefix;

			std::cout << (isLeft ? "├──" : "└──" );

			// print the value of the node
			if (!node->is_black) {
				std::cout << "\033[0;31m";
				std::cout << node->value;
				std::cout << "\033[0m\n";
			}
			else {
				std::cout << node->value;
			}

			std::cout << std::endl;

			// enter the next tree level - left and right branch
			printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
			printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
		}
	}


	void print()
	{
		this->printBT("", _root, false);
	}
};


#endif