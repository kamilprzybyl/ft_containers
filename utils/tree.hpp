#ifndef TREE_HPP
#define TREE_HPP

#include "../utils/iterator_traits.hpp"
#include "../utils/iterator.hpp"
#include "../utils/utility.hpp"

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
		return (ret);
	}

	tree_iterator	operator+(int const &i) const {
		tree_iterator ret = *this;
		for (int j = 0; j < i; j++)
		{
			ret++;
		}
		return (ret);
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

	void	swapValues(node *a, node *b)
	{
		int tmp;

		tmp = a->value;
		a->value = b->value;
		b->value = tmp;
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

	node* deleteNode(node* root, const value_type& v)
	{
		if (root == NULL) 
			return root;

		if (v.first < root->value.first)
			root->left = deleteNode(root->left, v);
		else if (v.first > root->value.first)
			root->right = deleteNode(root->right, v);
		else {
			if (root->left == NULL && root->right == NULL)
			{
				return nullptr;
			}
			else if (root->left == NULL)
			{
				node *temp = root->right;
				temp->parent = root->parent;
				_a_node.destroy(root);
				_a_node.deallocate(root, 1);
				return temp;
			}
			else if (root->right == NULL)
			{
				node *temp = root->left;
				temp->parent = root->parent;
				_a_node.destroy(root);
				_a_node.deallocate(root, 1);
				return temp;
			}
			else 
			{
				node* temp = min(root->right);
				temp->parent = root->parent;
				_a.construct(&temp->value, temp->value);
				root->right = deleteNode(root->right, temp->value);
			}
		}
		return root;
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
		//   _root(x._root),
		//   _dummy(),
		  _size(x._size)
	{
		this->clear();
		_root = clone(x._root);
		_dummy.left = _root;
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
			// iterator it = begin();
			// while (it != end())
			// {
			// 	insert(*it);
			// 	++it;
			// }
			// insert(x.begin(), x.end());
			_dummy.left = _root;
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


	// ft::pair<iterator, bool> insert(const value_type& v)
	// {
	// 	if (this->find(v) != end())
	// 	{
	// 		node *res = search(_root, v);
	// 		return ft::make_pair(iterator(res), true);
	// 	}
	// 	node *new_node = create_node(v);
	// 	_dummy.left = _root;
	// 	_root = my_insert(_root, new_node);
	// 	_size++;

	// 	return ft::make_pair(iterator(new_node), true);
	// }

	size_type 	erase (const value_type& v)
	{
		node	*res = search(_root, v);
		// if (!res || !equals(v, res->value))
		// 	return 0;
		// _root = deleteNode(_root, v);
		delete_node(res);
		_size--;

		return 1;
	}

	void 		swap (tree& x)
	{
		if (this != &x)
		{
			// node save = this->_dummy;
			// this->_dummy = x._dummy;
			// x._dummy = save;
		}
	}

	void	clear()
	{
		delete_tree(_root);
	}

	value_compare	value_comp() const
		{ return _comp; }

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

	size_type count (const value_type& k) const
		{return find(k) != end();}

	void	right_rotate(node *x)
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

	void	left_rotate(node *x)
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
					left_rotate(z);
				}
				else {									// case 3: z's uncle is black (line)
					// recolor the original parent and grandparent (switch colors)
					// std::cout << "case 3\n";
					z->parent->is_black = 1;
					z->parent->parent->is_black = 0;
					right_rotate(z->parent->parent);	// rotate z's grandparent
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
					right_rotate(z);
				}
				else {
					z->parent->is_black = 1;
					z->parent->parent->is_black = 0;
					left_rotate(z->parent->parent);
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
			// y->left->parent = y;
			y->left = z;
		}
		else {
			// y->right->parent = y;
			y->right = z;
		}

		rb_insert_fixup(z);
	}

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

	// // returns pointer to sibling
	// node	*sibling(node *x)
	// {
	// 	if (x == nullptr || x->parent == nullptr) {
	// 		return nullptr;
	// 	}
	// 	if (x == x->parent->left) {
	// 		return x->parent->right;
	// 	}
	// 	return x->parent->left;
	// }

	// // find node that do not have a left child
	// // in the subtree of the given node
	// node	*successor(node *x)
	// {
	// 	node *tmp = x;

	// 	while (tmp->left != nullptr) {
	// 		tmp = tmp->left;
	// 	}
	// 	return tmp;
	// }

	// // find node that replaces a deleted node in the tree
	// node	*replace(node *x)
	// {
	// 	// if (!x)
	// 		// return nullptr;

	// 	// when has 2 children
	// 	if (x->left != nullptr && x->right != nullptr)
	// 		return successor(x->right);

	// 	// when leaf
	// 	if (x->left == nullptr && x->right == nullptr)
	// 		return nullptr;

	// 	// when has a 1 child
	// 	if (x->right == nullptr)
	// 		return x->left;
	// 	else
	// 		return x->right;
	// }

	// void	delete_node(node *v)
	// {
	// 	node *u  = replace(v);
	// 	bool uvBlack = ((u == nullptr || u->is_black) && (v->is_black));
	// 	node *parent = v->parent; // maybe delete it later on, loooks like it's useless

	// 	if (u == nullptr)
	// 	{
	// 		if (v == _root)
	// 		{
	// 			_root = nullptr;
	// 			_dummy.left = &_dummy;
	// 		}
	// 		else
	// 		{
	// 			if (uvBlack == true) {
	// 				doubleBlackFixup(v);
	// 			}
	// 			else {
	// 				if (sibling(v) != nullptr) {
	// 					sibling(v)->is_black = 0;
	// 				}
	// 			}

	// 			if (v == v->parent->left) {
	// 				parent->left = nullptr;
	// 			}
	// 			else {
	// 				parent->right = nullptr;
	// 			}
	// 		}
	// 		_a.destroy(&v->value);
	// 		_a_node.deallocate(v, 1);
	// 		return ;
	// 	}

	// 	if (v->left == nullptr || v->right == nullptr)
	// 	{
	// 		if (v == _root)
	// 		{
	// 			v->value = u->value;
	// 			v->left = nullptr;
	// 			v->right = nullptr;
	// 			_a.destroy(&u->value);
	// 			_a_node.deallocate(u, 1);
	// 		}
	// 		else
	// 		{
	// 			if (v == v->parent->left) {
	// 				parent->left = u;
	// 			}
	// 			else {
	// 				parent->right = u;
	// 			}
	// 			_a.destroy(&v->value);
	// 			_a_node.deallocate(v, 1);
	// 			u->parent = parent;
	// 			if (uvBlack == true) {
	// 				doubleBlackFixup(u);
	// 			}
	// 			else {
	// 				u->is_black = 1;
	// 			}
	// 		}
	// 		return ;
	// 	}
	// 	swapValues(u, v);
	// 	_a.destroy(&u->value);
	// 	_a_node.deallocate(u, 1);
	// }
};


#endif