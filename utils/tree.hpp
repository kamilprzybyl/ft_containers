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
	tree_iterator(const tree_iterator<T *, container, value> & in) : _current(in.base()) { }
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
		tree_iterator save = _current;
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
		return save;
	}

	tree_iterator operator--(int) {
		tree_iterator save = _current;
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
		return save;
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
	// }
	bool operator==(tree_iterator const &other) const {
		return _current == other._current;
	}
	bool operator!=(tree_iterator const &other) const {
		return !(*this == other);
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

	typedef typename Allocator::template rebind<tree_node<value_type> >::other		tree_node_allocator_type;
	typedef	tree_node<value_type>													node;
	typedef	tree_iterator<node *, tree, T>										iterator;
	typedef	tree_iterator<const node *, tree, const T>							const_iterator;
	typedef	ft::reverse_iterator<iterator>							reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>							const_reverse_iterator;
	typedef	size_t																size_type;

private:
	value_compare	_comp;
	allocator_type	_a;
	tree_node_allocator_type	_a_node;
	node			*_root;
	node			*_parent;
	size_type		_size;
	size_type		_max_size;

public:
	tree(const value_compare& comp, const allocator_type& a)
		: _comp(comp),
		  _a(a),
		  _root(nullptr),
		  _size(),
		  _max_size()
	{
	}

	~tree() {}

	node	*find_min(node *root) const
	{
		while (root && root->left) {
			root = root->left;
		}
		return root;
	}

	iterator begin()
		{return iterator(find_min(_root));}
	// const_iterator begin()
	// 	{return const_iterator(find_min(_root));}
	iterator end()
		{return iterator(_root);}
	// const_iterator end()
	// 	{return const_iterator(nullptr);}

	size_type size() const {return _size;}
	size_type max_size() const {return _max_size;}


	void printHelper(node* root, std::string indent, bool last) {
		// print the tree structure on the screen
		if (root != nullptr) {
			if (last) {
				std::cout<<"└────";
				indent += "     ";
			} else {
				std::cout<<"├────";
				indent += "|    ";
			}

			std::cout << "[" << root->value.first << "|" << root->value.second << "]" << std::endl;

			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

	void prettyPrint() {
		printHelper(_root, "", true);
	}

	ft::pair<iterator, bool> insert(const value_type& v)
	{
		node *new_node = _a_node.allocate(1);
		_a.construct(&new_node->value, v);
		new_node->parent = nullptr;
		new_node->left = nullptr;
		new_node->right = nullptr;
		node *y = nullptr;
		node *x = this->_root;
		_size++;

		while (x != nullptr) {
			y = x;
			if (new_node->value < x->value) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// y is parent of x
		new_node->parent = y;
		if (y == nullptr) {
			_root = new_node;
		} else if (new_node->value < y->value) {
			y->left = new_node;
		} else {
			y->right = new_node;
		}

		return ft::make_pair(iterator(new_node), true);
	}
	// pair<iterator, bool> insert(const value_type& v)
	// {

	// }

	// iterator  erase(const_iterator first, const_iterator last)
	// {
		
	// }

	bool	equals(value_type const &first, value_type const &second) const {
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

	size_type 	erase (const value_type& v)
	{
		node	*tmp = search(_root, v);
		if (!tmp || !equals(v, tmp->value))
			return 0;
		// erase(tmp);
		return 1;
	}
};


#endif