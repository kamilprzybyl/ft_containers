#ifndef TREE_HPP
#define TREE_HPP

namespace ft
{

template<class T>
struct Node
{
	typedef T	value_type;
	int			data;
	Node		*parent;
	Node		*left;
	Node		*right;
	int			color; // int?
};

template <class Tp, class Compare, class Allocator>
class tree
{

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