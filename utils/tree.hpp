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
	size_type					_max_size;

public:
	tree(const value_compare& comp, const allocator_type& a)
		: _comp(comp),
		  _a(a),
		  _a_node(a),
		  _root(nullptr),
		  _dummy(),
		  _size(0),
		  _max_size(0)
	{
		_dummy.left = &_dummy;
		_dummy.right = nullptr;
	}

	tree	&operator=(const tree & x) {
		if (this != &x) {
			this->clear();
			_size = x._size;
			_comp = x._comp;
			_a = x._a;
			_a_node = x._a_node;
			_root = clone(x._root);
			_dummy.left = _root;
		}
		return *this;
	}

	~tree() {}

	node *create_node(const value_type& v)
	{
		node *new_node = _a_node.allocate(1);
		_a.construct(&new_node->value, v);
		new_node->parent = &_dummy;
		new_node->left = nullptr;
		new_node->right = nullptr;

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

	iterator begin()
		{return iterator(min(_dummy.left));}
	const_iterator begin() const
		{return const_iterator(min(_dummy.left));}
	iterator end()
		{return iterator(&_dummy);}
	const_iterator end() const
		{return const_iterator(&_dummy);}

	size_type size() const {return _size;}
	size_type max_size() const {return _max_size;}

	node *my_insert(node *root, node *new_node)
	{
		if (root == nullptr) {
			return new_node;
		}

		if (new_node->value < root->value) {
			node *left = my_insert(root->left, new_node);
			root->left = left;

			left->parent = root;
		}
		else if (new_node->value > root->value) {
			node *right = my_insert(root->right, new_node);
			root->right = right;

			right->parent = root;
		}

		return root;
	}

	ft::pair<iterator, bool> insert(const value_type& v)
	{
		node *new_node = create_node(v);
		_dummy.left = _root;
		_root = my_insert(_root, new_node);
		_size++;

		return ft::make_pair(iterator(new_node), true);
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

	size_type 	erase (const value_type& v)
	{
		_root = deleteNode(_root, v);
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
		while (_size != 0) {
			node *res = min(_root);
			erase(res->value);
		}
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

	iterator 		lower_bound (const value_type& k)
	{
		// iterator it = begin();

		// while (it != end() && !equals(*it, k) && !_comp(k, *it)) {
		// 	it++;
		// }
		// return it;
				(void)k;
		return begin();
	}

	const_iterator 		lower_bound (const value_type& k) const
	{
		return const_iterator(this->lower_bound(k));
	}

	iterator 		upper_bound (const value_type& k)
	{
		// reverse_iterator rbg = reverse_iterator(end());
		// reverse_iterator ren = reverse_iterator(begin());
		// while (rbg != ren && !equals(*rbg, k) && _comp(k, *rbg)) {
		// 	rbg++;
		// }
		(void)k;
		return begin();
	}

	const_iterator 		upper_bound (const value_type& k) const
	{
		return const_iterator(this->upper_bound(k));
	}
};


#endif