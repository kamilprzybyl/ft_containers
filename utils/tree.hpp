#ifndef TREE_HPP
#define TREE_HPP

namespace ft
{

template<class T, class Comparable>
class tree_iterator
{
private:
	Node	*_current;

public:
	bool operator== (const tree_iterator& i) const
		{return _current == i._current;}
	bool operator!= (const tree_iterator& i) const
		{return *this != i;}
	const Comparable &operator* () const
		{return _current->element;}

	tree_iterator &operator++()
	{
		if (_current == nullptr)
		{
			// ++ from end(). get the root of the tree
			_current = _current->parent;
			// error! ++ requested for an empty tree
			if (_current == nullptr)
				throw UnderflowException { };
			// move to the smallest value in the tree,
			// which is the first node inorder
			while (_current->left != nullptr) {
				_current = _current->left;
			}
		}
		else
		{
			if (_current->right != nullptr)
			{
				// successor is the farthest left node of
				// right subtree
				_current = _current->right;
				while (_current->left != nullptr) {
					_current = _current->left;
				}
			}
			else
			{
				// have already processed the left subtree, and
				// there is no right subtree. move up the tree,
				// looking for a parent for which nodePtr is a left child,
				// stopping if the parent becomes NULL. a non-NULL parent
				// is the successor. if parent is NULL, the original node
				// was the last node inorder, and its successor
				// is the end of the list
				Node p = _current->parrent;
				while (p != nullptr && _current == p->right) {
					_current = p;
					p = p->parrent;
				}

				// if we were previously at the right-most node in
				// the tree, nodePtr = nullptr, and the iterator specifies
				// the end of the list
				_current = p;
			}
		}
		return *this;
	}
};



template<class T>
struct Node
{
	typedef T	value_type;
	value_type	element;
	Node		*parent;
	Node		*left;
	Node		*right;
	int			color; // int?
};



template <class Tp, class Compare, class Allocator>
class tree
{
public:
	typedef	T																	value_type;
	typedef	Compare																value_compare;
	typedef	Allocator															allocator_type;
	typedef typename Allocator::template rebind<tree_node<value_type> >::other	node_allocator_type;
	typedef	tree_node<value_type>												Node;
	typedef	tree_iterator<Node *, Tree, T>										iterator;
	typedef	tree_iterator<const Node *, Tree, const T>							const_iterator;
	typedef ft::reverse_iterator<iterator>										reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
	typedef	size_t																size_type;

	iterator begin()
		{return iterator(find_min(root), this);}
	const_iterator begin()
		{return const_iterator(find_min(root), this);}
	iterator end()
		{return iterator(nullptr, this);}
	const_iterator end()
		{return const_iterator(nullptr, this);}

	reverse_iterator rbegin()
		{return reverse_iterator(end());}
	const_reverse_iterator rbegin()
		{return const_reverse_iterator(end());}
	reverse_iterator rend()
		{return reverse_iterator(begin());}
	const_reverse_iterator rend()
		{return const_reverse_iterator(begin());}

	size_type size() const {return _size;}
	size_type max_size() const {return _max_size;}

	pair<iterator, bool> insert(const value_type& v)
	{

	}

	iterator  erase(const_iterator first, const_iterator last)
	{
		
	}

	
	// insert(Tp &val);
	// erase(Tp &val);
	// iteratore
	// red 
};

}

#endif